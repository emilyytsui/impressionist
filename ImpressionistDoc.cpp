// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LineBrush.h"
#include "CircleBrush.h"
#include "ScatteredPointBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredCircleBrush.h"
#include "TriangleBrush.h"
#include "RingBrush.h"
#include "StarBrush.h"

#include <cmath>
#include <cstring>


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes. 
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush( this, "Scattered Circles" );
	ImpBrush::c_pBrushes[BRUSH_TRIANGLES]			
		= new TriangleBrush( this, "Triangles" );
	ImpBrush::c_pBrushes[BRUSH_RINGS]
		= new RingBrush(this, "Rings");
	ImpBrush::c_pBrushes[BRUSH_STARS]
		= new StarBrush(this, "Stars");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

	m_nBrushDirection = BRUSH_DIRECTION_SLIDER;

	// initialize cursor angle
	m_previousCursor = Point(0, 0);
	m_cursorAngle = 0.0f;

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}


//---------------------------------------------------------
// Returns the brush direction.
//---------------------------------------------------------
int ImpressionistDoc::getBrushDirection()
{
	return m_nBrushDirection;
}


//---------------------------------------------------------
// Called by the UI when the user changes the brush
// direction.
// direction: one of the defined stroke directions.
//---------------------------------------------------------
void ImpressionistDoc::setBrushDirection(int direction)
{
	m_nBrushDirection = direction;
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Returns the line thickness of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getLineThickness()
{
	return m_pUI->getLineThickness();
}

//---------------------------------------------------------
// Returns the brush angle.
//---------------------------------------------------------
int ImpressionistDoc::getBrushAngle()
{
	return m_pUI->getBrushAngle();
}

//---------------------------------------------------------
// Returns the alpha value.
//---------------------------------------------------------
float ImpressionistDoc::getAlphaValue()
{
	return m_pUI->getAlphaValue();
}

//---------------------------------------------------------
// Returns the gradient angle.
//---------------------------------------------------------
float ImpressionistDoc::getGradientAngle(const Point source)
{
	const float PI = 3.14159265f;

	// Use the slider angle if no gradient can be determined.
	float fallbackAngle = getBrushAngle() * PI / 180.0f;

	if (m_ucBitmap == NULL)
		return fallbackAngle;

	const int sobelX[3][3] = {
		{-1,  0,  1},
		{-2,  0,  2},
		{-1,  0,  1}
	};

	const int sobelY[3][3] = {
		{-1, -2, -1},
		{ 0,  0,  0},
		{ 1,  2,  1}
	};

	float gx = 0.0f;
	float gy = 0.0f;

	// Examine the 3 × 3 neighborhood around the source pixel.
	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			GLubyte* pixel = GetOriginalPixel(
				source.x + x,
				source.y + y
			);

			// Convert RGB to Y-channel brightness.
			float brightness =
				0.299f * pixel[0]
				+ 0.587f * pixel[1]
				+ 0.114f * pixel[2];

			gx += brightness * sobelX[y + 1][x + 1];
			gy += brightness * sobelY[y + 1][x + 1];
		}
	}

	// Flat areas have no meaningful gradient direction.
	if (gx * gx + gy * gy < 0.000001f)
		return fallbackAngle;

	// Turn 90 degrees to point perpendicular to the gradient.
	return std::atan2(gy, gx) + PI / 2.0f;
}


void ImpressionistDoc::beginCursorStroke(const Point target)
{
	m_previousCursor = target;

	// Use the slider angle until the cursor starts moving.
	const float PI = 3.14159265f;
	m_cursorAngle = getBrushAngle() * PI / 180.0f;
}


void ImpressionistDoc::updateCursorDirection(const Point target)
{
	float dx = static_cast<float>(target.x - m_previousCursor.x);
	float dy = static_cast<float>(target.y - m_previousCursor.y);

	if (dx != 0.0f || dy != 0.0f) {
		m_cursorAngle = std::atan2(dy, dx);
	}

	m_previousCursor = target;
}


//---------------------------------------------------------
// Returns the cursor angle.
//---------------------------------------------------------
float ImpressionistDoc::getCursorAngle()
{
	return m_cursorAngle;
}




//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	m_undoPainting.clear();
	m_dissolveBase.clear();

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{
	m_undoPainting.clear();

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

//----------------------------------------------------------------
// Swap the contents of the painting window and the contents of 
// the original image window
//----------------------------------------------------------------
void ImpressionistDoc::swapContent()
{
	if (m_ucBitmap == NULL || m_ucPainting == NULL) {
		fl_alert("No image loaded.");
		return;
	}

	m_undoPainting.clear();
	m_dissolveBase.clear();

	unsigned char* temp = m_ucBitmap;
	m_ucBitmap = m_ucPainting;
	m_ucPainting = temp;

	m_pUI->m_origView->refresh();
	m_pUI->m_paintView->refresh();
}

//----------------------------------------------------------------
// Save the current state of the painting for undo functionality
//----------------------------------------------------------------
void ImpressionistDoc::saveUndoState()
{
	if (m_ucPainting == NULL)
		return;

	const std::size_t bytes =
		static_cast<std::size_t>(m_nPaintWidth) *
		m_nPaintHeight * 3;

	m_undoPainting.assign(
		m_ucPainting,
		m_ucPainting + bytes
	);
}

void ImpressionistDoc::undo()
{
	if (m_ucPainting == NULL || m_undoPainting.empty())
		return;

	std::memcpy(
		m_ucPainting,
		m_undoPainting.data(),
		m_undoPainting.size()
	);

	m_undoPainting.clear();
	m_pUI->m_paintView->refresh();
}

// Dissolve a second image into the original, which brushes sample from.
// Center the second image and crop anything outside the original.
int ImpressionistDoc::dissolveImage(char* filename, float amount)
{
	if (m_ucBitmap == NULL)
	{
		fl_alert("Load the original image first.");
		return 0;
	}

	int secondWidth = 0;
	int secondHeight = 0;

	unsigned char* secondImage =
		readBMP(filename, secondWidth, secondHeight);

	if (secondImage == NULL ||
		secondWidth <= 0 || secondHeight <= 0)
	{
		delete[] secondImage;
		fl_alert("Could not load the second BMP.");
		return 0;
	}

	if (amount < 0.0f)
		amount = 0.0f;

	if (amount > 1.0f)
		amount = 1.0f;

	// Keep the first image so loading another BMP replaces the second image.
	const std::size_t bytes =
		static_cast<std::size_t>(m_nWidth) * m_nHeight * 3;
	if (m_dissolveBase.empty())
		m_dissolveBase.assign(m_ucBitmap, m_ucBitmap + bytes);

	// Always start from the first image, not the previous blend.
	unsigned char* dissolvedImage = new unsigned char[bytes];
	std::memcpy(dissolvedImage, m_dissolveBase.data(), bytes);

	// Center the second image over the original.
	int offsetX = (m_nWidth - secondWidth) / 2;
	int offsetY = (m_nHeight - secondHeight) / 2;

	for (int y = 0; y < m_nHeight; ++y)
	{
		int secondY = y - offsetY;

		// No overlap on this row: keep the original.
		if (secondY < 0 || secondY >= secondHeight)
			continue;

		for (int x = 0; x < m_nWidth; ++x)
		{
			int secondX = x - offsetX;

			// No overlap at this pixel: keep the original.
			if (secondX < 0 || secondX >= secondWidth)
				continue;

			std::size_t originalIndex =
				(static_cast<std::size_t>(y) * m_nWidth + x) * 3;

			std::size_t secondIndex =
				(static_cast<std::size_t>(secondY) *
					secondWidth + secondX) * 3;

			// Blend the overlapping pixels.
			for (int channel = 0; channel < 3; ++channel)
			{
				float value =
					(1.0f - amount) *
					m_dissolveBase[originalIndex + channel] +
					amount *
					secondImage[secondIndex + channel];

				dissolvedImage[originalIndex + channel] =
					static_cast<unsigned char>(value + 0.5f);
			}
		}
	}

	delete[] secondImage;

	// Replace the source image that both OriginalView and the brushes use.
	delete[] m_ucBitmap;
	m_ucBitmap = dissolvedImage;
	m_pUI->m_origView->refresh();
	return 1;
}

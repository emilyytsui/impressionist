// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"

#include <vector>

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType

	int		getBrushDirection();			// get the UI brush direction
	void	setBrushDirection(int direction);	// called by the UI to set the brush direction

	int		getSize();						// get the UI size
	void	setSize(int size);				// set the UI size

	int		getLineThickness();				// get the UI line thickness
	int		getBrushAngle();				// get the UI brush angle
	float	getAlphaValue();				// get the UI alpha value

	float	getGradientAngle(const Point source); // get the gradient angle

	void beginCursorStroke(const Point target);
	void updateCursorDirection(const Point target);
	float getCursorAngle(); // get the cursor angle

	void swapContent();

	void saveUndoState();
	void undo();

	char*	getImageName();					// get the current image name
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;


	// The current active brush.
	ImpBrush*			m_pCurrentBrush;
	// The current active brush direction.
	int m_nBrushDirection;
	// Size of the brush.
	int m_nSize;							

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  


private:
	char			m_imageName[256];
	Point			m_previousCursor;
	float			m_cursorAngle;

	std::vector<unsigned char> m_undoPainting;

};

extern void MessageBox(char *message);

#endif

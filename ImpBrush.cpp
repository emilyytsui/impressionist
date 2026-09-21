//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
//void ImpBrush::SetColor (const Point source)
//{
//	ImpressionistDoc* pDoc = GetDocument();
//
//	GLubyte color[4];
//
//	memcpy(color, pDoc->GetOriginalPixel(source), 3);
//
//	float alphaValue = pDoc->getAlphaValue();
//
//	// Convert the slider's 0–1 value to an alpha byte (0–255)
//	color[3] = GLubyte(alphaValue * 255.0f);
//
//	glColor4ubv(color);
//
//}

void ImpBrush::SetColor(const Point source)
{
    ImpressionistDoc* pDoc = GetDocument();

    GLubyte* sampledColor = pDoc->GetOriginalPixel(source);
    GLubyte color[4];

    for (int channel = 0; channel < 3; ++channel)
    {
        double value =
            sampledColor[channel] *
            pDoc->m_pUI->m_rgbSliders[channel]->value();

        if (value < 0.0f)
            value = 0.0f;

        if (value > 255.0f)
            value = 255.0f;

        color[channel] = static_cast<GLubyte>(value + 0.5f);
    }

    color[3] = static_cast<GLubyte>(
        pDoc->getAlphaValue() * 255.0f + 0.5f
        );

    glColor4ubv(color);
}
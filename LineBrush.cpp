//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "linebrush.h"
#include <cmath>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	int thickness = pDoc->getLineThickness();

	glLineWidth((float)thickness);

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	float halfLength = size / 2.0f;

	// Convert the slider angle from degrees to radians
	const float PI = 3.14159265f;
	float angle;

	//if (pDoc->getBrushDirection() == BRUSH_DIRECTION_SLIDER) // Slider angle
	//{
	//	
	//}
	//else 
	if (pDoc->getBrushDirection() == BRUSH_DIRECTION_GRADIENT) // Gradient angle
	{
		angle = pDoc->getGradientAngle(source);
	}
	else
	{
		angle = pDoc->getBrushAngle() * PI / 180.0f;
	}

	// Horizontal and vertical distances from the line's center
	float dx = halfLength * std::cos(angle);
	float dy = halfLength * std::sin(angle);

	glBegin(GL_LINES);
	SetColor(source);

	glVertex2f(target.x - dx, target.y - dy);
	glVertex2f(target.x + dx, target.y + dy);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


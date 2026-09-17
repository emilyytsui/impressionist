//
// SquareBrush.cpp
//
// The implementation of Square Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "squarebrush.h"

extern float frand();

SquareBrush::SquareBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void SquareBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void SquareBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("SquareBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	float halfSize = size / 2.0f;

	glBegin(GL_QUADS);
	SetColor(source);

	glVertex2d(target.x - halfSize, target.y - halfSize);
	glVertex2d(target.x + halfSize, target.y - halfSize);
	glVertex2d(target.x + halfSize, target.y + halfSize); 
	glVertex2d(target.x - halfSize, target.y + halfSize);

	glEnd();
}

void SquareBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


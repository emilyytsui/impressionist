//
// TriangleBrush.cpp
//
// The implementation of Triangle Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "trianglebrush.h"

extern float frand();

TriangleBrush::TriangleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void TriangleBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("TriangleBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	float halfSize = size / 2.0f;

	glBegin(GL_TRIANGLES);
	SetColor(source);

	glVertex2d(target.x - halfSize, target.y + halfSize);
	glVertex2d(target.x + halfSize, target.y + halfSize);
	glVertex2d(target.x, target.y - halfSize);

	glEnd();
}

void TriangleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


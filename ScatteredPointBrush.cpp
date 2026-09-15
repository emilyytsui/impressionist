//
// ScatteredPointBrush.cpp
//
// The implementation of Scattered Point Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredpointbrush.h"

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	glPointSize(1.0f);

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	const int scatterCount = 15; // Number of points to scatter

	glBegin(GL_POINTS);


	for (int i = 0; i < scatterCount; i++) {
		// Randomly offset the source and target points within the brush size
		int offsetX = rand() % size - size / 2;
		int offsetY = rand() % size - size / 2;

		Point scatteredSource(source.x + offsetX, source.y + offsetY);
		Point scatteredTarget(target.x + offsetX, target.y + offsetY);

		SetColor(scatteredSource);
		glVertex2d(scatteredTarget.x, scatteredTarget.y);
	}

	glEnd();
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


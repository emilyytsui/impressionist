//
// ScatteredLineBrush.cpp
//
// The implementation of Scattered Line Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredlinebrush.h"

extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	glLineWidth(1.0f);

	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	float halfLength = size / 2.0f;
	const int scatterCount = 3; // Number of lines to scatter

	glBegin(GL_LINES);

	for (int i = 0; i < scatterCount; i++)
	{
		int offsetX = rand() % size - size / 2;
		int offsetY = rand() % size - size / 2;

		Point scatteredSource(source.x + offsetX, source.y + offsetY);
		Point scatteredTarget(target.x + offsetX, target.y + offsetY);

		SetColor(scatteredSource);

		glVertex2f(scatteredTarget.x - halfLength, scatteredTarget.y);
		glVertex2f(scatteredTarget.x + halfLength, scatteredTarget.y);
	}


	glEnd();
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


//
// ScatteredLineBrush.cpp
//
// The implementation of Scattered Line Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredlinebrush.h"
#include <cmath>

extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	int thickness = pDoc->getLineThickness();

	glLineWidth((float)thickness);

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

	// Convert the slider angle from degrees to radians
	const float PI = 3.14159265f;

	glBegin(GL_LINES);

	for (int i = 0; i < scatterCount; i++)
	{
		int offsetX = rand() % size - size / 2;
		int offsetY = rand() % size - size / 2;

		Point scatteredSource(source.x + offsetX, source.y + offsetY);
		Point scatteredTarget(target.x + offsetX, target.y + offsetY);

        float angle;

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

		SetColor(scatteredSource);

		glVertex2f(scatteredTarget.x - dx, scatteredTarget.y - dy);
		glVertex2f(scatteredTarget.x + dx, scatteredTarget.y + dy);
	}


	glEnd();
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


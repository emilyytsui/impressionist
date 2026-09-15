//
// ScatteredCircleBrush.cpp
//
// The implementation of Scattered Circle Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredcirclebrush.h"
#include <cmath>

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	glLineWidth(1.0f);

	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove document is NULL\n");
		return;
	}

    int size = pDoc->getSize();
    float radius = size / 2.0f;
    const float PI = 3.14159265f;
    const int segments = 32;
    const float angle_step = (2.0f * PI) / segments;
    const int scatterCount = 2;

    for (int i = 0; i < scatterCount; i++)
    {
        int offsetX = rand() % size - size / 2;
        int offsetY = rand() % size - size / 2;

        Point scatteredSource(source.x + offsetX, source.y + offsetY);
        Point scatteredTarget(target.x + offsetX, target.y + offsetY);

        glBegin(GL_TRIANGLE_FAN);
        SetColor(scatteredSource);

        // First vertex: the center of the circle.
        glVertex2d(scatteredTarget.x, scatteredTarget.y);

        // Remaining vertices: positions around its edge.
        for (int j = 0; j <= segments; j++) {
            float angle = j * angle_step;

            float x = scatteredTarget.x + radius * std::cos(angle);
            float y = scatteredTarget.y + radius * std::sin(angle);

            glVertex2f(x, y);
        }

        glEnd();

    }
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


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

    glBegin(GL_TRIANGLE_FAN);
    SetColor(source);

    // First vertex: the center of the circle.
    glVertex2d(target.x, target.y);

    // Remaining vertices: positions around its edge.
    for (int i = 0; i <= segments; i++) {
        float angle = i * angle_step;

        float x = target.x + radius * std::cosf(angle);
        float y = target.y + radius * std::sinf(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


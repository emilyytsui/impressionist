//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circlebrush.h"
#include <cmath>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove document is NULL\n");
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

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


//
// RingBrush.cpp
//
// The implementation of Ring Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ringbrush.h"

#include <cmath>

extern float frand();

RingBrush::RingBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void RingBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void RingBrush::BrushMove(const Point source, const Point target)
{
    ImpressionistDoc* pDoc = GetDocument();

    if (pDoc == NULL) {
        printf("RingBrush::BrushMove document is NULL\n");
        return;
    }

    float radius = pDoc->getSize() / 2.0f;
    const float PI = 3.14159265f;
    const int segments = 32;

    glLineWidth((float)pDoc->getLineThickness());
    SetColor(source);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < segments; i++) {
        float angle = i * 2.0f * PI / segments;

        float x = target.x + radius * std::cos(angle);
        float y = target.y + radius * std::sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

void RingBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


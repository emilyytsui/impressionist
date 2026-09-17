//
// StarBrush.cpp
//
// The implementation of Star Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "starbrush.h"
#include <cmath>

extern float frand();

StarBrush::StarBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void StarBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void StarBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("StarBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	float outerRadius = size / 2.0f;
	float innerRadius = outerRadius * 0.4f;
	const float PI = 3.14159265f;
	const int points = 5;
	const int segments = points * 2;
	const float angle_step = PI / points;

	glBegin(GL_TRIANGLE_FAN);
	SetColor(source);

	// First vertex: the center of the star.
	glVertex2d(target.x, target.y);

	// Remaining vertices: alternating outer and inner points around its edge.
	for (int i = 0; i <= segments; i++) {
		float angle = (i * angle_step) - (PI / 2.0f);
		float radius = (i % 2 == 0) ? outerRadius : innerRadius;

		float x = target.x + radius * std::cosf(angle);
		float y = target.y + radius * std::sinf(angle);

		glVertex2f(x, y);
	}

	glEnd();
}

void StarBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}


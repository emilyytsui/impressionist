//
// SquareBrush.h
//
// The header file for Square Brush. 
//

#ifndef SQUAREBRUSH_H
#define SQUAREBRUSH_H

#include "ImpBrush.h"

class SquareBrush : public ImpBrush
{
public:
	SquareBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
};

#endif
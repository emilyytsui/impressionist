#ifndef FILTERBRUSH_H
#define FILTERBRUSH_H

#include "ImpBrush.h"
#include <vector>

class FilterBrush : public ImpBrush
{
public:
	FilterBrush(ImpressionistDoc* pDoc, char* name, bool sharpen);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);

private:
	bool m_sharpen;
	int m_width;
	int m_height;
	std::vector<unsigned char> m_strokePixels;
};

#endif

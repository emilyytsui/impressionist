#include "FilterBrush.h"
#include "ImpressionistDoc.h"

FilterBrush::FilterBrush(ImpressionistDoc* pDoc, char* name, bool sharpen) :
	ImpBrush(pDoc, name), m_sharpen(sharpen), m_width(0), m_height(0)
{
}

void FilterBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	m_strokePixels.clear();
	if (pDoc == NULL || pDoc->m_ucPainting == NULL ||
		pDoc->m_nPaintWidth <= 0 || pDoc->m_nPaintHeight <= 0)
		return;

	m_width = pDoc->m_nPaintWidth;
	m_height = pDoc->m_nPaintHeight;
	const std::size_t bytes = static_cast<std::size_t>(m_width) * m_height * 3;
	m_strokePixels.assign(pDoc->m_ucPainting, pDoc->m_ucPainting + bytes);
	BrushMove(source, target);
}

void FilterBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL || pDoc->m_ucPainting == NULL || m_strokePixels.empty() ||
		m_width != pDoc->m_nPaintWidth || m_height != pDoc->m_nPaintHeight)
		return;

	const int blurKernel[3][3] = {
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 1, 1, 1 }
	};
	const int sharpenKernel[3][3] = {
		{ 0, -1, 0 },
		{ -1, 5, -1 },
		{ 0, -1, 0 }
	};
	const int (*kernel)[3] = m_sharpen ? sharpenKernel : blurKernel;
	const float divisor = m_sharpen ? 1.0f : 9.0f;
	const int size = pDoc->getSize();
	const int half = size / 2;
	float strength = pDoc->getAlphaValue();
	if (strength < 0.0f) strength = 0.0f;
	if (strength > 1.0f) strength = 1.0f;

	// PaintView passes the upper edge of the pixel as its source Y.
	const int centerY = source.y - 1;
	glPushAttrib(GL_CURRENT_BIT | GL_POINT_BIT | GL_ENABLE_BIT);
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_DITHER);
	glPointSize(1.0f);
	glBegin(GL_POINTS);

	for (int dy = -half; dy < size - half; ++dy)
	{
		const int y = centerY + dy;
		if (y < 0 || y >= m_height) continue;

		for (int dx = -half; dx < size - half; ++dx)
		{
			const int x = source.x + dx;
			if (x < 0 || x >= m_width) continue;

			const std::size_t index = (static_cast<std::size_t>(y) * m_width + x) * 3;
			GLubyte color[3];
			for (int channel = 0; channel < 3; ++channel)
			{
				int sum = 0;
				for (int ky = -1; ky <= 1; ++ky)
				{
					int sampleY = y + ky;
					if (sampleY < 0) sampleY = 0;
					if (sampleY >= m_height) sampleY = m_height - 1;

					for (int kx = -1; kx <= 1; ++kx)
					{
						int sampleX = x + kx;
						if (sampleX < 0) sampleX = 0;
						if (sampleX >= m_width) sampleX = m_width - 1;

						const std::size_t sampleIndex =
							(static_cast<std::size_t>(sampleY) * m_width + sampleX) * 3;
						sum += kernel[ky + 1][kx + 1] * m_strokePixels[sampleIndex + channel];
					}
				}

				float filtered = sum / divisor;
				if (filtered < 0.0f) filtered = 0.0f;
				if (filtered > 255.0f) filtered = 255.0f;

				const float value = (1.0f - strength) * m_strokePixels[index + channel] +
					strength * filtered;
				color[channel] = static_cast<GLubyte>(value + 0.5f);
				pDoc->m_ucPainting[index + channel] = color[channel];
			}

			// Draw at pixel centers, matching the canvas bytes updated above.
			glColor3ubv(color);
			glVertex2d(target.x + dx + 0.5, target.y + dy - 0.5);
		}
	}

	glEnd();
	glPopAttrib();
}

void FilterBrush::BrushEnd(const Point source, const Point target)
{
	m_strokePixels.clear();
}

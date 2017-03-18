#ifndef _MAT_H
#define _MAT_H

typedef struct {
	void** content;
	unsigned int width;
	unsigned int height;
} _ColorMat, *ColorMat;

typedef struct {
	void** content;
	unsigned int width;
	unsigned int height;
} _WeightMat, *WeightMat;


ColorMat CreateColorMat(unsigned int width, unsigned int height);
void DesdroyColorMat(ColorMat mat);
ColorMat CreateWeightMat(unsigned int width, unsigned int height);
void DesdroyWeightMat(ColorMat mat);

#endif //_MAT_H


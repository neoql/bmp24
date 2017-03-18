#ifndef _MAT_H
#define _MAT_H


#include "bitmap.h"

typedef struct {
	Color** content;
	unsigned int width;
	unsigned int height;
} _ColorMat, *ColorMat;

typedef struct {
	double ** content;
	unsigned int width;
	unsigned int height;
} _WeightMat, *WeightMat;


ColorMat CreateColorMat(unsigned int width, unsigned int height);
void DesdroyColorMat(ColorMat mat);
WeightMat CreateWeightMat(unsigned int width, unsigned int height);
void DesdroyWeightMat(WeightMat mat);

#endif //_MAT_H


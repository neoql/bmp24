#include "mat.h"
#include <stdlib.h>


ColorMat CreateColorMat(unsigned int width, unsigned int height)
{
	ColorMat mat;
	int i;
	Color **content;

	mat = malloc(sizeof(_ColorMat));
	content = (Color**)malloc(height * sizeof(Color*));
	for (i = 0; i < height; i++) {
		content[i] = malloc(sizeof(Color) * width);
	}

	mat->content = content;
	mat->width = width;
	mat->height = height;

	return mat;
}


WeightMat CreateWeightMat(unsigned int width, unsigned int height)
{
    WeightMat mat;
    int i;
    double **content;

    mat = malloc(sizeof(_WeightMat));
    content = (double **)malloc(height * sizeof(double *));
    for (i = 0; i < height; i++) {
        content[i] = malloc(sizeof(double) * width);
    }

    mat->content = content;
    mat->width = width;
    mat->height = height;

    return mat;
}


void DesdroyColorMat(ColorMat mat)
{
	int i;

	for (i = 0; i < mat->height; i++) {
		free(mat->content[i]);
	}
	free(mat->content);
	free(mat);
}


void DesdroyWeightMat(WeightMat mat)
{
    int i;

    for (i = 0; i < mat->height; i++) {
        free(mat->content[i]);
    }
    free(mat->content);
    free(mat);
}


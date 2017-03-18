#include "mat.h"
#include <stdlib.h>
#include "string.h"


ColorMat CreateColorMat(unsigned int width, unsigned int height)
{
	ColorMat mat;
	int i;
    void **content;

    mat = malloc(sizeof(_ColorMat));
	content = (void**)malloc(height * sizeof(void*));
	for (i = 0; i < height; i++) {
		content[i] = malloc(sizeof() * width);
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


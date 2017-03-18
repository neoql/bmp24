#include "mat.h"
#include <stdlib.h>
#include "string.h"


Mat CreateMat(unsigned int width, unsigned int height, unsigned int size)
{
	Mat mat;
	int i;
    void **content;

    mat = malloc(sizeof(_Mat));
	content = (void**)malloc(height * sizeof(void*));
	for (i = 0; i < height; i++) {
		content[i] = malloc(size * width);
	}

    mat->content = content;
	mat->width = width;
	mat->height = height;

	return mat;
}


void DesdroyMat(Mat mat)
{
	int i;

	for (i = 0; i < mat->height; i++) {
		free(mat->content[i]);
	}
	free(mat->content);
	free(mat);
}


#ifndef _MAT_H
#define _MAT_H

typedef struct {
	void** content;
	unsigned int width;
	unsigned int height;
} _Mat, *Mat;


Mat CreateMat(unsigned int width, unsigned int height, unsigned int size);
void DesdroyMat(Mat mat);

#endif //_MAT_H


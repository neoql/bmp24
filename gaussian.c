#include <math.h>
#include <string.h>
#include "gaussian.h"

#define PI 3.1415926


double GetWeight(int x, int y, int radius)
{
	double sigma;
	double weight;

	sigma = (radius * 2 + 1) / 2;
	weight = (1 / (2 * PI * sigma * sigma)) * pow(exp(1), ((-(x * x + y * y)) / ((2 * sigma)*(2 * sigma))));

	return weight;
}


WeightMat GetWeightMat(int radius)
{
	WeightMat mat;
	int i, j;
	double sum;
	double weight;

	sum = 0;

	mat = CreateWeightMat(radius * 2 + 1, radius * 2 + 1, sizeof(double));
	for (i = 0; i < mat->width; i++) {
		for (j = 0; j < mat->height; j++) {
			weight = GetWeight(i - radius, radius - i, radius);
			sum += weight;
			memcpy(mat->content[j] + i, &weight, sizeof(double));
		}
	}

	for (i = 0; i < mat->width; i++) {
		for (j = 0; j < mat->height; j++) {
			memcpy(&weight, mat->content[j] + i, sizeof(double));
			weight /= sum;
			memcpy(mat->content[j] + i, &weight, sizeof(double));
		}
	}

	return mat;
}


Mat GetColorMat(int x, int y, int radius, Bitmap bmp)
{
	Mat mat;
	int startX, startY, len;
	int i, j;
	int count;
	Color color;

	count = 0;
	startX = x - radius;
	startY = y - radius;
	len = radius * 2 + 1;

	mat = CreateMat(radius * 2 + 1, radius * 2 + 1, sizeof(Color));

	for (i = startX; i < startX + len; i++) {
		for (j = startY; j < startY + len; j++) {
			color = GetPointColor(bmp, i, j);
			memcpy((Color*)mat->content[j] + i, &color, sizeof(Color));
		}
	}

	return mat;
}


Color GetBlurColor(Mat color_mat, Mat weight_mat)
{
	Color color, tmp;
	int i, j;
	double weight;

	color.r = 0;
	color.g = 0;
	color.b = 0;

	for (i = 0; i < color_mat->width; i++) {
		for (j = 0; j < color_mat->height; j++) {
			memcpy(&tmp, color_mat->content[j] + i, sizeof(Color));
			memcpy(&weight, weight_mat->content[j] + i, sizeof(double));
			color.r += tmp.r * weight;
			color.g += tmp.g * weight;
			color.b += tmp.b * weight;
		}
	}

	return color;
}


Bitmap GsTrans(Bitmap bmp, int radius)
{
	Bitmap img;
	int i, j;
	Mat weight_mat, color_mat;
	Color color;

	img = CloneBmp(bmp);

	weight_mat = GetWeightMat(radius);

	for (i = radius; i < img->info_header.biWidth - radius; i++) {
		for (j = radius; j < img->info_header.biHeight - radius; j++) {
			color_mat = GetColorMat(i, j, radius, bmp);
			color = GetBlurColor(color_mat, weight_mat);
			SetPointColor(bmp, i, j, color);
			DesdroyMat(color_mat);
		}
	}

	DesdroyMat(weight_mat);
	return img;
}


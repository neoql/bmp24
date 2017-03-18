#include <math.h>
#include <string.h>
#include "gaussian.h"
#include "mat.h"

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

	mat = CreateWeightMat(radius * 2 + 1, radius * 2 + 1);
	for (i = 0; i < mat->width; i++) {
		for (j = 0; j < mat->height; j++) {
			weight = GetWeight(i - radius, radius - i, radius);
			sum += weight;
			mat->content[j][i] = weight;
		}
	}

	for (i = 0; i < mat->width; i++) {
		for (j = 0; j < mat->height; j++) {
			weight = mat->content[j][i];
			weight /= sum;
			mat->content[j][i] = weight;
		}
	}

	return mat;
}


ColorMat GetColorMat(int x, int y, int radius, Bitmap bmp)
{
	ColorMat mat;
	int startX, startY, len;
	int i, j;
	int count;
	Color color;

	count = 0;
	startX = x - radius;
	startY = y - radius;
	len = radius * 2 + 1;

	mat = CreateColorMat(radius * 2 + 1, radius * 2 + 1);

	for (i = startX; i < startX + len; i++) {
		for (j = startY; j < startY + len; j++) {
			color = GetPointColor(bmp, i, j);
			mat->content[count % len][count / len] = color;
			count++;
		}
	}

	return mat;
}


Color GetBlurColor(ColorMat color_mat, WeightMat weight_mat)
{
	Color color, tmp;
	int i, j;
	double weight;

	color.r = 0;
	color.g = 0;
	color.b = 0;

	for (i = 0; i < color_mat->width; i++) {
		for (j = 0; j < color_mat->height; j++) {
			tmp = color_mat->content[j][i];
			weight = weight_mat->content[j][i];
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
	WeightMat weight_mat;
	ColorMat color_mat;
	Color color;

	img = CloneBmp(bmp);

	weight_mat = GetWeightMat(radius);

	for (i = radius; i < img->info_header.biWidth - radius; i++) {
		for (j = radius; j < img->info_header.biHeight - radius; j++) {
			color_mat = GetColorMat(i, j, radius, bmp);
			color = GetBlurColor(color_mat, weight_mat);
			SetPointColor(bmp, i, j, color);
			DesdroyColorMat(color_mat);
		}
	}

	DesdroyWeightMat(weight_mat);
	return img;
}


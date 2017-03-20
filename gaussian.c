#include "gaussian.h"
#include <math.h>
#include <stdlib.h>


#define PI 3.1415926


static double GetWeight(int x, double sigma)
{
	double weight;

	weight = (1 / (pow(2 * PI, 0.5) * sigma)) * exp(- (x * x) / (2 * sigma * sigma));

	return weight;
}


static double* GetWeightArray(double sigma, int radius)
{
	int len;
	double* wa;
	int i;
	double sum = 0;


	len = radius * 2 + 1;
	wa = malloc(sizeof(double) * len);

	for (i = 0; i < len; i++) {
		wa[i] = GetWeight(i - radius, sigma);
		sum += wa[i];
	}

	for (i = 0; i < len; i++) {
		wa[i] /= sum;
	}

	return wa;
}


static Color* GetColorArray(Bitmap bmp, int x, int y, int radius, int direct)
{
	Color* ca;
	int len;
	int i;

	len = radius * 2 + 1;
	ca = malloc(sizeof(Color) * len);

    if (direct) {
        // H
        x -= radius;
    } else {
        // V
        y -= radius;
    }

	for (i = 0; i < len; i++) {
		if (direct) {
			// H
			ca[i] = GetPointColor(bmp, x + i, y);
		} else {
			// V
			ca[i] = GetPointColor(bmp, x, y + i);
		}
	}

	return ca;
}


static Color GetBlurColor(Color* ca, double* wa, int radius)
{
	Color color;
	int i;
	int len;

	len = radius * 2 + 1;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	for (i = 0; i < len; i++) {
		color.r += ca[i].r * wa[i];
		color.g += ca[i].g * wa[i];
		color.b += ca[i].b * wa[i];
	}

	return color;
}


static void GsHVTrans(Bitmap dest, Bitmap src, double sigma, int radius, int direct)
{
	int x, y;
	double* wa;
	Color* ca;
	Color color;

	wa = GetWeightArray(sigma, radius);

	for (x = 0; x < src->info_header.biWidth; x++) {
		for (y = 0; y < src->info_header.biHeight; y++) {
			ca = GetColorArray(src, x, y, radius, direct);
			color = GetBlurColor(ca, wa, radius);
			SetPointColor(dest, x, y, color);
			free(ca);
		}
	}
	free(wa);
}


static void GsHTrans(Bitmap dest, Bitmap src, double sigma, int radius)
{
	GsHVTrans(dest, src, sigma, radius, 1);
}


static void GsVTrans(Bitmap dest, Bitmap src, double sigma, int radius)
{
	GsHVTrans(dest, src, sigma, radius, 0);
}


Bitmap GsTrans(Bitmap bmp, double sigma)
{
	Bitmap tmp, dest;
	int radius;

	radius = (int) ceil(sigma * 3);

	tmp = CloneBmp(bmp);
	GsHTrans(tmp, bmp, sigma, radius);

	dest = CloneBmp(tmp);
	GsVTrans(dest, tmp, sigma, radius);

    DestroyBmp(tmp);

	return dest;
}


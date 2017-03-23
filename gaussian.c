#include "gaussian.h"
#include "bitmap.h"
#include <math.h>
#include <stdlib.h>


#define PI 3.1415926


static double GetWeight(int x, double sigma)
{
	double weight;

	weight = (1 / (pow(2 * PI, 0.5) * sigma)) * exp(- (x * x) / (2 * sigma * sigma));

	return weight;
}


static double* GetWeightSubArray(double sigma, int radius, int start, int end)
{
    	double *wa;
    	int i;
    	double sum = 0;

    	wa = malloc(sizeof(double) * (radius * 2 + 1));

    	for (i = 0; i < radius * 2 + 1; i++) {
        	wa[i] = 0;
    	}

    	for (i = start; i <= end; i++) {
        	wa[i] = GetWeight(i - radius, sigma);
        	sum += wa[i];
    	}

    	for (i = start; i <= end; i++) {
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
    	double r, g, b;

	len = radius * 2 + 1;
	r = 0;
	g = 0;
	b = 0;

	for (i = 0; i < len; i++) {
		r += ca[i].r * wa[i];
		g += ca[i].g * wa[i];
		b += ca[i].b * wa[i];
	}
    	color.r = (uchar)(int)r;
    	color.g = (uchar)(int)g;
    	color.b = (uchar)(int)b;

	return color;
}


static void GsHTrans(Bitmap dest, Bitmap src, double sigma, int radius)
{
    	int x, y;
    	double* wa, *wsa;
    	Color* ca;
    	Color color;
        int start, end;

    	wa = GetWeightSubArray(sigma, radius, 0, radius * 2);

    	for (x = 0; x < src->info_header.biWidth; x++) {
                if (x < radius || x >= src->info_header.biWidth - radius) {
                        start = 0;
                        end = radius * 2;
                        if (x < radius) {
                                start = radius - x;
                        }
                        if (x >= src->info_header.biWidth - radius) {
                                end = radius + src->info_header.biWidth - x - 1;
                        }
                        wsa = GetWeightSubArray(sigma, radius, start, end);
                } else {
                        wsa = wa;
                }

        	for (y = 0; y < src->info_header.biHeight; y++) {

            		ca = GetColorArray(src, x, y, radius, 1);
            		color = GetBlurColor(ca, wsa, radius);
            		SetPointColor(dest, x, y, color);
            		free(ca);

        	}
        	if (wsa != wa) {
            		free(wsa);
        	}
    	}
    	free(wa);
}


static void GsVTrans(Bitmap dest, Bitmap src, double sigma, int radius)
{
    	int x, y;
    	double* wa, *wsa;
    	Color* ca;
    	Color color;
        int start, end;

        wa = GetWeightSubArray(sigma, radius, 0, radius * 2);

    	for (y = 0; y < src->info_header.biHeight; y++) {
                if (y < radius || y >= src->info_header.biHeight - radius) {
                        start = 0;
                        end = radius * 2;
                        if (y < radius) {
                                start = radius - y;
                        }
                        if (y >= src->info_header.biHeight - radius) {
                                end = radius + src->info_header.biHeight - y - 1;
                        }
                        wsa = GetWeightSubArray(sigma, radius, start, end);
                } else {
                        wsa = wa;
                }
        	for (x = 0; x < src->info_header.biWidth; x++) {

            		ca = GetColorArray(src, x, y, radius, 0);
            		color = GetBlurColor(ca, wsa, radius);
            		SetPointColor(dest, x, y, color);
            		free(ca);

        	}
        	if (wsa != wa) {
            		free(wsa);
        	}
    	}
    	free(wa);
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

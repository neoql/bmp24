//
// Created by moons on 17-4-27.
//

#include "median.h"
#include "bitmap.h"
#include <stdlib.h>


static void sort(int *array, int length)
{
        int i, j;
        int temp;

        for (i = 0; i < length - 1; i++) {
                for (j = i; j < length - 1; j++) {
                        if (array[i] > array[j + 1]) {
                                temp = array[i];
                                array[i] = array[j + 1];
                                array[j + 1] = temp;
                        }
                }
        }
}


static Color GetMedianRGB(int x, int y, int radius, Bitmap bmp)
{
        Color color;
        int width, height;
        int xstart, ystart;
        int *r, *g, *b, *gray;
        int i, j;

        width = height = radius * 2 + 1;
        xstart = x - radius;
        ystart = y - radius;

        if (x < radius) {
                width -= radius;
                xstart += radius;
        } else if (x + radius >= bmp->info_header.biWidth) {
                width -= (x + radius - bmp->info_header.biWidth + 1);
        }

        if (y < radius) {
                height -= radius;
                ystart += radius;
        } else if (y + radius >= bmp->info_header.biHeight) {
                height -= (y + radius - bmp->info_header.biHeight + 1);
        }

        r = malloc(sizeof(int) * width * height);
        g = malloc(sizeof(int) * width * height);
        b = malloc(sizeof(int) * width * height);

        for (i = 0; i < width; i++) {
                for (j = 0; j < height; j++) {
                        color = GetPointColor(bmp, i + xstart, j + ystart);
                        r[j * width + i] = color.r;
                        g[j * width + i] = color.g;
                        b[j * width + i] = color.b;
                }
        }

        sort(r, width * height);
        sort(g, width * height);
        sort(b, width * height);

        color.r = (uchar) r[radius];
        color.g = (uchar) g[radius];
        color.b = (uchar) b[radius];

        free(r);
        free(g);
        free(b);

        return color;
}


Bitmap MedianFilter(Bitmap bmp, int radius)
{
        Bitmap dest;
        int i, j;
        Color color;

        dest = CloneBmp(bmp);

        for (i = 0; i < bmp->info_header.biWidth; i++) {
                for (j = 0; j < bmp->info_header.biHeight; j++) {
                        color = GetMedianRGB(i, j, radius, bmp);
                        SetPointColor(dest, i, j, color);
                }
        }

        return dest;
}

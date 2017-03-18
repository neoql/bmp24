#include "bitmap.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Bitmap LoadBmp(char *path)
{
	Bitmap bmp;
	int fp;
	unsigned char *img;
	char buf[1024];
	int len;


	bmp = (Bitmap) malloc(sizeof(_Bitmap));
	fp = open(path, O_RDONLY);

	read(fp, &bmp->file_header.bfType, 2);
	read(fp, &bmp->file_header.bfSize, 4);
	read(fp, &bmp->file_header.bfReserved, 4);
	read(fp, &bmp->file_header.bfOffBits, 4);


	read(fp, &bmp->info_header.biSize, 4);
	read(fp, &bmp->info_header.biWidth, 4);
	read(fp, &bmp->info_header.biHeight, 4);
	read(fp, &bmp->info_header.biPlanes, 2);
	read(fp, &bmp->info_header.biBitCount, 2);
	read(fp, &bmp->info_header.biCompression, 4);
	read(fp, &bmp->info_header.biSizeImage, 4);
	read(fp, &bmp->info_header.biXPelsPerMeter, 4);
	read(fp, &bmp->info_header.biYPelsPerMeter, 4);
	read(fp, &bmp->info_header.biClrUsed, 4);
	read(fp, &bmp->info_header.biClrImportant, 4);

	img = (unsigned char*) malloc(bmp->info_header.biSizeImage);
	read(fp, img, bmp->info_header.biSizeImage);

	bmp->image = img;

	close(fp);
	return bmp;
}


Bitmap CloneBmp(Bitmap bmp)
{
	Bitmap new_bmp;
	uchar* img;

	new_bmp = malloc(sizeof(_Bitmap));
	img = malloc(bmp->info_header.biSizeImage);

	new_bmp->file_header = bmp->file_header;
	new_bmp->info_header = bmp->info_header;
	memcpy(img, bmp->image, bmp->info_header.biSizeImage);
	new_bmp->image = img;

	return new_bmp;
}


void DesdroyBmp(Bitmap bmp)
{
	free(bmp->image);
	free(bmp);
}


void PrintHeaders(Bitmap bmp)
{

	printf("-----------------File Header--------------------\n");
	printf("bfType: %s\n", (char*)&bmp->file_header.bfType);
	printf("bfSize: %d\n", bmp->file_header.bfSize);
	printf("bfReserved: %d\n", bmp->file_header.bfReserved);
	printf("bfOffBits: %d\n", bmp->file_header.bfOffBits);


	printf("-----------------Info Header--------------------\n");
	printf("biSize: %d\n", bmp->info_header.biSize);
	printf("biWidth: %d\n", bmp->info_header.biWidth);
	printf("biHeight: %d\n", bmp->info_header.biHeight);
	printf("biPlanes: %d\n", bmp->info_header.biPlanes);
	printf("biBitCount: %d\n", bmp->info_header.biBitCount);
	printf("biCompression: %d\n", bmp->info_header.biCompression);
	printf("biSizeImage: %d\n", bmp->info_header.biSizeImage);
	printf("biXPelsPerMeter: %d\n", bmp->info_header.biXPelsPerMeter);
	printf("biYPelsPerMeter: %d\n", bmp->info_header.biYPelsPerMeter);
	printf("biClrUsed: %d\n", bmp->info_header.biClrUsed);
	printf("biClrImportant: %d\n", bmp->info_header.biClrImportant);
}


Color GetPointColor(Bitmap bmp, unsigned int x, unsigned int y)
{
	Color color;
	int width, height;
	int line_index;
	uchar *p_img;
	char buf[5];

	width = bmp->info_header.biWidth;
	height = bmp->info_header.biHeight;
	p_img = bmp->image;

	line_index = (width * 3 + width % 4) * y;
	p_img += line_index;
	p_img += (x * 3);

	memcpy(buf, p_img, 3);

	color.r = p_img[2];
	color.g = p_img[1];
	color.b = p_img[0];

	return color;
}


void SetPointColor(Bitmap bmp, unsigned int x, unsigned int y, Color color)
{
	int line_index;
	int width, height;
	uchar *p_img;


	width = bmp->info_header.biWidth;
	height = bmp->info_header.biHeight;
	p_img = bmp->image;

	line_index = (width * 3 + width % 4) * y;
	p_img += line_index;
	p_img += (x * 3);

	p_img[2] = color.r;
	p_img[1] = color.g;
	p_img[0] = color.b;
}


void SaveBmp(Bitmap bmp, char* path)
{
	int fp;

	printf("%s\n", path);
	fp = open(path, O_WRONLY | O_CREAT);


	write(fp, &bmp->file_header.bfType, 2);
	write(fp, &bmp->file_header.bfSize, 4);
	write(fp, &bmp->file_header.bfReserved, 4);
	write(fp, &bmp->file_header.bfOffBits, 4);


	write(fp, &bmp->info_header.biSize, 4);
	write(fp, &bmp->info_header.biWidth, 4);
	write(fp, &bmp->info_header.biHeight, 4);
	write(fp, &bmp->info_header.biPlanes, 2);
	write(fp, &bmp->info_header.biBitCount, 2);
	write(fp, &bmp->info_header.biCompression, 4);
	write(fp, &bmp->info_header.biSizeImage, 4);
	write(fp, &bmp->info_header.biXPelsPerMeter, 4);
	write(fp, &bmp->info_header.biYPelsPerMeter, 4);
	write(fp, &bmp->info_header.biClrUsed, 4);
	write(fp, &bmp->info_header.biClrImportant, 4);

	write(fp, bmp->image, bmp->info_header.biSizeImage);

	close(fp);
}


void MkBmpGray(Bitmap bmp)
{
	int i, j;
	Color color;
	int gray;

	for (i = 0; i < bmp->info_header.biWidth; i++) {
		for (j = 0; j < bmp->info_header.biHeight; j++) {
			color = GetPointColor(bmp, i, j);
			gray = (color.r + color.g + color.b) / 3;
			color.r = gray;
			color.g = gray;
			color.b = gray;
			SetPointColor(bmp, i, j, color);
		}
	}
}



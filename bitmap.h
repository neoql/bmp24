#ifndef _BITMAP_H
#define _BITMAP_H


typedef unsigned char uchar;
typedef unsigned short WORD;
typedef unsigned int DWORD;

typedef struct {
	WORD bfType;
	DWORD bfSize;
	DWORD bfReserved;
	DWORD bfOffBits;

} FILE_HEADER;


typedef struct {
	DWORD biSize;
	DWORD biWidth;
	DWORD biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	DWORD biXPelsPerMeter;
	DWORD biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} INFO_HEADER;


typedef struct {
	FILE_HEADER file_header;
	INFO_HEADER info_header;
	unsigned char* image;
} *Bitmap, _Bitmap;


typedef struct {
	uchar r;
	uchar g;
	uchar b;
} Color;



Bitmap LoadBmp(char *path);
Bitmap CloneBmp(Bitmap bmp);
void DesdroyBmp(Bitmap bmp);
void PrintHeaders(Bitmap bmp);
Color GetPointColor(Bitmap bmp, int x, int y);
void SetPointColor(Bitmap bmp, unsigned int x, unsigned int y, Color color);
void SaveBmp(Bitmap bmp, char* path);
void MkBmpGray(Bitmap bmp);


#endif //_BITMAP_H


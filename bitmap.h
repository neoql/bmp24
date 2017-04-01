#ifndef _BITMAP_H
#define _BITMAP_H



#ifdef _WIN32
#ifdef libbmp24_EXPORTS
#define BMP_API __declspec(dllexport)
#else
#define BMP_API __declspec(dllimport)
#endif
#else
#define BMP_API
#endif


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



extern BMP_API Bitmap LoadBmp(char *path);
extern BMP_API Bitmap CloneBmp(Bitmap bmp);
extern BMP_API void DestroyBmp(Bitmap bmp);
extern BMP_API void PrintHeaders(Bitmap bmp);
extern BMP_API Color GetPointColor(Bitmap bmp, int x, int y);
extern BMP_API void SetPointColor(Bitmap bmp, unsigned int x, unsigned int y, Color color);
extern BMP_API void SaveBmp(Bitmap bmp, char* path);
extern BMP_API void MkBmpGray(Bitmap bmp);


#endif //_BITMAP_H


#include "bitmap.h"
#include "gaussian.h"
#include <stdlib.h>


int main(int argc, char* argv[])
{
	Bitmap bmp, dest;

	bmp = LoadBmp(argv[1]);
	PrintHeaders(bmp);

	dest = GsTrans(bmp, atof(argv[3]));

	SaveBmp(dest, argv[2]);

	PrintHeaders(dest);

    	DestroyBmp(bmp);
	DestroyBmp(dest);

	return 0;
}


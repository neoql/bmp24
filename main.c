#include <stdio.h>
#include "bitmap.h"
#include "gaussian.h"


int main(int argc, char* argv[])
{
	Bitmap bmp, dest;

	bmp = LoadBmp(argv[1]);
	dest = GsTrans(bmp, 2);

	SaveBmp(dest, argv[2]);

	DesdroyBmp(bmp);
	DesdroyBmp(dest);

	return 0;
}


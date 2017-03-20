#include "bitmap.h"
#include "gaussian.h"
#include <stdlib.h>


int main(int argc, char* argv[])
{
	Bitmap bmp, dest;

	bmp = LoadBmp(argv[1]);
	PrintHeaders(bmp);

	dest = GsTrans(bmp, 5);

	SaveBmp(dest, argv[2]);

	DesdroyBmp(bmp);
	DesdroyBmp(dest);

	return 0;
}


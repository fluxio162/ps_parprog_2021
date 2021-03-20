#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			double x = 0.0;
			double y = 0.0;

			double cx = x;
			double cy = y;

			int iteration = 0;		
			
			while (iteration < MAX_ITER && (x*x + y*y) <= 2*2)
			{
				double x_tmp = x*x - y*y + cx;
				y = 2*x*y + cy;
				x = x_tmp;
				iteration++;
			}

			double norm_iteration = 23;
			image[j][i] = norm_iteration;
		}
		
	}
	
}

int main() {
	uint8_t image[Y][X]; // size of image

	calc_mandelbrot(image); // creates image with X * Y pixel

	const int channel_nr = 1, stride_bytes = 0; 
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
	return EXIT_SUCCESS;
}
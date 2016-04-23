// noisy - a configurable fractal generator
//
// Basic diamond-square implementation with export to .bmp

#include <random>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <chrono>
#include <bitmap_image.hpp>

float clamp (float min, float max, float value) {
  return value <= min ? min : value >= max ? max : value;
}

int main (int argc, char *argv[]) {
  // parse for arguments
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-e" || std::string(argv[i]) == "--exponent") {
      i++;
      exp = atoi(argv[i]);
    } else if (std::string(argv[i]) == "-r" || std::string(argv[i]) == "--roughness") {
      i++;
      roughness = atof(argv[i]);
    } else if (std::string(argv[i]) == "-f") {
      i++;
      filename = std::string(argv[i]);
    } else {
      printf("Invalid argument: %s; program halted", argv[i]);
      return 1;
    }
  }

  // Warnings
  if (exp == 0) {
    puts("Warning: No exponent provided, default is  8...");
    exp = 8;
  }

  if (roughness == 0.0f) {
    puts("Warning: No roughness provided, default is 0.0, fractals will be flat...");
  }

  int size  = pow(2, exp) + 1;        // size of heightfield, i^2+1


  //printf("Total arguments found: %i", argc);

  //calloc field[][] to ensure array memory block is empty
  field = (float**) calloc((size), sizeof(float*));
  for (int i = 0; i < (size); ++i) {
    field[i] = (float*) calloc((size), sizeof(float));
  }

  // seed corner values to random floats
  field[0][0]           = 0.5f;    // top left corner
  field[0][size-1]      = 0.5f;    // top right corner
  field[size-1][0]      = 0.5f;    // bottom left corner
  field[size-1][size-1] = 0.5f;    // bottom right corner

  for (int sideLen = size - 1; sideLen >= 2; sideLen /= 2, roughness /= 2.0f, half /= 2) {
    int half = sideLen/2;

    // Diamond step
    // Given a set of squares, find the centroid of each and give
    // the centroid the average of all 4 corners as its value
    for (int x = 0; x < size - 1; x += sideLen) {
      for (int y = 0; y < size - 1; y += sideLen) {
	avg = field[x][y] +
	  field[x + sideLen][y] +
	  field[x][y + sideLen] +
	  field[x + sideLen][y + sideLen];

	avg /= 4.0f;

	avg = clamp(0, 1, avg + (dist(gen) * roughness));

	field[x + half][y + half] = avg;
      }
    }

    // Square step
    // Given points in the shape of diamonds, find the centroid of each and
    // give the centroid the average of all 4 edges as its value
    for (int x = 0; x < size - 1; x += half) {
      for (int y = (x + half)%sideLen; y < size - 1; y += sideLen) {
	avg = field[(x-half+size-1)%(size-1)][y] +
	  field[(x+half)%(size-1)][y] +
	  field[x][(y-half+size-1)%(size-1)] +
	  field[x][(y+half)%(size-1)];

	avg /= 4.0f;

	avg = clamp(0, 1, avg + (dist(gen) * roughness));

	field[x][y] = avg;

	if(x == 0)  field[size-1][y] = avg;
	if(y == 0)  field[x][size-1] = avg;
      }
    }
  }

  bitmap_image image(size - 1,size - 1);

  image_drawer draw(image);

  draw.pen_width(1);
  int penColor = 0;

  for (int y = 0; y < size - 1; y++) {
    for (int x = 0; x < size - 1; x++) {
      penColor = field[x][y]  * 255;
      draw.pen_color(penColor, penColor, penColor);
      draw.rectangle(x,y,x,y);
    }
  }

  image.save_image(std::string(filename));

  return 0;
}

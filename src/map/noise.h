#ifndef NOISE_H
#define NOISE_H

#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PERMUTATION_SIZE 256

// Function to generate a permutation array (i.e., an array of random numbers)
void generatePermutation();

// Fade function as defined by Ken Perlin
double fade(double t);

// Linear interpolation
double lerp(double t, double a, double b);

// Gradient function
double grad(int hash, double x, double y);

// 2D Perlin Noise function
double perlin2d(double x, double y);

#endif // NOISE_H

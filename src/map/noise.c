#include "noise.h"


int permutation[PERMUTATION_SIZE] = {0}; // Permutation array for noise generation

// Function to generate a permutation array (i.e., an array of random numbers)
void generatePermutation() {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < PERMUTATION_SIZE; i++) {
        permutation[i] = rand() % PERMUTATION_SIZE;
    }
}

// Fade function as defined by Ken Perlin
double fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

// Linear interpolation
double lerp(double t, double a, double b) {
    return a + t * (b - a);
}

// Gradient function
double grad(int hash, double x, double y) {
    int h = hash & 3;
    double u = h < 2 ? x : y;
    double v = h < 2 ? y : x;
    return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
}

// 2D Perlin Noise function
double perlin2d(double x, double y) {
    int xi = (int)x & 255;
    int yi = (int)y & 255;
    double xf = x - (int)x;
    double yf = y - (int)y;

    double u = fade(xf);
    double v = fade(yf);

    int aa = permutation[(permutation[xi] + yi) % PERMUTATION_SIZE];
    int ab = permutation[(permutation[xi] + yi + 1) % PERMUTATION_SIZE];
    int ba = permutation[(permutation[xi + 1] + yi) % PERMUTATION_SIZE];
    int bb = permutation[(permutation[xi + 1] + yi + 1) % PERMUTATION_SIZE];

    double x1, x2, y1;
    x1 = lerp(u, grad(aa, xf, yf), grad(ba, xf - 1, yf));
    x2 = lerp(u, grad(ab, xf, yf - 1), grad(bb, xf - 1, yf - 1));
    y1 = lerp(v, x1, x2);

    return (y1 + 1) / 2;
}

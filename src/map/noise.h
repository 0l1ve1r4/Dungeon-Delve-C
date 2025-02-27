// This file is part of DungeonDelveC.
// Copyright (C) 2024 - 2025 Guilherme Oliveira Santos

// DungeonDelveC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

/*
	Created on June 14th, 2023 by Ícaro Freire (https://github.com/ivfrere)
	Institute of Physics - University of São Paulo
	São Paulo, BRAZIL
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float* create_grid(int N) {
	float* grid;
	grid = malloc(sizeof(float) * pow(N, 2));
	for (int i = 0; i < N; i++) for(int j = 0; j < N; j++) grid[i * N + j] = 0.0f;
	return grid;
}

float laplacian(float* grid, int N, int i, int j) {
	float sum = 0.0f;
	sum += grid[( (N + (i+1 % N)) % N ) * N + j];
	sum += grid[( (N + (i-1 % N)) % N ) * N + j];
	sum += grid[ i * N + ((N + (j+1 % N)) % N)];
	sum += grid[ i * N + ((N + (j-1 % N)) % N)];
	return sum / 4.0f;
}

void iterate_grid(float* grid, float* bounds, int N) {
	for (int i = 0; i < N; i++) for(int j = 0; j < N; j++) if (bounds[ i * N + j ] == 0.0f) grid[ i * N + j ] = laplacian(grid, N, i, j);
}

void save_grid(float* grid, int N) {
	FILE* save = fopen("grid", "wb");
	fwrite(grid, sizeof(float), pow(N, 2), save);
	fclose(save);
}

void boundary(float* grid, float* bounds, int N) {
	for (int j = 0; j < N; j++) {
		grid[64 * N + j] = 100.0f;
		bounds[64 * N + j] = 1;

		grid[0 * N + j] = 0;
		bounds[0 * N + j] = 1;

		grid[127 * N + j] = 0;
		bounds[127 * N + j] = 1;

		grid[64 * N + 64] = 0.0f;
	}
}

int main(int argc, char* argv[]) {

	// Simulation parameters
	int N = 128;
	float L = 1;

	// Finite elements
	float dL = L / N;

	float* grid		= create_grid(N);
	float* bounds	= create_grid(N);

	boundary(grid, bounds, N);

	for (int t = 0; t < 1000; t++) {
		iterate_grid(grid, bounds, N);
	}

	save_grid(grid, N);

	return 0;
}
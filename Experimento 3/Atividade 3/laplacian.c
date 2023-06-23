/*
	Created on June 14th, 2023 by Ícaro Freire (https://github.com/ivfrere)
	Institute of Physics - University of São Paulo
	São Paulo, BRAZIL
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float* create_grid(int N) {
	float* grid = (float*) malloc(sizeof(float) * pow(N, 2));
	for (int i = 0; i < N; i++) for(int j = 0; j < N; j++) grid[i * N + j] = 0.0f;
	return grid;
}

void iterate_grid(float* grid, float* bounds, int N) {
	for (int i = 1; i < N - 1; i++)
		for(int j = 1; j < N - 1; j++)
			if (bounds[ i * N + j ] == 0.0f)
				grid[i*N+j] = ( grid[(i+1)*N+j] + grid[(i-1)*N+j] + grid[i*N+j+1] + grid[i*N+j-1] ) / 4.0f;
}

void save_grid(float* grid, int N) {
	FILE* save = fopen("grid", "wb");
	fwrite(grid, sizeof(float), pow(N, 2), save);
	fclose(save);
}

void set_cell(float* grid, int N, int i, int j, float v) { grid[i*N+j] = v;  }

void boundary(float* grid, float* bounds, int N, float dL) {
	int h = (int)(N/2);
	
	int d = (int)(1.4/dL);
	int x0 = (int)(15/dL);
	int y0 = h - (int)(d/2);
	
	
	
	int n = (int)(8/dL);
	for(int i = 0; i < n; i++) {
		set_cell(grid, N, y0, x0 + i, 1.0f);
		set_cell(bounds, N, y0, x0 + i, 1.0f);
		
		set_cell(bounds, N, y0 + d, x0 + i, 1.0f);
	}
	
	x0 += n;
	n = (int)(22/dL);
	for(int i = 0; i < n; i++) {
		int j = (int)(5*i/22);
		
		set_cell(grid, N, y0 - j, x0 + i, 1.0f);
		set_cell(bounds, N, y0 - j, x0 + i, 1.0f);
		
		set_cell(bounds, N, y0 + d + j, x0 + i, 1.0f);
	}
}

int main(int argc, char* argv[]) {

	// Simulation parameters
	int N = 4096;
	float L = 300;

	// Finite elements
	float dL = L / N;

	float* grid		= create_grid(N);
	float* bounds	= create_grid(N);

	boundary(grid, bounds, N, dL);
	for (int t = 0; t < 20000; t++) iterate_grid(grid, bounds, N);
	save_grid(grid, N);

	return 0;
}

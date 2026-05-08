#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define MAXCOL 255
#define PIXSTR 12
static const char *fname = "grid.ppm";

static const char *black = "000 000 000 ";
static const char *white = "255 255 255 ";
static const char *blue = "126 162 214 ";

typedef struct {
	uint8_t **data;
	size_t width;
	size_t height;
	size_t ppu;

	size_t x_origin;
	size_t y_origin;
} Grid;

void setcoor(Grid *grid, double x, double y);
void setpix(Grid *grid, signed int x, signed int y);

Grid *initGrid(size_t width, size_t height, size_t pixels_per_unit)
{
	Grid *grid = (Grid *)malloc(sizeof(Grid));
	grid->width = width;
	grid->height = height;
	grid->ppu = pixels_per_unit;
	grid->x_origin = width  >> 1;
	grid->y_origin = height >> 1;

	uint8_t **data = (uint8_t **)malloc(height * sizeof(uint8_t *));
	for (int i = 0; i < height; i++) {
		*(data + i) = (uint8_t *)malloc(PIXSTR * width * sizeof(uint8_t));

		for (int j = 0; j < width; j++) {

			if (i >= height / 2 - 1 && i <= height / 2 + 1 ||	/* x-axis */
			    j >= width  / 2 - 1 && j <= width  / 2 + 1 ||	/* y-axis */
			    (i - height / 2) % pixels_per_unit == 0 ||		/* horizontal bars */
			    (j - width  / 2) % pixels_per_unit == 0) {		/* vertical bars */
				strncpy(*(data + i) + j * PIXSTR, white, PIXSTR);
			} else {
				strncpy(*(data + i) + j * PIXSTR, black, PIXSTR);
			}
		}
	}
	grid->data = data;
	return grid;
}
void freeGrid(Grid *grid)
{
	for (int i = 0; i < grid->height; i++) {
		free(*(grid->data + i));
	}
	free(grid->data);
	free(grid);
}

void makeppm(Grid *grid)
{
	FILE *fp = fopen(fname, "w");
	fprintf(fp, "P3\n");
	fprintf(fp, "%d %d\n", grid->width, grid->height);
	fprintf(fp, "%d\n", MAXCOL);

	for (int i = 0; i < grid->height; i++) {
		fprintf(fp, "%s\n", *(grid->data + i));
	}
}

void linear(Grid *grid, double slope, double y_intercept)
{
	double x, y;
	for (int i = 0; i < grid->width; i++) {
		x = (i - (double)grid->x_origin) / (double)grid->ppu;
		y = slope * x + y_intercept;
		setcoor(grid, x, y);
	}
}
void quadratic(Grid *grid, double a, double b, double c)
{
	double x, y;
	for (int i = 0; i < grid->width; i++) {
		x = (i - (double)grid->x_origin) / (double)grid->ppu;
		y = a * x * x + b * x + c;
		setcoor(grid, x, y);
	}
}
void rational(Grid *grid, double vertical_asymptote, double horizontal_asymptote)
{
	double x, y;
	for (int i = 0; i < grid->width; i++) {
		x = (i - (double)grid->x_origin) / (double)grid->ppu;
		y = 1 / (x - vertical_asymptote) + horizontal_asymptote;
		setcoor(grid, x, y);
	}
}
void sine(Grid *grid, double amplitude, double period, double phase, double equilibrium)
{
	double x, y;
	for (int i = 0; i < grid->width; i++) {
		x = (i - (double)grid->x_origin) / (double)grid->ppu;
		y = amplitude * sin(period * x - phase * M_PI) + equilibrium;
		setcoor(grid, x, y);
	}
}

void circle(Grid *grid, double radius)
{
	double x, y;
	for (int i = 0; i < grid->width; i++) {
		x = (i - (double)grid->x_origin) / (double)grid->ppu;
		y = sqrt(radius * radius - x * x);
		setcoor(grid, x, y);
	}
	for (int i = 0; i < grid->width; i++) {
		x = (i - (double)grid->x_origin) / (double)grid->ppu;
		y = -sqrt(radius * radius - x * x);
		setcoor(grid, x, y);
	}
}
void ellipse(Grid *grid, double xpos, double ypos, double semi_major, double semi_minor)
{
	double x, y;
	for (int i = 0; i < grid->width; i++) {
		x = (i - (double)grid->x_origin) / (double)grid->ppu;
		y = (semi_minor / semi_major) * sqrt(semi_major * semi_major - (x - xpos) * (x - xpos)) + ypos;
		setcoor(grid, x, y);
	}
	for (int i = 0; i < grid->width; i++) {
		x = (i - (double)grid->x_origin) / (double)grid->ppu;
		y = -(semi_minor / semi_major) * sqrt(semi_major * semi_major - (x - xpos) * (x - xpos)) + ypos;
		setcoor(grid, x, y);
	}
}

void setcoor(Grid *grid, double x, double y)
{
	setpix(grid, (int)(x * (double)grid->ppu), (int)(y * (double)grid->ppu));
}
void setpix(Grid *grid, signed int x, signed int y) 
{
	if (x + grid->x_origin > grid->width  - 1 || x + grid->x_origin < 0 ||
	    y + grid->y_origin > grid->height - 0 || y + grid->y_origin < 1) {
		return;
	}
	strncpy(*(grid->data + grid->height - (y + grid->y_origin)) + (x + grid->x_origin) * PIXSTR, blue, PIXSTR);
}

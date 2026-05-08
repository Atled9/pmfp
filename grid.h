#ifndef GRID
#define GRID

#include <stddef.h>
#include <stdint.h>

typedef struct Grid Grid;

Grid *initGrid(size_t width, size_t height, size_t pixels_per_unit);
void freeGrid(Grid *grid);

void makeppm(Grid *grid);

void linear(Grid *grid, double slope, double y_intercept);
void quadratic(Grid *grid, double a, double b, double c);
void rational(Grid *grid, double vertical_asymptote, double horizontal_asymptote);
void sine(Grid *grid, double amplitude, double period, double phase, double equilibrium);

void circle(Grid *grid, double radius);
void ellipse(Grid *grid, double xpos, double ypos, double semi_major, double semi_minor);

#endif

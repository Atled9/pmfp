#include "grid.h"

#define W_RATIO 16
#define H_RATIO 9
#define FACTOR	64
#define PIXELS_PER_UNIT 64

int main()
{
	Grid *grid = initGrid(FACTOR * W_RATIO, FACTOR * H_RATIO, PIXELS_PER_UNIT);

	/* Example plot */
	sine(grid, 1, 1, 0, 3.5);
	sine(grid, 1, 1.5, 0.5, -3.5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			ellipse(grid, j - 4, i - 2, 1, 0.5);
		}
	}
	/* End Example */

	makeppm(grid);
	freeGrid(grid);
	return 0;
}

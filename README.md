## Pixel Map Function Plotter

Graph any given function within a portable pixel map (.ppm) image

![.ppm graph example](images_for_README/grid.png)

## How to Use

* Set the image properties for the grid at the top of `main()`
* Premade functions can be found toward the bottom half of `grid.h` (red box)

![grid header with premade functions in box](images_for_README/grid_header_with_box.png)

* Call your chosen function in `main()` and define its properties within the arguments
* You can call more than one function for the plot
* Compile the binary `<gcc clang your_compiler> main.c grid.c -lm -o main`
* Run the binary `./main` 
* Now your will have your pixelmap image, the default name is "grid.ppm"

## Build Your Own Function

// g++ -Wall -pedantic src/main.cpp src/graphics.cpp src/loop.cpp -lSDL2 -lSDL2_ttf
#include <iostream>
#include "test.h"
// #include "loop.h"
#include "rtree.h"
#include "graphics.h"
#include "experiments.h"

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 850
#define FONT "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
// #define TEST
// #define EXPERIMENT

int main() {
  #ifdef TEST
    run_tests();
    return EXIT_SUCCESS;
  #endif // TEST

  #ifdef EXPERIMENT
    run_experiments();
    return EXIT_SUCCESS;
  #endif // TEST

  CGraphics* graphics = new CGraphics(WINDOW_WIDTH, WINDOW_HEIGHT, FONT);
    
  CLoop main_loop(graphics);
  main_loop.menu_loop();
    
  delete graphics;

  return EXIT_SUCCESS;
}
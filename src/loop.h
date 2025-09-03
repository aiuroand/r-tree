#ifndef LOOP_H
#define LOOP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cctype>
#include <cmath>
#include <cassert>
#include <string>
#include <random>
#include <sstream>
#include <chrono>
#include <filesystem>
#include "object.h"
#include "graphics.h"
#include "rtree.h"
#include "helping.h"
#include "brute_force.h"
#include "index.h"

#define INTERFACE_Y 200
#define INTERFACE_X 100
#define SAVES_DIR "saves/"
#define BASE_RANDOM_NUMBER 0
#define BASE_DELAY 0

class CLoop {
  CGraphics* m_Graphics;
  SDL_Color c_Black  = {0, 0, 0, 255};
  SDL_Color c_White  = {255, 255, 255, 255};
  SDL_Color c_Gray   = {128, 128, 128, 255};
  SDL_Color c_Green  = {0, 255, 0, 255};
  SDL_Color c_Blue   = {0, 0, 255, 255};
  SDL_Color c_Yellow = {255, 255, 0, 255};
  SDL_Color c_Red    = {200, 0, 0, 255};
  SDL_Color c_Orange = {225, 165, 0, 255};
public:
  CLoop(CGraphics* graphics) : m_Graphics(graphics) {}
  void menu_loop (void);
  void new_loop (void);
  void save_loop (void);
  void rtree_loop (CIndex* index, int randomNumber, int delay, bool axes, bool visualize, bool print);

};

#endif //LOOP_H
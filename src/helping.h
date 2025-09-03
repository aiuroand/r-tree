#ifndef HELPING_H
#define HELPING_H

#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <numeric> 
#include <chrono> 
#include <iomanip> 
#include "object.h"



bool inside(const SDL_Rect& rect, int x, int y);
CPoint parseCoordinates(int dimension, const std::string& str);
double euclideanDistance(const CPoint& a, const CPoint& b);
double pointRectDist(const CPoint& p, const CBoundaries& boundaries);
std::string getCurrentTimeString();

#endif // HELPING_H
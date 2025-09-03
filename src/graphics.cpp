#include "graphics.h"

CGraphics::CGraphics(int w, int h, const char* font)
  : m_Width(w), m_Height(h) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "SDL_Init error Error: %s\n", SDL_GetError());
    throw std::bad_alloc();
  }
  
  m_Window = SDL_CreateWindow("R-tree!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
  if (m_Window == nullptr) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    throw std::bad_alloc();
  }
  
  m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (m_Renderer == nullptr) {
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
    throw std::bad_alloc();
  }
  
  if (TTF_Init() == -1) {
    fprintf(stderr, "TTF_Init Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    SDL_Quit();
    throw std::bad_alloc();
  }
  
  m_Font = TTF_OpenFont(font, FONT_SIZE);
  if (font == nullptr) {
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    SDL_Quit();
    TTF_Quit();
    throw std::bad_alloc();
  }
}

CGraphics::~CGraphics() {
  SDL_DestroyWindow(m_Window);
  SDL_DestroyRenderer(m_Renderer);
  TTF_CloseFont(m_Font);
  SDL_Quit();
  TTF_Quit();
}

void CGraphics::renderText(const CText& text) {
  SDL_Surface* surface = TTF_RenderText_Solid(m_Font, text.m_Text.c_str(), text.m_TextColor);
  if (!surface) { 
    fprintf(stderr, "SDL_Surface error: %s\n", SDL_GetError());
    return;
  }
  
  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
  if (!texture) {
    SDL_FreeSurface(surface);
    fprintf(stderr, "SDL_Surface error: %s\n", SDL_GetError());
    return;
  }
  int w = surface->w;
  int h = surface->h;

  SDL_Rect sRect = {text.m_Rectangle.x, text.m_Rectangle.y, w, h};
  SDL_RenderCopy(m_Renderer, texture, nullptr, &sRect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void CGraphics::renderButton (const CButton& button) {
  SDL_SetRenderDrawColor(m_Renderer, button.m_Color.r, button.m_Color.g, button.m_Color.b, button.m_Color.a);
  SDL_RenderFillRect(m_Renderer, &button.m_Rectangle);

  SDL_SetRenderDrawColor(m_Renderer, button.m_FrameColor.r, button.m_FrameColor.g, button.m_FrameColor.b, button.m_FrameColor.a);
  SDL_RenderDrawRect(m_Renderer, &button.m_Rectangle);

  renderText(CText(SDL_Rect({button.m_Rectangle.x + 2, button.m_Rectangle.y + 2, 0, 0}), button.m_TextColor, button.m_Text.empty() ? " " : button.m_Text));
}    

void CGraphics::renderCheckBox (const CCheckBox& checkBox) {
  SDL_SetRenderDrawColor(m_Renderer, checkBox.m_Color.r, checkBox.m_Color.g, checkBox.m_Color.b, checkBox.m_Color.a);
  SDL_RenderFillRect(m_Renderer, &checkBox.m_Rectangle);

  SDL_SetRenderDrawColor(m_Renderer, checkBox.m_FrameColor.r, checkBox.m_FrameColor.g, checkBox.m_FrameColor.b, checkBox.m_FrameColor.a);
  SDL_RenderDrawRect(m_Renderer, &checkBox.m_Rectangle);

  if (checkBox.m_Status) {
    SDL_SetRenderDrawColor(m_Renderer, checkBox.m_FrameColor.r, checkBox.m_FrameColor.g, checkBox.m_FrameColor.b, checkBox.m_FrameColor.a);
    SDL_Rect tmp({checkBox.m_Rectangle.x + 2, checkBox.m_Rectangle.y + 2, checkBox.m_Rectangle.w - 4, checkBox.m_Rectangle.h - 4});
    SDL_RenderFillRect(m_Renderer, &tmp);
  }
}

void CGraphics::renderCircle(int x, int y, int r, const SDL_Color& color)
{
  SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, 255);
  int diameter = r * 2;
  int x_new = r - 1;
  int y_new = 0;
  int tx = 1;
  int ty = 1;
  int error = tx - diameter;

  while (x_new >= y_new)
  {
    SDL_RenderDrawPoint(m_Renderer, x + x_new, y - y_new);
    SDL_RenderDrawPoint(m_Renderer, x + x_new, y + y_new);
    SDL_RenderDrawPoint(m_Renderer, x - x_new, y - y_new);
    SDL_RenderDrawPoint(m_Renderer, x - x_new, y + y_new);
    SDL_RenderDrawPoint(m_Renderer, x + y_new, y - x_new);
    SDL_RenderDrawPoint(m_Renderer, x + y_new, y + x_new);
    SDL_RenderDrawPoint(m_Renderer, x - y_new, y - x_new);
    SDL_RenderDrawPoint(m_Renderer, x - y_new, y + x_new);
    if (error <= 0)
    {
      ++y_new;
      error += ty;
      ty += 2;
    }
    if (error > 0)
    {
      --x_new;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void CGraphics::renderLine(int x1, int y1, int x2, int y2, const SDL_Color& color) {
  SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, 255);
  SDL_RenderDrawLine(m_Renderer, x1, y1, x2, y2);
}

void CGraphics::renderRectangle (const SDL_Rect& rect, const SDL_Color& color) {
  SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, 255);
  SDL_RenderFillRect(m_Renderer, &rect);
}

void CGraphics::renderRectangle (const CBoundaries& boundaries, const SDL_Color& color) {
  SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, 255);
  SDL_Rect tmp = SDL_Rect({static_cast<int>(boundaries.m_BottomLeft.m_Coordinates[0]),
    static_cast<int>(boundaries.m_TopRight.m_Coordinates[1]),
    static_cast<int>(boundaries.m_TopRight.m_Coordinates[0] - boundaries.m_BottomLeft.m_Coordinates[0]),
    static_cast<int>(boundaries.m_TopRight.m_Coordinates[1] - boundaries.m_BottomLeft.m_Coordinates[1])
    });
  SDL_RenderFillRect(m_Renderer, &tmp);
}
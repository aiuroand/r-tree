#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <exception>
#include <iostream>
#include "object.h"
#define FONT_SIZE 15

struct CObject{
  CObject (const SDL_Rect& rect) 
    : m_Rectangle(rect){}
  SDL_Rect m_Rectangle;
};


struct CButton : CObject{
  CButton (const SDL_Rect& rect, const SDL_Color& color, const SDL_Color& frameColor, const SDL_Color& textColor, const std::string& text) 
    : CObject(rect),
      m_Color(color),
      m_FrameColor(frameColor),
      m_TextColor(textColor),
      m_Text(text)
  {}
  SDL_Color m_Color;
  SDL_Color m_FrameColor;
  SDL_Color m_TextColor;
  std::string m_Text;
};

struct CText : CObject{
  CText (const SDL_Rect& rect, const SDL_Color& textColor, const std::string& text) 
  : CObject(rect),
    m_TextColor(textColor),
    m_Text(text)
  {}
  SDL_Color m_TextColor;
  std::string m_Text;
};

struct CCheckBox : CObject{
  CCheckBox (const SDL_Rect& rect, const SDL_Color& color, const SDL_Color& frameColor, bool status) 
  : CObject(rect),
    m_Color(color),
    m_FrameColor(frameColor),
    m_Status(status)
  {}

  SDL_Color m_Color;
  SDL_Color m_FrameColor;
  bool m_Status;
};

class CGraphics {
  int m_Width;
  int m_Height;
  SDL_Renderer *m_Renderer = nullptr;
  SDL_Window *m_Window = nullptr;
  TTF_Font* m_Font = nullptr;

public:
  CGraphics(int w, int h, const char* font);
  ~CGraphics();
  void renderText(const CText& str);
  void renderButton (const CButton& button);
  void renderCheckBox (const CCheckBox& checkBox);
  void renderCircle (int x, int y, int r, const SDL_Color& color);
  void renderLine (int x1, int y1, int x2, int y2, const SDL_Color& color);
  void renderRectangle (const SDL_Rect& rect, const SDL_Color& color);
  void renderRectangle (const CBoundaries& rect, const SDL_Color& color);
  std::pair<int, int> getWindowSize(void) {
    int W, H;
    SDL_GetWindowSize(m_Window, &W, &H);
    return {W, H};
  }
  void render (void) {SDL_RenderPresent(m_Renderer);}
  void clear (void) {SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255); SDL_RenderClear(m_Renderer);}

};
#endif // GRAPHICS_H
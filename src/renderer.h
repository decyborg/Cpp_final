#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <string>
#include "SDL_ttf.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void RenderSplashInit();
  void RenderSplash(const int& max_score,
                    const std::string& player_max_score,
                    const std::string& cur_player);
  void UpdateWindowTitle(int score, int fps);

  SDL_Renderer *sdl_renderer;
 private:
  SDL_Window *sdl_window;
  TTF_Font* font;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif

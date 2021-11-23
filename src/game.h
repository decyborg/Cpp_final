#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

#include <string>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void SplashScreen(Controller const &controller, Renderer &renderer);
  void EndGame(void);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int max_score_{0};

  // File were information about the game is stored
  const std::string game_file_{"snake_data.txt"};
  std::string player_name_{"?"};

  void PlaceFood();
  void Update();
};

#endif

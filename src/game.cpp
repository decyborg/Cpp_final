#include "game.h"
#include <iostream>
#include "SDL.h"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace
{
// Parses the game file to get the max_score so far and the player that got it
// param[in] filename Name of the game file (with expected format).
// param[out] max_score Max score stored on the file.
// param[out] player Name of the player stored in the file.
// returns true if it succeeds to read the file and data, false otherwise
bool parse_game_file(const std::string& filename, int& max_score, std::string& player)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cout << "Couldn't open file " << filename << std::endl;
        return false;
    }
    std::string tmp_str;
    std::getline(file, tmp_str);
    std::istringstream str_stream(tmp_str);
    std::string tmp_name;
    int tmp_score;
    if(!(str_stream >> tmp_name >> tmp_score))
    {
        std::cout << "Couldn't parse file" << std::endl;
        return false;
    }

    return true;
}

} // Anonymous namespace

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

/// Displays an initial screen to select the name of player
/// @param[in] controller A reference to the controller object
/// @param[in] renderer A reference to the renderer object
void Game::SplashScreen(Controller const &controller, Renderer &renderer)
{

    // Check if file already exists
    if(std::filesystem::exists(game_file_))
    {
        // Load file if it exists
        if(!parse_game_file(game_file_, max_score_, player_name_))
        {
            std::cout << "Could not open and parse " << game_file_ << std::endl;
        }
    }
    else
    {
        std::cout << game_file_ << " doesn't exist, using defaults" << std::endl;
    }

    // Render max score to date and get current player name
    std::string tmp_player{};
    renderer.RenderSplash(max_score_, player_name_, tmp_player);
    SDL_Delay(10000);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::EndGame()
{
    // Save current game
    // Only update if score beats max score
    if(score > max_score_)
    {
        // Overwrite previous score
        std::ofstream outfile;
        outfile.open(game_file_, std::ios_base::out | std::ios_base::trunc);
        if(outfile.is_open())
        {
            outfile << player_name_ << " " << score << std::endl;
        }
        else
        {
            std::cout << "Couldn't open file to save game results!" << std::endl;
        }
    }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }


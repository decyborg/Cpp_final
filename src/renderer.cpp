#include "renderer.h"
#include <iostream>
#include <sstream>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

/// Renders text to a renderer object but does not displays it
/// param[in] str String to display
/// param[in] font Font to use
/// param[in] renderer_ to render text to
/// param[in] offset Offset at which to display the text
/// param[in] color Color to display text
/// returns last height at which text was displayed (to use for next offset)
int RenderText(const char* str, TTF_Font* font, SDL_Renderer* renderer_, const int& offset, const SDL_Color& color)
{
    SDL_Surface* text = TTF_RenderText_Solid(font, str, color);
    if(!text)
    {
        std::cout << "Failed to render text: " << str << " " << TTF_GetError() << std::endl;
    }
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer_, text);
    SDL_Rect dest = { 0, offset, text->w, text->h};
    SDL_RenderCopy(renderer_, text_texture, nullptr, &dest);

    return text->h;
}

void Renderer::RenderSplashInit()
{
    if(TTF_Init() < 0)
    {
        std::cout << "Error initializing SDL TTF: " << TTF_GetError() << "\n";
    }

    // Load font
	font = TTF_OpenFont("../support/font.ttf", 56);
	if ( !font )
    {
        std::cout << "Error loading font: " << TTF_GetError() << "\n";
	}
}

/// Render the splash screen name
///
void Renderer::RenderSplash(const int& max_score, const std::string& player_max_score, const std::string& cur_player)
{
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Set color to black
    SDL_Color color = { 0xFF, 0xFF, 0xFF };

    // First section of Splash Screen
    std::stringstream ss;
    ss << "Max score: " << max_score << " ";
    std::string tmp_str = ss.str();
    int offset = RenderText(tmp_str.c_str(), font, sdl_renderer, 0, color);
    ss.str(std::string());
    ss << "Player: " << player_max_score;
    tmp_str = ss.str();
    offset += RenderText(tmp_str.c_str(), font, sdl_renderer, offset, color);

    // Middle Section
    offset += RenderText("Insert your name:", font, sdl_renderer, offset, color);
    if(cur_player.size())
    {
        offset += RenderText(cur_player.c_str(), font, sdl_renderer, offset, color);
    }
    else
    {
        offset += RenderText(" ", font, sdl_renderer, offset, color);
    }

    // End section
    offset += RenderText("Press enter to continue", font, sdl_renderer, offset, color);

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

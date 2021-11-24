#pragma once

#include <chrono>
#include <SDL.h>
#include <random>
#include "game_object.h"
#include "snake.h"

enum class food_state
{
    bonus,
    damage,
};

// Bonus Food object
// Allows the snake to grow with random multipliers
class BonusFood final: public GameObject
{
public:
    // Constructor of the BonusFood object
    // takes the maximum multiplier value
    explicit BonusFood(std::size_t w, std::size_t h, int max_multiplier);
    BonusFood() = delete;
    ~BonusFood() = default;

    // Render the object
    void Render(SDL_Renderer* sdl_renderer, SDL_Rect& block) override;

    // Updates the BonusFood multiplier value and location
    void Update(void) override;

    // Update the location of the bonus food
    void Place(Snake& snake, SDL_Point& food);

    // Check if there is a collision with the point
    bool Collision(int& x, int& y);

    // Get the multiplier value for the bonus food
    int get_multiplier();

    // Get the food state
    food_state get_state(){return state_;};
private:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
    std::uniform_int_distribution<int> random_m_pos;
    std::uniform_int_distribution<int> random_m_neg;
    std::uniform_int_distribution<int> random_interval;

    std::chrono::steady_clock::time_point start_;
    std::chrono::milliseconds interval_{1000};

    SDL_Point location_;
    // RGBA
    SDL_Color color_{0x00, 0x00, 0xFF, 0xFF};
    int max_multiplier_;
    int multiplier_;
    food_state state_{food_state::bonus};
    std::size_t w_;
    std::size_t h_;

    // Internal function to toggle the state of the bonus
    void ToggleState();
    // Internal function to update the color of the food
    void UpdateColor();
};

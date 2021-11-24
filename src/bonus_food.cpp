#include "bonus_food.h"


BonusFood::BonusFood(std::size_t w, std::size_t h, int max_multiplier) :
                    w_(w),
                    h_(h),
                    max_multiplier_(max_multiplier),
                    engine(dev()),
                    random_w(0, static_cast<int>(w - 1)),
                    random_h(0, static_cast<int>(h - 1)),
                    random_m_neg(-max_multiplier, 0),
                    random_m_pos(0, max_multiplier),
                    random_interval(1000, 3000)
{
    start_ = std::chrono::steady_clock::now();
}


int BonusFood::get_multiplier()
{
    int multiplier{0};

    switch(state_)
    {
        case food_state::bonus:
            multiplier = random_m_pos(engine);
            break;
        case food_state::damage:
            multiplier = random_m_neg(engine);
            break;
    }
    return multiplier;
}

bool BonusFood::Collision(int& x, int& y)
{
    if(x == location_.x && y == location_.y)
    {
        return true;
    }

    return false;
}

void BonusFood::Place(Snake& snake, SDL_Point& food)
{
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!snake.SnakeCell(x, y) && food.x != x && food.y != y)
        {
            location_.x = x;
            location_.y = y;
            return;
        }
  }
}

void BonusFood::Render(SDL_Renderer* sdl_renderer, SDL_Rect& block)
{
  SDL_SetRenderDrawColor(sdl_renderer, color_.r, color_.g, color_.b, color_.a);
  block.x = location_.x * block.w;
  block.y = location_.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
}

void BonusFood::UpdateColor()
{
    switch(state_)
    {
        case food_state::bonus:
            // Set blue color to signal bonus state
            color_.r = 0x00;
            color_.b = 0xFF;
            break;
        case food_state::damage:
            // Set red color to signal damage state
            color_.r = 0xFF;
            color_.b = 0x00;
            break;

    }
}

void BonusFood::ToggleState()
{
    // Switch state
    switch(state_)
    {
        case food_state::bonus:
            state_ = food_state::damage;
            break;
        case food_state::damage:
            state_ = food_state::bonus;
            break;
    }

    // Update color
    UpdateColor();
}

void BonusFood::Update(void)
{
    // Toggle state at random intervals
    if(std::chrono::steady_clock::now() - start_ >= interval_)
    {
        ToggleState();
        interval_ = static_cast<std::chrono::milliseconds>(random_interval(engine));
        start_ = std::chrono::steady_clock::now();
    }
}

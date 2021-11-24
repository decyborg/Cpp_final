#pragma once

// An abstract class that defines the basic interface
// of a Game Object
class GameObject{
public:
    //GameObject() = default;
    //virtual ~GameObject() = default;
    virtual void Render(SDL_Renderer* sdl_renderer, SDL_Rect& block) = 0;

    virtual void Update(void) = 0;
private:
};

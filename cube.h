#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

using namespace std;

class Screen {
public:
  SDL_Event e;
  SDL_Window *window;
  SDL_Renderer *render;
  vector<SDL_FPoint> points;

  Screen() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640 * 2, 480 * 2, 0, &window, &render);
    SDL_RenderSetScale(render, 2, 2);
  }

  void pixel(float x, float y) { points.emplace_back(x, y); }
  void show() {
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    for (auto &point : points) {
      SDL_RenderDrawPoint(render, point.x, point.y);
    }
    SDL_RenderPresent(render);
  }

  void clear() { points.clear(); }

  void input() {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        SDL_Quit();
        exit(0);
      }
    }
  }
};

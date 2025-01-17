#include "Game.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <stdio.h>

int main() {
  Game g = Game();
  g.run();
  return 0;
}

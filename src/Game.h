#ifndef GAME_H
#define GAME_H

class SDL_Window;
class SDL_Renderer;

class Game {
public:
  Game();
  bool init();
  bool loadMedia();
  void close();
  void run();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif

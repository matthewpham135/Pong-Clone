#ifndef GAME_H
#define GAME_H

#include <SDL_mixer.h>
class SDL_Window;
class SDL_Renderer;
class TTF_Font;
typedef struct SDL_Texture SDL_Texture;
#include <string>

class Game {
public:
  Game();
  bool init();
  bool loadMedia();
  SDL_Texture *renderText(std::string message);
  void close();
  void run();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *score1Texture;
  SDL_Texture *score2Texture;
  TTF_Font *gameFont;
  Mix_Chunk *hitSound;
};

#endif

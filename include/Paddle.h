#ifndef PADDLE_H
#define PADDLE_H
#include "Global.h"
#include <SDL_rect.h>
typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;

class Paddle {
public:
  static const int PADDLE_WIDTH = 10;
  static const int PADDLE_HEIGHT = SCREEN_HEIGHT / 6;
  static const int PADDLE_VEL = 350;
  Paddle(int id);
  void handleEvent(SDL_Event &e);
  void move(float timeStep);
  void render(SDL_Renderer *renderer);
  SDL_Rect mCollider;

private:
  int playerId;
  float mPosX, mPosY;
  float mVelY;
};

#endif

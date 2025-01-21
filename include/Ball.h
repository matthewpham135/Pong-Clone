#ifndef BALL_H
#define BALL_H

#include <SDL_rect.h>
typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

class Ball {
public:
  static const int BALL_WIDTH = 20;
  static const int BALL_HEIGHT = 20;
  static const int BALL_VEL = 350;
  Ball(SDL_Renderer *renderer);
  void move(float timeStep, SDL_Rect wall1, SDL_Rect wall2);
  void render(SDL_Renderer *renderer);
  void loadFromFile(SDL_Renderer *renderer);
  bool checkCollision(SDL_Rect a, SDL_Rect b);
  void reset();

private:
  float mPosX, mPosY;
  float mVelX, mVelY;
  SDL_Texture *ballTexture;
  SDL_Rect mCollider;
};

#endif

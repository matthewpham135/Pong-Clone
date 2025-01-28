#ifndef BALL_H
#define BALL_H
#define NO_SCORE 0
#define PLAYER_1_SCORES 1
#define PLAYER_2_SCORES 2
#define PADDLE_HIT 3
#define MAX_BOUNCE_ANGLE 60 * (M_PI / 180.0f)
#include <SDL_rect.h>
typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

class Ball {
public:
  static const int BALL_WIDTH = 20;
  static const int BALL_HEIGHT = 20;
  static const int BALL_VEL = 400;
  Ball(SDL_Renderer *renderer);
  int move(float timeStep, SDL_Rect wall1, SDL_Rect wall2);
  void render(SDL_Renderer *renderer);
  bool checkCollision(SDL_Rect a, SDL_Rect b);
  void reset();

private:
  float mPosX, mPosY;
  float mVelX, mVelY;
  SDL_Rect mCollider;
};

#endif

#include "Ball.h"
#include "Global.h"
#include "Paddle.h"
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <string>

Ball::Ball(SDL_Renderer *renderer) {
  mPosX = int(SCREEN_WIDTH / 2) - int(BALL_WIDTH / 2);
  mPosY = int(SCREEN_HEIGHT / 2) - int(BALL_HEIGHT / 2);
  mVelX = -BALL_VEL;
  mVelY = BALL_VEL;
  mCollider.x = mPosX;
  mCollider.y = mPosY;
  mCollider.h = BALL_HEIGHT;
  mCollider.w = BALL_WIDTH;
}
int Ball::move(float timeStep, SDL_Rect wall1, SDL_Rect wall2) {
  mPosX += mVelX * timeStep;
  if (mPosX < 0) {
    reset();
    return PLAYER_2_SCORES;
  }
  if (mPosX >= SCREEN_WIDTH - BALL_WIDTH) {
    reset();
    return PLAYER_1_SCORES;
  }
  mPosY += mVelY * timeStep;
  if (mPosY < 0) {
    mPosY = 0;
    mVelY *= -1;
  } else if (mPosY > SCREEN_HEIGHT - BALL_HEIGHT) {
    mPosY = SCREEN_HEIGHT - BALL_HEIGHT;
    mVelY *= -1;
  }
  if (checkCollision(mCollider, wall1)) {
    mPosX = wall1.x + wall1.w;
    mVelX *= -1;
  }
  if (checkCollision(mCollider, wall2)) {
    mPosX = wall2.x - BALL_WIDTH;
    mVelX *= -1;
  }
  mCollider.x = mPosX;
  mCollider.y = mPosY;
  return NO_SCORE;
}

void Ball::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xE0, 0xE0, 0xE0, 0xBF);
  SDL_Rect ballRect = {int(mPosX), int(mPosY), BALL_WIDTH, BALL_HEIGHT};
  SDL_RenderFillRect(renderer, &ballRect);
}

bool Ball::checkCollision(SDL_Rect a, SDL_Rect b) {
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;
  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;
  if (bottomA <= topB) {
    return false;
  }

  if (topA >= bottomB) {
    return false;
  }

  if (rightA <= leftB) {
    return false;
  }

  if (leftA >= rightB) {
    return false;
  }

  return true;
}

void Ball::reset() {
  mPosX = int(SCREEN_WIDTH / 2) - int(BALL_WIDTH / 2);
  mPosY = int(SCREEN_HEIGHT / 2) - int(BALL_HEIGHT / 2);
  mVelX = -BALL_VEL;
  mVelY = BALL_VEL;
  mCollider.x = mPosX;
  mCollider.y = mPosY;
}

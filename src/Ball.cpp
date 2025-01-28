#include "Ball.h"
#include "Global.h"
#include "Paddle.h"
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <cmath>

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
  bool hit = false;
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
    hit = true;
  } else if (mPosY > SCREEN_HEIGHT - BALL_HEIGHT) {
    mPosY = SCREEN_HEIGHT - BALL_HEIGHT;
    mVelY *= -1;
    hit = true;
  }
  if (checkCollision(mCollider, wall1)) {
    float relativeIntersectY = (wall1.y + (float(Paddle::PADDLE_HEIGHT) / 2)) -
                               (mPosY + (float(BALL_HEIGHT) / 2));
    float normalizedRelativeIntersectionY =
        (relativeIntersectY / (float(Paddle::PADDLE_HEIGHT) / 2));
    float bounceAngle = normalizedRelativeIntersectionY * MAX_BOUNCE_ANGLE;
    mPosX = wall1.x + wall1.w;
    mVelX = BALL_VEL * cos(bounceAngle);
    mVelY = BALL_VEL * sin(bounceAngle);
    hit = true;
  }
  if (checkCollision(mCollider, wall2)) {
    float relativeIntersectY = (wall2.y + (float(Paddle::PADDLE_HEIGHT) / 2)) -
                               (mPosY + (float(BALL_HEIGHT) / 2));
    float normalizedRelativeIntersectionY =
        (relativeIntersectY / (float(Paddle::PADDLE_HEIGHT) / 2));
    float bounceAngle = normalizedRelativeIntersectionY * MAX_BOUNCE_ANGLE;
    mPosX = wall2.x - BALL_WIDTH - 1;
    mVelX = -1 * BALL_VEL * cos(bounceAngle);
    mVelY = BALL_VEL * sin(bounceAngle);
    hit = true;
  }
  mCollider.x = mPosX;
  mCollider.y = mPosY;
  if (hit) {
    return PADDLE_HIT;
  }
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

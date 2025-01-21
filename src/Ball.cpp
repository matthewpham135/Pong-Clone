#include "Ball.h"
#include "Global.h"
#include "Paddle.h"
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include <string>

Ball::Ball(SDL_Renderer *renderer) {
  mPosX = int(SCREEN_WIDTH / 2) - int(BALL_WIDTH / 2);
  mPosY = int(SCREEN_HEIGHT / 2) - int(BALL_HEIGHT / 2);
  mVelX = -BALL_VEL;
  mVelY = BALL_VEL;
  loadFromFile(renderer);
  mCollider.x = mPosX;
  mCollider.y = mPosY;
  mCollider.h = BALL_HEIGHT;
  mCollider.w = BALL_WIDTH;
}
void Ball::move(float timeStep, SDL_Rect wall1, SDL_Rect wall2) {
  mPosX += mVelX * timeStep;
  if (mPosX < 0 || mPosX >= SCREEN_WIDTH - BALL_WIDTH) {
    reset();
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
  printf("%i %i\n", wall2.w, wall2.h);
  if (checkCollision(mCollider, wall2)) {
    mPosX = wall2.x - BALL_WIDTH;
    mVelX *= -1;
  }
  mCollider.x = mPosX;
  mCollider.y = mPosY;
}

void Ball::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0xE0, 0xE0, 0xE0, 0xBF);
  SDL_Rect renderQuad = {int(mPosX), int(mPosY), BALL_WIDTH, BALL_HEIGHT};
  SDL_RenderCopy(renderer, ballTexture, NULL, &renderQuad);
}

void Ball::loadFromFile(SDL_Renderer *renderer) {
  SDL_Texture *newTexture = NULL;
  std::string path = "../assets/dot.bmp";
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
  }
  ballTexture = newTexture;
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

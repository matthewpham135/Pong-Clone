#include "Paddle.h"
#include "Global.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>

Paddle::Paddle(int id) {
  playerId = id;
  if (id == 0) {
    mPosX = 5;
  } else {
    mPosX = SCREEN_WIDTH - PADDLE_WIDTH - 5;
  }
  mPosY = int(SCREEN_HEIGHT / 2) - int(PADDLE_HEIGHT / 2);
  mVelY = 0;
  mCollider.w = PADDLE_WIDTH;
  mCollider.h = PADDLE_HEIGHT;
  mCollider.x = mPosX;
  mCollider.y = mPosY;
}

void Paddle::handleEvent(SDL_Event &e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    if (playerId == 0) {
      switch (e.key.keysym.sym) {
      case SDLK_w:
        mVelY -= PADDLE_VEL;
        break;
      case SDLK_s:
        mVelY += PADDLE_VEL;
        break;
      }
    } else {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        mVelY -= PADDLE_VEL;
        break;
      case SDLK_DOWN:
        mVelY += PADDLE_VEL;
        break;
      }
    }
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    if (playerId == 0) {
      switch (e.key.keysym.sym) {
      case SDLK_w:
        mVelY += PADDLE_VEL;
        break;
      case SDLK_s:
        mVelY -= PADDLE_VEL;
        break;
      }
    } else {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        mVelY += PADDLE_VEL;
        break;
      case SDLK_DOWN:
        mVelY -= PADDLE_VEL;
        break;
      }
    }
  }
}

void Paddle::move(float timeStep) {
  mPosY += mVelY * timeStep;
  if (mPosY < 0) {
    mPosY = 0;
  } else if (mPosY > SCREEN_HEIGHT - PADDLE_HEIGHT) {
    mPosY = SCREEN_HEIGHT - PADDLE_HEIGHT;
  }
  mCollider.y = mPosY;
}

void Paddle::render(SDL_Renderer *renderer) {
  SDL_Rect paddleRect = {(int)mPosX, (int)mPosY, PADDLE_WIDTH, PADDLE_HEIGHT};
  SDL_SetRenderDrawColor(renderer, 0xE0, 0xE0, 0xE0, 0xBF);
  SDL_RenderFillRect(renderer, &paddleRect);
}

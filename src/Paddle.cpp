#include "Paddle.h"
#include "Global.h"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>

Paddle::Paddle(int id) {
  playerId = id;
  if (id == 0) {
    mPosX = 0;
  } else {
    mPosX = SCREEN_WIDTH - PADDLE_WIDTH;
  }
  mPosY = (SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
  mVelY = 0;
}

void Paddle::handleEvent(SDL_Event &e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    if (playerId == 0) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        mVelY -= PADDLE_VEL;
      case SDLK_DOWN:
        mVelY += PADDLE_VEL;
      }
    } else {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        mVelY -= PADDLE_VEL;
      case SDLK_DOWN:
        mVelY += PADDLE_VEL;
      }
    }
  } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    if (playerId == 0) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        mVelY += PADDLE_VEL;
      case SDLK_DOWN:
        mVelY -= PADDLE_VEL;
      }
    } else {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        mVelY += PADDLE_VEL;
      case SDLK_DOWN:
        mVelY -= PADDLE_VEL;
      }
    }
  }
}
void Paddle::move() {
  mPosY += mVelY;
  if ((mPosY < 0) || (mPosY + PADDLE_HEIGHT > SCREEN_HEIGHT)) {
    mPosY -= mVelY;
  }
}
void Paddle::render() {
  // come back to after we add texture class for render
  // this will just call render member function
}

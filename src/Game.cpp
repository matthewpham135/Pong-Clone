#include "Game.h"
#include "Ball.h"
#include "Global.h"
#include "Paddle.h"
#include "SDL.h"
#include <SDL_blendmode.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <cstddef>
Game::Game() {}

bool Game::init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      renderer = SDL_CreateRenderer(
          window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      }
      if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0) {
        printf("Renderer Blend Mode could not be set! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      }
    }
  }
  return success;
}

void Game::close() {
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_Quit();
}

void Game::run() {
  if (!(init())) {
    printf("Failed to initialize!\n");
  } else {
    SDL_Event e;
    bool quit = false;
    Paddle paddle1 = Paddle(0);
    Paddle paddle2 = Paddle(1);
    Ball ball = Ball(renderer);
    Uint32 lastTicks = SDL_GetTicks();
    while (!quit) {
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
          if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_s) {
            paddle1.handleEvent(e);
          } else if (e.key.keysym.sym == SDLK_UP ||
                     e.key.keysym.sym == SDLK_DOWN) {
            paddle2.handleEvent(e);
          }
        }
      }
      Uint32 nowTicks = SDL_GetTicks();
      float timeStep = (nowTicks - lastTicks) / 1000.f;
      paddle1.move(timeStep);
      paddle2.move(timeStep);
      ball.move(timeStep, paddle1.mCollider, paddle2.mCollider);
      lastTicks = nowTicks;
      SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0xFF);
      SDL_RenderClear(renderer);

      SDL_Rect boundary = {SCREEN_WIDTH / 2 - (SCREEN_WIDTH / 200), 0,
                           SCREEN_WIDTH / 100, SCREEN_HEIGHT};
      SDL_SetRenderDrawColor(renderer, 0xE0, 0xE0, 0xE0, 0xBF);
      SDL_RenderFillRect(renderer, &boundary);

      paddle1.render(renderer);
      paddle2.render(renderer);
      ball.render(renderer);
      SDL_RenderPresent(renderer);
    }
  }
  close();
}

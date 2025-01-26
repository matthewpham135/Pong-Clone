#include "Game.h"
#include "Ball.h"
#include "Global.h"
#include "Paddle.h"
#include "SDL.h"
#include <SDL_blendmode.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL_video.h>
#include <cstddef>
#include <sstream>
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
      } else {
        if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) < 0) {
          printf("Renderer Blend Mode could not be set! SDL Error: %s\n",
                 SDL_GetError());
          success = false;
        }
        if (TTF_Init() < 0) {
          printf("TTF could not be created! SDL_ttf Error: %s\n",
                 TTF_GetError());
          success = false;
        }
      }
    }
  }
  return success;
}

bool Game::loadMedia() {
  bool success = true;
  gameFont = TTF_OpenFont("../assets/fonts/font.ttf", 28);
  if (gameFont == NULL) {
    printf("Failed to load game font! SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  }
  return success;
}

SDL_Texture *Game::renderText(std::string message) {
  SDL_Color textColor = {224, 224, 224};
  if (gameFont == NULL) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    return NULL;
  }
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(gameFont, message.c_str(), textColor);
  SDL_Texture *text = NULL;
  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
    return NULL;
  } else {
    text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (text == NULL) {
      printf("Unable to crete texture from rendered text! SDL Error: %s\n",
             SDL_GetError());
      return NULL;
    }
  }
  SDL_FreeSurface(textSurface);
  return text;
}

void Game::close() {
  SDL_DestroyTexture(score1Texture);
  score1Texture = NULL;
  SDL_DestroyTexture(score2Texture);
  score2Texture = NULL;
  TTF_CloseFont(gameFont);
  gameFont = NULL;
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void Game::run() {
  if (!(init())) {
    printf("Failed to initialize!\n");
  } else {
    if (!(loadMedia())) {
      printf("Failed to load media!\n");
    } else {
      SDL_Event e;
      bool quit = false;
      Paddle paddle1 = Paddle(0);
      Paddle paddle2 = Paddle(1);
      Ball ball = Ball(renderer);
      Uint32 lastTicks = SDL_GetTicks();
      int score1 = 0;
      int score2 = 0;
      std::stringstream score1Text;
      std::stringstream score2Text;
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

        int result = ball.move(timeStep, paddle1.mCollider, paddle2.mCollider);
        if (result == PLAYER_1_SCORES) {
          score1 += 1;
        } else if (result == PLAYER_2_SCORES) {
          score2 += 1;
        }

        score1Text.str("");
        score1Text << score1;
        score2Text.str("");
        score2Text << score2;
        score1Texture = renderText(score1Text.str().c_str());
        score2Texture = renderText(score2Text.str().c_str());

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
        SDL_Rect score1Rect = {SCREEN_WIDTH / 4, 10, 50, 100};
        SDL_Rect score2Rect = {(3 * (SCREEN_WIDTH / 4)) - 50, 10, 50, 100};
        SDL_RenderCopy(renderer, score1Texture, NULL, &score1Rect);
        SDL_RenderCopy(renderer, score2Texture, NULL, &score2Rect);

        SDL_RenderPresent(renderer);
      }
    }
  }
  close();
}

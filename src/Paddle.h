#ifndef PADDLE_H
#define PADDLE_H

typedef union SDL_Event SDL_Event;

class Paddle {
public:
  static const int PADDLE_WIDTH = 20;
  static const int PADDLE_HEIGHT = 20;
  static const int PADDLE_VEL = 10;
  Paddle(int id);
  void handleEvent(SDL_Event &e);
  void move();
  void render();

private:
  int playerId;
  int mPosX, mPosY;
  int mVelX, mVelY;
};

#endif

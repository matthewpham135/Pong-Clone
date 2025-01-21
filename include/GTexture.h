#ifndef GTEXTURE_H
#define GTEXTURE_H

#include <string>
typedef int SDL_Texture;

class GTexture {
public:
  GTexture();
  ~GTexture();
  bool loadFromFile(std::string path);
  void free();
  void render(int x, int y);
  int getWidth();
  int getHeight();

private:
  SDL_Texture *mTexture;
  int mHeight;
  int mWidth;
};

#endif

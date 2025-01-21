#include "GTexture.h"

GTexture::GTexture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}
GTexture::~GTexture() { free(); }
bool GTexture::loadFromFile(std::string path) { return false; }
void GTexture::free() {}
void GTexture::render(int x, int y) {}
int GTexture::getWidth() { return mWidth; }
int GTexture::getHeight() { return mHeight; }

#pragma once

#include <stdint.h>

class PDBP {
public:
  PDBP();
  ~PDBP();
  
  PDBP(uint8_t pxlSize, uint8_t pxlHeight, uint8_t pxlWidth);

  int initDisplay(); // TODO: do error handling
  void exitDisplay();

  void setDrawColor(uint8_t red, uint8_t green, uint8_t blue);

  void drawPixel(uint8_t x, uint8_t y);
  void drawPixel(uint8_t x, uint8_t y,
      uint8_t red, uint8_t green, uint8_t blue);

  void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,
      uint8_t red, uint8_t green, uint8_t blue);

  void clearDisplay();
  void clearDisplay(uint8_t red, uint8_t green, uint8_t blue);
  void clearDisplayBlack();

  void applyDrawToDisplay();
private:
  uint8_t pxlHeight;
  uint8_t pxlWidth;
  uint8_t pxlSize;

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  void printError(const char*);
};
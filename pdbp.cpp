#include <SDL2/SDL.h>

#include <stdio.h>
#include <iostream>

#include "pdbp.h"

PDBP::PDBP() {
  pxlHeight = 32;
  pxlWidth = 64;
  pxlSize = 16;

  screenBits = boost::dynamic_bitset<>(pxlHeight * pxlWidth);
}

 PDBP::~PDBP() {
 }

PDBP::PDBP(uint8_t pxlSize, uint8_t pxlHeight, uint8_t pxlWidth) {
  this->pxlHeight = pxlHeight;
  this->pxlWidth = pxlWidth;
  this->pxlSize = pxlSize;
}


int PDBP::initDisplay() {
  if(SDL_Init(SDL_INIT_VIDEO ) != 0) {
    printError(SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(
    "SDL Tutorial",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    pxlWidth * pxlSize, pxlHeight * pxlSize,
    SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    printError(SDL_GetError());
    SDL_Quit();
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    printError(SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
}

void PDBP::exitDisplay() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}

void PDBP::setDrawColor(uint8_t red, uint8_t green, uint8_t blue) {
  SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);
}

void PDBP::drawPixel(uint8_t x, uint8_t y) {
  SDL_Rect pxl = {
    x * pxlSize,
    y * pxlSize,
    pxlSize,
    pxlSize
  };
  SDL_RenderFillRect(renderer, &pxl);
}
void PDBP::drawPixel(uint8_t x, uint8_t y,
    uint8_t red, uint8_t green, uint8_t blue) {
  setDrawColor(red, green, blue);
  drawPixel(x, y);
}

void PDBP::drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  uint8_t smX = x1 < x2 ? x1 : x2;
  uint8_t smY = y1 < y2 ? y1 : y2;
  uint8_t lgX = smX == x1 ? x2 : x1;
  uint8_t lgY = smY == y1 ? y2 : y1;

  SDL_Rect rect = {
    smX * pxlSize,
    smY * pxlSize,
    (lgX - smX + 1) * pxlSize,
    (lgY - smY + 1) * pxlSize
  };
  SDL_RenderFillRect(renderer, &rect);
}
void PDBP::drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,
    uint8_t red, uint8_t green, uint8_t blue) {
  setDrawColor(red, green, blue);
  drawRect(x1, y1, x2, y2);
}

void PDBP::applyDrawToDisplay() {
  SDL_RenderPresent(renderer);
}

void PDBP::printError(const char* msg) {
  printf("Error:\n%s\n", msg);
}

void PDBP::setKeyMap(SDL_Keycode key, std::function<void()> callback) {
  keyMap.insert({key, callback}); 
}

bool PDBP::polls() {
  bool contRunning = true;
  SDL_PollEvent(&sdl_evt);
  poll_quit(contRunning);
  poll_keys(contRunning);
  return contRunning;
}

void PDBP::poll_quit(bool &contRunning) {
  if (contRunning)
    contRunning = (sdl_evt.type != SDL_QUIT);
}

void PDBP::poll_keys(bool &contRunning) {
  if (contRunning && sdl_evt.type == SDL_KEYDOWN && keyMap[sdl_evt.key.keysym.sym]) {
    (keyMap[sdl_evt.key.keysym.sym])();
  }
}


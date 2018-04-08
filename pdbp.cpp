#include <SDL2/SDL.h>
#include <stdio.h>

#include "pdbp.h"

PDBP::PDBP() {
  this->pxlHeight = 32;
  this->pxlWidth = 64;
  this->pxlSize = 16;
}

 PDBP::~PDBP() {
  delete window;
  delete renderer;
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

  this->window = SDL_CreateWindow(
    "SDL Tutorial",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    pxlWidth * pxlSize, pxlHeight * pxlSize,
    SDL_WINDOW_SHOWN);

  if (this->window == nullptr) {
    printError(SDL_GetError());
    SDL_Quit();
    return 1;
  }

  this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
  if (this->renderer == nullptr) {
    printError(SDL_GetError());
    SDL_DestroyWindow(this->window);
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
// int main(int argc, char* args[]) {
//   SDL_SetRenderDrawColor(renderer, 0x40, 0xB0, 0xC0, 0xFF);
//   SDL_RenderClear(renderer);

//   SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
//   SDL_Rect r = { //construct "pixel" rect
//         0,
//         0,
//         PXL_SIZE,
//         PXL_SIZE
//       };
//   SDL_RenderFillRect(renderer, &r);
//   SDL_RenderPresent(renderer);

//   SDL_Event quittingEvt;
//   while(quittingEvt.type != SDL_QUIT) {
//     SDL_PollEvent(&quittingEvt);
//   }

  
//   return 0;
// }


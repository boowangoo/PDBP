#pragma once

#include <SDL2/SDL.h>

#include <boost/dynamic_bitset.hpp>

#include <stdint.h>
#include <bitset>
#include <unordered_map>

class PDBP {
public:
  PDBP();
  ~PDBP();
  
  PDBP(uint8_t pxlSize, uint8_t pxlHeight, uint8_t pxlWidth);

  // Displays
  int initDisplay(); // TODO: do error handling
  void exitDisplay();

  void setDrawColor(uint8_t red, uint8_t green, uint8_t blue);

  void drawPixel(uint8_t x, uint8_t y);
  void drawPixel(uint8_t x, uint8_t y,
      uint8_t red, uint8_t green, uint8_t blue);

  void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void drawRect(uint8_t x1, uint8_t y1,  uint8_t x2, uint8_t y2,
      uint8_t red, uint8_t green, uint8_t blue);

  void clearDisplay();
  void clearDisplay(uint8_t red, uint8_t green, uint8_t blue);
  void clearDisplayBlack();

  void applyDrawToDisplay();

  // Keys
  void setKeyMap(SDL_Keycode key, void (*callback)());

  // Polling
  bool polls();

private:
  uint8_t pxlHeight;
  uint8_t pxlWidth;
  uint8_t pxlSize;

  boost::dynamic_bitset<> screenBits;

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  SDL_Event sdl_evt;

  std::unordered_map<SDL_Keycode, void (*)()> keyMap;

  void poll_quit(bool &contRunning);
  void poll_keys(bool &contRunning);

  void printError(const char*);
};
#include "game/Game.h"

int main() {
  Game game(800, 600, "RetroKanto");
  int returnCode = game.run();
  return returnCode;
}
#include "render.h"
#include "pixelShit.h"
#include <string.h>


void setupFrameBuffer() {
  return;

}

void drawMapState() {

  // Alternative 1: do it simply:
  /* 1. loop through background: draw walls/spaces
     2. loop through enemies:draw enemeies(over background)
     3. draw player
     4. tell framebuffer driver that the screen has been updated.
  */

  // Alternative 2: no overwrites, but some searching required.
  // i is each tile.
  for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; ++i) {
    uint16_t **write;
    if (playerAtIndex(i)) {
      write = PIXEL_PLAYER;
    } else if (enemyAtIndex(i)) {
      write = PIXEL_ENEMY;
    } else if (wallAtIndex(i)) {
      write = PIXEL_WALL;
    } else if (spaceAtIndex(i)) {
      write = PIXEL_SPACE;
    } else {
      // critical failure
      //      exit(1); or something
    }

    // j is each row in the "pixel art"
    for (int j = 0; j < RENDER_TILE_SIZE; ++j) {
      // todo change output array to something else.
      //memcpy(output + i*RENDER_TILE_SIZE + j*MAP_WIDTH*RENDER_TILE_SIZE,
      //	     write + j*RENDER_TILE_SIZE,
      //	     RENDER_TILE_SIZE);
    }

  }


  // TODO: tell framebuffer to update!


}

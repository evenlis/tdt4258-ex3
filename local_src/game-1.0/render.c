#include "render.h"
#include "pixelShit.h"
#include <string.h>


void drawMapState(int[] map, Enemy[] enemies, Player player) {

  // i is each tile.
  for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; ++i) {
    uint16_t *write;
    if (playerAtIndex(i)) {
      *write = &PIXEL_PLAYER
    } else if (enemyAtIndex(i)) {
      *write = &PIXEL_ENEMY;
    } else if (wallAtIndex(i)) {
      *write = &PIXEL_WALL;
    } else if (spaceAtIndex(i)) {
      *write = &PIXEL_SPACE;
    }

    // j is each row in the "pixel art"
    for (int j = 0; j < RENDER_TILE_SIZE; ++j) {
      // todo change output array to something else.
      memcpy(output + i*RENDER_TILE_SIZE + j*MAP_WIDTH*RENDER_TILE_SIZE,
	     write + j*RENDER_TILE_SIZE,
	     RENDER_TILE_SIZE);
    }

  }


}

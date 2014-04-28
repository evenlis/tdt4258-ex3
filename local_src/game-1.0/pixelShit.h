#ifndef _PIXELSHIT_H_
#define _PIXELSHIT_H_

#include <stdint.h>

// tiles are 16x16
#define RENDER_TILE_SIZE 16

// COLORS:
#define black  0b0000000000000000
#define red    0b1111100000000000
#define blue   0b0000011111100000
#define green  0b0000000000011111
#define white  0b1111111111111111
#define lgrey  0b0100101001010100
#define brown  0b0111100001000011
#define dkred  0b1101100011000101
#define blond  0b1110111011011001

#define morter  0b1011010110101100
#define brick_  0b1010001000000110

#define skin_  0b1111111111111111

// PIXEL ARRAYS:
uint16_t PIXEL_WALL[RENDER_TILE_SIZE*RENDER_TILE_SIZE] =
  { morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter,
    brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter,
    brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter,
    brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter,

    morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter,
    brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_,
    brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_,
    brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_,

    morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter,
    brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter,
    brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter,
    brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter,

    morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter, morter,
    brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_,
    brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_,
    brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_, brick_, brick_, brick_, morter, brick_, brick_, brick_, brick_
  };


uint16_t PIXEL_SPACE[RENDER_TILE_SIZE*RENDER_TILE_SIZE] =
  { black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, black, black, black, black, black, black
 };

uint16_t PIXEL_PLAYER[RENDER_TILE_SIZE*RENDER_TILE_SIZE] =
  { black, black, black, black, black, black, black, black, black, black, lgrey, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, lgrey, black, black, black, black, black,
    black, black, black, black, black, black, brown, brown, brown, brown, lgrey, black, black, black, black, black,
    black, black, black, black, black, black, brown, white, white, brown, lgrey, black, black, black, black, black,
    black, black, black, black, black, black, white, white, white, white, black, black, lgrey, lgrey, lgrey, black,
    black, black, black, dkred, black, black, white, white, white, white, black, lgrey, lgrey, lgrey, lgrey, black,
    black, skin_, dkred, dkred, dkred, dkred, black, black, black, black, brown, brown, brown, skin_, black, black,
    black, skin_, skin_, skin_, dkred, dkred, dkred, black, black, black, brown, skin_, skin_, skin_, lgrey, black,
    black, skin_, skin_, skin_, dkred, dkred, dkred, black, black, black, brown, skin_, skin_, skin_, lgrey, black,
    black, skin_, dkred, dkred, dkred, dkred, black, black, black, black, brown, brown, brown, skin_, black, black,
    lgrey, lgrey, lgrey, dkred, black, black, blond, blond, blond, blond, black, lgrey, lgrey, lgrey, lgrey, black,
    black, black, lgrey, black, black, black, blond, blond, blond, blond, black, black, lgrey, lgrey, lgrey, black,
    black, black, black, black, black, lgrey, blond, blond, blond, blond, lgrey, black, black, black, black, black,
    black, black, black, black, black, lgrey, skin_, skin_, skin_, skin_, lgrey, black, black, black, black, black,
    black, black, black, black, black, lgrey, lgrey, black, black, lgrey, lgrey, black, black, black, black, black,
    black, black, black, black, black, lgrey, lgrey, black, black, lgrey, lgrey, black, black, black, black, black
  };

// placeholder, clone of player
uint16_t PIXEL_ENEMY[RENDER_TILE_SIZE*RENDER_TILE_SIZE] =
  { black, black, black, black, black, black, black, black, black, black, lgrey, black, black, black, black, black,
    black, black, black, black, black, black, black, black, black, black, lgrey, black, black, black, black, black,
    black, black, black, black, black, black, brown, brown, brown, brown, lgrey, black, black, black, black, black,
    black, black, black, black, black, black, brown, red, red, brown, lgrey, black, black, black, black, black,
    black, black, black, black, black, black, red, red, red, red, black, black, lgrey, lgrey, lgrey, black,
    black, black, black, dkred, black, black, red, red, red, red, black, lgrey, lgrey, lgrey, lgrey, black,
    black, red, dkred, dkred, dkred, dkred, black, black, black, black, brown, brown, brown, red, black, black,
    black, red, red, red, dkred, dkred, dkred, black, black, black, brown, red, red, red, lgrey, black,
    black, red, red, red, dkred, dkred, dkred, black, black, black, brown, red, red, red, lgrey, black,
    black, red, dkred, dkred, dkred, dkred, black, black, black, black, brown, brown, brown, red, black, black,
    lgrey, lgrey, lgrey, dkred, black, black, blond, blond, blond, blond, black, lgrey, lgrey, lgrey, lgrey, black,
    black, black, lgrey, black, black, black, blond, blond, blond, blond, black, black, lgrey, lgrey, lgrey, black,
    black, black, black, black, black, lgrey, blond, blond, blond, blond, lgrey, black, black, black, black, black,
    black, black, black, black, black, lgrey, red, red, red, red, lgrey, black, black, black, black, black,
    black, black, black, black, black, lgrey, lgrey, black, black, lgrey, lgrey, black, black, black, black, black,
    black, black, black, black, black, lgrey, lgrey, black, black, lgrey, lgrey, black, black, black, black, black
  };


#endif

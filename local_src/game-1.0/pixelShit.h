#ifndef _PIXELSHIT_H_
#define _PIXELSHIT_H_

// tiles are 16x16
#define RENDER_TILE_SIZE 16

// COLORS:
uint16_t black = 0b0000000000000000;
uint16_t red =   0b1111100000000000;
uint16_t blue =  0b0000011111100000;
uint16_t green = 0b0000000000011111;
uint16_t white = 0b1111111111111111;

uint16_t lgrey = 0b0100101001010100;
uint16_t brown = 0b0111100001000011;
uint16_t dkred = 0b1101100011000101;
uint16_t blond = 0b1110111011011001;
// wall colors:
uint16_t morter = 0b1011010110101100;
uint16_t brick_ = 0b1010001000000110;

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
    black, black, black, black, black, lgrey, lgrey, black, black, lgrey_, lgrey, black, black, black, black, black,
    black, black, black, black, black, lgrey, lgrey, black, black, lgrey_, lgrey, black, black, black, black, black
 }

// placeholder, clone of player
uint16_t PIXEL_ENEMY[RENDER_TILE_SIZE*RENDER_TILE_SIZE] =
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
    black, black, black, black, black, lgrey, lgrey, black, black, lgrey_, lgrey, black, black, black, black, black,
    black, black, black, black, black, lgrey, lgrey, black, black, lgrey_, lgrey, black, black, black, black, black
 }


#endif

#ifndef _GAME_H_
#define _GAME_H_

// enemy types
#define ENEMY_ALIEN 0

// tile types
#define TILE_WALL 0
#define TILE_SPACE 1

// powerup types
#define POWERUP_MEDKIT 0
#define POWERUP_AMMO 1
#define POWERUP_WEAPON 2

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Position position;
  int tileType;
} Tile;

typedef struct {
  int health;
  int damage;
  int enemyType
} EnemyType;

typedef struct {
  Position position;
  enemyType enemyType;
} Enemy;

typedef struct {
  int ammoDelta;
  int damageDelta;
  int healthDelta;
  int powerUpType;
} PowerUpType;

typedef struct {
  Position position;
  PowerUpType powerUpType;
} PowerUp;

typedef struct {
  Position position;
  int health;
  int ammo;
  int damage;
} Player;

#endif

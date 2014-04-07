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

// event types
#define EVENT_MOVE_UP 0
#define EVENT_MOVE_RIGHT 1
#define EVENT_MOVE_DOWN 2
#define EVENT_MOVE_LEFT 3
#define EVENT_SHOOT_UP 4
#define EVENT_SHOOT_RIGHT 5
#define EVENT_SHOOT_DOWN 6
#define EVENT_SHOOT_LEFT 7

// map meta
#define MAP_WIDTH 1
#define MAP_HEIGHT 1

int map[MAP_WIDTH*MAP_HEIGHT];

Enemy enemies[MAP_WIDTH*MAP_HEIGHT];
int maxEnemies = 0;

Player player;

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  int maxHealth;
  int damage;
  int enemyType;
} EnemyType;

typedef struct {
  Position position;
  int health;
  enemyType* enemyType;
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

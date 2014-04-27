#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

// tile types
#define TILE_WALL 0
#define TILE_SPACE 1

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
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

// misc
#define TRUE 1
#define FALSE 0

FILE* driver;

typedef struct {
  int x;
  int y;
} Position;

typedef struct {
  Position position;
} Entity;

struct EntityList {
  Entity entity;
  struct EntityList *next;
};

int setupGamepad();
int init();
void input_handler(int);
void gpio_handler();
int isButtonPressed(const unsigned int, const unsigned int);

Entity* getEnemyAtPosition(int, int);
int removeEnemyByPosition(int, int);
void addEnemy(Entity);

void movePlayer(int, int);
void shootDirection(int, int);
void generateMap();

int enemyAtPosition(int, int);
int enemyAtIndex(int);
int playerAtIndex(int);
int wallAtIndex(int);
int spaceAtIndex(int);

void turnEvent(int);
void printMap();
int randomFreeSpacePosition();
int enemyAtPositionFlat(int);

int hamiltonDistance(Position, Position);
void moveEnemy(Entity*, int);
void calculateEnemyMove(Entity*);
void attackPlayer(Entity*);
int isFreeSpace(Position);
int abs(int);
void playerTurn();
void enemyTurn();

int map[MAP_WIDTH*MAP_HEIGHT];


struct EntityList *enemies;

Entity player;

#endif

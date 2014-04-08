#include <stdio.h>
#include <stdlib.h>
#include "game.h"

EnemyType Even = {
  .maxHealth = 100,
  .damage = 1,
  .enemyType = 0
};

void movePlayer(int x, int y){

}

/*
 * Returns NULL if there is no enemy at the provided coordinates
 */

Enemy* getEnemyAtPosition(int x, int y){
  for(int i=0; i<maxEnemies; ++i){
    if(enemies[i].position.x == x && enemies[i].position.y == y)
      return &enemies[i];
  }
  return NULL;
}

void shootDirection(int x, int y){
  int xPos = player.position.x;
  int yPos = player.position.y;
  while((xPos += x) != 0 &&
	xPos != MAP_WIDTH-1 &&
	(yPos += y) != 0 &&
	yPos != MAP_HEIGHT-1){
    Enemy* enemy = getEnemyAtPosition(xPos, yPos);
    if(enemy != NULL)
      enemy->health -= player.damage;
  }
}

int randomFreeSpacePosition(){
  // subtract 2*MAP_WIDTH to ensure that a free space will be found
  int randomPosition = rand()%MAP_WIDTH*MAP_HEIGHT-(MAP_WIDTH*2);
  // find first available space; if none is found, exit with an error
  while (map[randomPosition] == TILE_WALL ||
	 enemyAtPosition(randomPosition % MAP_WIDTH, randomPosition / MAP_WIDTH) ||
	 player.position.y * MAP_WIDTH + player.position.x == randomPosition) {
    if (++randomPosition >= MAP_WIDTH*MAP_HEIGHT) {
      exit(1);
    }
  }
  return randomPosition;
}

void generateMap(){
  int openSpaces = (MAP_HEIGHT-2)*(MAP_HEIGHT-2);
  int obstacleRatio = (rand()%5) + 5;
  int nofObstacles = openSpaces*obstacleRatio;
  int enemyRatio = (rand()%5) + 2;
  int nofEnemies = openSpaces * enemyRatio;

  for(int i=0; i<MAP_WIDTH*MAP_HEIGHT; ++i){
    if(i < MAP_WIDTH ||
       i % MAP_WIDTH == 0 ||
       i % MAP_WIDTH == MAP_WIDTH-1 ||
       i >= MAP_WIDTH*MAP_HEIGHT - MAP_WIDTH){
      map[i] = TILE_WALL;
    } else {
      if(nofObstacles != 0 &&
	 rand()%100 <= obstacleRatio){
	--nofObstacles;
	map[i] = TILE_WALL;
	continue;
      } else if (nofEnemies != 0 &&
		 rand()%100 <= enemyRatio) {
	--nofEnemies;
	int randPos = randomFreeSpacePosition();
	enemies[maxEnemies++] = (Enemy){(Position) {randPos%MAP_WIDTH, randPos/MAP_WIDTH}, Even.maxHealth, &Even};
      }
      map[i] = TILE_SPACE;
    }
  }
  int randomPlayerPosition = rand()%MAP_WIDTH*MAP_HEIGHT-(MAP_WIDTH*2);
  while (map[randomPlayerPosition] == TILE_WALL ||
	 enemyAtPosition(randomPlayerPosition % MAP_WIDTH, randomPlayerPosition / MAP_WIDTH)) {
    if (++randomPlayerPosition >= MAP_WIDTH*MAP_HEIGHT) {
      exit(1);
    }
  }
  player =
    (Player){ { .x = randomPlayerPosition % MAP_WIDTH, .y = randomPlayerPosition / MAP_WIDTH },
       100,
       100,
       50
  };
}

int enemyAtPosition(int x, int y) {
  for (int i = 0; i <= maxEnemies; ++i) {
    if (enemies[i].position.x == x &&
	enemies[i].position.y == y)
      return TRUE;
  }
  return FALSE;
}

void turnEvent(int event){
  if(event<4){
    if(event==EVENT_MOVE_UP){
      movePlayer(0,-1);
    } else if(event==EVENT_MOVE_RIGHT){
      movePlayer(1,0);
    } else if(event==EVENT_MOVE_DOWN){
      movePlayer(0,1);
    } else {
      movePlayer(-1,0);
    }
  } else {
    if(event==EVENT_SHOOT_UP){
      shootDirection(0,-1);
    } else if(event==EVENT_SHOOT_RIGHT){
      shootDirection(1,0);
    } else if(event==EVENT_SHOOT_DOWN){
      shootDirection(0,1);
    } else {
      shootDirection(-1,0);
    }
  }
}

int enemyAtPos(int pos){
  for(int i=0; i<maxEnemies; ++i){
    if(enemies[i].position.y*MAP_WIDTH + enemies[i].position.x == pos)
      return TRUE;
  }
  return FALSE;
}

void printMap(){
  int playerPos = player.position.y*MAP_HEIGHT + player.position.x;
  for(int i=0; i<MAP_WIDTH*MAP_HEIGHT; ++i){
    if(i==playerPos){
      printf("%c ", 'P');
      continue;
    } else if(enemyAtPos(i)){
      printf("%c ", 'E');
      continue;
    } else if(i % MAP_WIDTH == 0)
      printf("\n");
    printf("%c ",(map[i] == TILE_WALL ? '#' : ' ' ));
  }
  printf("\n");
  for(int i=0; i<maxEnemies; ++i){
    Enemy enemy = enemies[i];
    Position pos = enemy.position;
    printf("\nE(x=%d, y=%d)\nH: %d\n", pos.x, pos.y, enemy.health);
  }
}

int main(int argc, char *argv[])
{
  generateMap();
  printMap();
  turnEvent(EVENT_SHOOT_UP);
  printMap();
  exit(EXIT_SUCCESS);
}

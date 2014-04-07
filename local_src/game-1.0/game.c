#include <stdio.h>
#include <stdlib.h>
#include "game.h"

EnemyType Even = {
  .maxHealth = 10,
  .damage = 1,
  .enemyType = 0
};

void movePlayer(int x, int y){

}

void shootDirection(int x, int y){

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
       i % MAP_WIDTH-1 == 0 ||
       i >= MAP_WIDTH*MAP_HEIGHT){
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
	enemies[maxEnemies++] = (Enemy){(Position) {1, 1}, &Even, Even.maxHealth};
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
       100
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
      movePlayer(0,1);
    } else if(event==EVENT_MOVE_RIGHT){
      movePlayer(1,0);
    } else if(event==EVENT_MOVE_DOWN){
      movePlayer(0,-1);
    } else {
      movePlayer(-1,0);
    }
  } else {
    if(event==EVENT_SHOOT_UP){
      shootDirection(0,1);
    } else if(event==EVENT_SHOOT_RIGHT){
      shootDirection(1,0);
    } else if(event==EVENT_SHOOT_DOWN){
      shootDirection(0,-1);
    } else {
      shootDirection(-1,0);
    }
  }
}

int main(int argc, char *argv[])
{
  printf("Hello World, I'm game!\n");

  exit(EXIT_SUCCESS);
}

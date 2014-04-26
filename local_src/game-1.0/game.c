#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "game.h"

int removeEnemyByPosition(int x, int y) {
  struct EntityList* previous = NULL;
  struct EntityList* current  = enemies;
  struct EntityList* next     = NULL;
  while(current) {
    Position pos = current->entity.position;
    if (pos.x == x && pos.y == y) {
      if (previous) { // not the first element
	previous->next = next;
	free(current);
	return TRUE;
      }
      else { // the first element, TODO CORRECT???
	free(enemies);
	enemies = next;
	return TRUE;
      }
    }
    previous = current;
    current  = next;
    next = current->next;
  }

  return FALSE;
}

void addEnemy(Entity enemy) {
  struct EntityList* current = enemies;
  while(current) {
    struct EntityList* next = current->next;
    if (!next){
      next = (struct EntityList*) malloc(sizeof(struct EntityList));
      next->entity = enemy;
      return;
    }
    current = next;

  }
}

int enemyAtIndex(int index) {
  int x = index % MAP_WIDTH;
  int y = index / MAP_WIDTH;

  struct EntityList* current = enemies;
  while(current) {
    if (current->entity.position.x == x &&
	current->entity.position.y == y)
      return TRUE;

    current = current->next;
  }
  return FALSE;
}
int playerAtIndex(int index) {
  int x = index % MAP_WIDTH;
  int y = index / MAP_WIDTH;

  return player.position.x == x && player.position.y == y;

}

int wallAtIndex(int index) {
  return map[index] == TILE_WALL;

}

int spaceAtIndex(int index) {
  return map[index] == TILE_SPACE;
}

void calculateEnemyMove(Entity* enemy){
  if((abs(enemy->position.x - player.position.x) == 1 && enemy->position.y - player.position.y == 0) ||
     (abs(enemy->position.y - player.position.y) == 1 && enemy->position.x - player.position.x == 0)){
    attackPlayer(enemy);
    return;
  }
  Position playerPos = player.position;
  Position enemyPos  = enemy->position;
  int enemyX = enemyPos.x;
  int enemyY = enemyPos.y;
  //  int best = 1000000000;
  Position up    = (Position){enemyX,   enemyY-1};
  Position right = (Position){enemyX+1, enemyY};
  Position down  = (Position){enemyX,   enemyY+1};
  Position left  = (Position){enemyX-1, enemyY};
  if(isFreeSpace(up) &&
     hamiltonDistance(up, playerPos) < hamiltonDistance(enemyPos, playerPos))
    moveEnemy(enemy, EVENT_MOVE_UP);
  else if(isFreeSpace(right) &&
	  hamiltonDistance(right, playerPos) < hamiltonDistance(enemyPos, playerPos))
    moveEnemy(enemy, EVENT_MOVE_RIGHT);
  else if(isFreeSpace(down) &&
	  hamiltonDistance(down, playerPos) < hamiltonDistance(enemyPos, playerPos))
    moveEnemy(enemy, EVENT_MOVE_DOWN);
  else if(isFreeSpace(left) &&
	  hamiltonDistance(left, playerPos) < hamiltonDistance(enemyPos, playerPos))
    moveEnemy(enemy, EVENT_MOVE_LEFT);
}

void moveEnemy(Entity* enemy, int event){
  if(event==EVENT_MOVE_UP){
    enemy->position.y -= 1;
  } else if(event==EVENT_MOVE_RIGHT){
    enemy->position.x += 1;
  } else if(event==EVENT_MOVE_DOWN){
    enemy->position.y += 1;
  } else {
    enemy->position.x -= 1;
  }
}

void attackPlayer(Entity* enemy){
  //  player.health -= enemy->enemyType->damage;
  // kill player!
}

/*
 * Returns NULL if there is no enemy at the provided coordinates
 */
Entity* getEnemyAtPosition(int x, int y){

  struct EntityList *current = enemies;
  while(current) {
    Position pos = current->entity.position;
    if (pos.x == x && pos.y == y)
      return &current->entity;

    current = current->next;

  }
  return NULL;
}

int abs(int a){
  return (a < 0 ? -a : a);
}

int hamiltonDistance(Position a, Position b){
  return abs(a.x-b.x) + abs(a.y-b.y);
}

void movePlayer(int x, int y){
  int newX = player.position.x + x;
  int newY = player.position.y + y;
  if(newX > 0 &&
     newX < MAP_WIDTH - 1 &&
     newY > 0 &&
     newY < MAP_HEIGHT - 1 &&
     map[newY * MAP_WIDTH + newX] != TILE_WALL &&
     !getEnemyAtPosition(newX, newY)){
    player.position.x = newX;
    player.position.y = newY;
  }
}


void shootDirection(int x, int y){
  int xPos = player.position.x;
  int yPos = player.position.y;
  while((xPos += x) != 0 &&
	xPos != MAP_WIDTH-1 &&
	(yPos += y) != 0 &&
	yPos != MAP_HEIGHT-1){
    if (removeEnemyByPosition(xPos, yPos))
      break;
  }
}

int randomFreeSpacePosition(){
  // subtract 2*MAP_WIDTH to ensure that a free space will be found
  int randomPosition = rand()%(MAP_WIDTH*MAP_HEIGHT-MAP_WIDTH*2);
  // find first available space; if none is found, exit with an error
  while (map[randomPosition] == TILE_WALL ||
	 getEnemyAtPosition(randomPosition % MAP_WIDTH, randomPosition / MAP_WIDTH)) {
    if (++randomPosition >= MAP_WIDTH*MAP_HEIGHT) {
      exit(1);
    }
  }
  return randomPosition;
}

void generateMap(){
  int openSpaces = (MAP_HEIGHT-2)*(MAP_HEIGHT-2);
  int obstacleRatio = (rand()%5) + 5;
  int nofObstacles = (int)(openSpaces*obstacleRatio/100.0);
  int enemyRatio = (rand()%5) + 2;
  int nofEnemies = (int)(openSpaces * enemyRatio/100.0);

  // generate map
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
      }
      map[i] = TILE_SPACE;
    }
  }

  // generate enemies
  struct EntityList* prev = NULL;
  struct EntityList* current = enemies;
  for(int i=0; i<nofEnemies; ++i){
    int randPos = randomFreeSpacePosition();
    current = (struct EntityList*) malloc(sizeof(struct EntityList));
    current->entity = (Entity) {(Position) {randPos%MAP_WIDTH, randPos/MAP_WIDTH}};
    current->next = NULL;

    if (prev)
      prev->next = current;

    prev = current;



  }


  // place player
  int randomPlayerPosition = randomFreeSpacePosition();
  player =
    (Entity){ { .x = randomPlayerPosition % MAP_WIDTH, .y = randomPlayerPosition / MAP_WIDTH }
  };

}

int isFreeSpace(Position pos){
  if(pos.x > 0 && pos.x < MAP_WIDTH - 1 && pos.y > 0 && pos.y < MAP_HEIGHT - 1)
    return map[pos.y * MAP_WIDTH + pos.x];
  return FALSE;
}

void turnEvent(int event){
  if(event < 4){
    if(event == EVENT_MOVE_UP){
      movePlayer(0,-1);
    } else if(event == EVENT_MOVE_RIGHT){
      movePlayer(1,0);
    } else if(event == EVENT_MOVE_DOWN){
      movePlayer(0,1);
    } else {
      movePlayer(-1,0);
    }
  } else {
    if(event == EVENT_SHOOT_UP){
      shootDirection(0,-1);
    } else if(event == EVENT_SHOOT_RIGHT){
      shootDirection(1,0);
    } else if(event == EVENT_SHOOT_DOWN){
      shootDirection(0,1);
    } else {
      shootDirection(-1,0);
    }
  }
}

void enemyTurn(){
  struct EntityList* current = enemies;
  while(current) {
    calculateEnemyMove(&current->entity);
    current = current->next;

  }
}

void playerTurn(){
  //TODO: get player's move
}

void printMap(){
  int playerPos = player.position.y*MAP_WIDTH + player.position.x;
  for(int i=0; i<MAP_WIDTH*MAP_HEIGHT; ++i){
    if(i==playerPos){
      printf("%c ", 'P');
      continue;
    } else if(enemyAtIndex(i)){
      printf("%c ", 'E');
      continue;
    } else if(i % MAP_WIDTH == 0){
      printf("\n");
    }
    printf("%c ",(map[i] == TILE_WALL ? '#' : ' ' ));
  }
  printf("\n");

  struct EntityList* current = enemies;
  while(current) {
    Position pos = current->entity.position;
    printf("\nE(x=%d, y=%d)\n\n", pos.x, pos.y);
    current = current->next;
  }
}

int main(int argc, char *argv[])
{
  generateMap();
  printMap();
  exit(EXIT_SUCCESS);
}

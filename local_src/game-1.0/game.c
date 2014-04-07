#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void movePlayer(int x, int y){

}

void shootDirection(int x, int y){

}

void generateMap(){
  int openSpaces = (MAP_HEIGHT-2)*(MAP_HEIGHT-2);
  float obstacleRatio = (rand()%5)/100.0 + 0.05;
  int nofObstacles = (int)(openSpaces*obstacleRatio);
  for(int i=0; i<MAP_WIDTH*MAP_HEIGHT; ++i){
    if(i < MAP_WIDTH ||
       i % MAP_WIDTH == 0 ||
       i % MAP_WIDTH-1 == 0 ||
       i >= MAP_WIDTH*MAP_HEIGHT){
      map[i] = TILE_WALL;
    } else {
      if(nofObstacles != 0){

      }
      map[i] = TILE_SPACE;
    }
  }

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

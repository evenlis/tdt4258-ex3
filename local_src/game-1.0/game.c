#include "game.h"

int playerIsAlive = TRUE;

int removeEnemyByPosition(int x, int y) {
  struct EntityList* previous = NULL;
  struct EntityList* current  = enemies;
  struct EntityList* next     = NULL;
  while(current) {
    Position pos = current->entity.position;
    //    printf("\nChecking pos: x=%d, y=%d\n", x, y);
    //    printf("Enemy    pos: x=%d, y=%d\n", pos.x, pos.y);
    if (pos.x == x && pos.y == y) {
      //      printf("Found enemy at x: %d, y: %d\n", pos.x, pos.y);
      if (previous) { // not the first element
	previous->next = next;
	free(current);
	return TRUE;
      }
      else { // the first element, TODO CORRECT???
	enemies = current->next;
	free(current);
	return TRUE;
      }
    }
    previous = current;
    current  = current->next;
    if(current)
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
     hamiltonDistance(up, playerPos) < hamiltonDistance(enemyPos, playerPos)){
    unchanged[enemyY*MAP_WIDTH + enemyX] = FALSE;
    unchanged[(enemyY-1) * MAP_WIDTH + enemyX] = FALSE;
    moveEnemy(enemy, EVENT_MOVE_UP);
  }else if(isFreeSpace(right) &&
	   hamiltonDistance(right, playerPos) < hamiltonDistance(enemyPos, playerPos)){
    unchanged[enemyY*MAP_WIDTH + enemyX + 1] = FALSE;
    unchanged[enemyY*MAP_WIDTH + enemyX] = FALSE;
    moveEnemy(enemy, EVENT_MOVE_RIGHT);
  }else if(isFreeSpace(down) &&
	   hamiltonDistance(down, playerPos) < hamiltonDistance(enemyPos, playerPos)){
    unchanged[(enemyY+1)*MAP_WIDTH + enemyX] = FALSE;
    unchanged[enemyY*MAP_WIDTH + enemyX] = FALSE;
    moveEnemy(enemy, EVENT_MOVE_DOWN);
  }else if(isFreeSpace(left) &&
	   hamiltonDistance(left, playerPos) < hamiltonDistance(enemyPos, playerPos)){
    unchanged[enemyY*MAP_WIDTH + enemyX-1] = FALSE;
    unchanged[enemyY*MAP_WIDTH + enemyX] = FALSE;
    moveEnemy(enemy, EVENT_MOVE_LEFT);
  }
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
  playerIsAlive = FALSE;
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
    unchanged[player.position.y*MAP_WIDTH + player.position.x] = FALSE;
    unchanged[newY*MAP_WIDTH + newX] = FALSE;
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
    if (removeEnemyByPosition(xPos, yPos)){
      unchanged[yPos*MAP_WIDTH + xPos] = FALSE;
      break;
    }
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
  int enemyRatio = (rand()%9) + 4;
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
  struct EntityList* current = NULL;

  for(int i=0; i<nofEnemies; ++i){
    int randPos = randomFreeSpacePosition();
    if (!prev) { // brute: første
      prev =  (struct EntityList*) malloc(sizeof(struct EntityList));
      prev->entity = (Entity) {(Position) {randPos%MAP_WIDTH, randPos/MAP_WIDTH}};
      prev->next = NULL;
      enemies = prev;
    } else {
      current =  (struct EntityList*) malloc(sizeof(struct EntityList));
      current->entity = (Entity) {(Position) {randPos%MAP_WIDTH, randPos/MAP_WIDTH}};
      current->next = NULL;

      prev->next = current;
      prev = current;


    }

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
  enemyTurn();
}

void enemyTurn(){
  struct EntityList* current = enemies;
  while(current) {
    calculateEnemyMove(&current->entity);
    current = current->next;

  }
}

int setupGamepad(){
  driver = fopen("/dev/GPIO_GAMEPAD", "rb");
  if(!driver){
    printf("Error opening gamepad driver\n");
    return -1;
  }
  if(signal(SIGIO, &input_handler) == SIG_ERR){
    printf("Error creating signal handler\n");
    return -1;
  }
  if(fcntl(fileno(driver), F_SETOWN, getpid()) == -1){
    printf("Error setting process as owner\n");
    return -1;
  }
  long oflags = fcntl(fileno(driver), F_GETFL);
  if(fcntl(fileno(driver), F_SETFL, oflags | FASYNC) == -1){
    printf("Error setting FASYNC flag\n");
    return -1;
  }
  return 0;
}

void destroyGamepad(){
  fclose(driver);
}

void input_handler(int signal_no){
  int buttonStatus = fgetc(driver);
  if(isButtonPressed(buttonStatus, 0)){
    turnEvent(EVENT_MOVE_LEFT);
  }else if(isButtonPressed(buttonStatus, 1)){
    turnEvent(EVENT_MOVE_UP);
  }else if(isButtonPressed(buttonStatus, 2)){
    turnEvent(EVENT_MOVE_RIGHT);
  }else if(isButtonPressed(buttonStatus, 3)){
    turnEvent(EVENT_MOVE_DOWN);
  }else if(isButtonPressed(buttonStatus, 4)){
    turnEvent(EVENT_SHOOT_LEFT);
  }else if(isButtonPressed(buttonStatus, 5)){
    turnEvent(EVENT_SHOOT_UP);
  }else if(isButtonPressed(buttonStatus, 6)){
    turnEvent(EVENT_SHOOT_RIGHT);
  }else if(isButtonPressed(buttonStatus, 7)){
    turnEvent(EVENT_SHOOT_DOWN);
  }

}

int isButtonPressed(const unsigned int buttonStatii, const unsigned int buttonNumber) {
  return ((buttonStatii & (1 << buttonNumber)) != (1 << buttonNumber));

}


int init(){
  if(setupGamepad() == -1){
    printf("Error setting up gamepad\n");
    return -1;
  }
  if(setupFrameBuffer() == -1){
    printf("Error setting up framebuffer\n");
    return -1;
  }
  return 0;
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
  /*  while(current) {
    Position pos = current->entity.position;
    //    printf("\nE(x=%d, y=%d)\n\n", pos.x, pos.y);
    current = current->next;
    }*/
}

int main(int argc, char *argv[])
{
  srand(time(NULL));
  generateMap();
  printMap();
  init();
  while(TRUE){
    if (enemies == NULL) { // win condition
      drawMapState(WIN_MAP);
      break;
    } if (!playerIsAlive) {
      drawMapState(GAME_OVER_MAP);
      break;
    }
    drawMapState(map);
    printMap();
    pause();
  }
  destroyFrameBuffer();
  destroyGamepad();
}




/* RENDERING CODE */

// this used to be in a separate file, but we mangled the makefile and were short on time.
#include <string.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>



// file
int fbfd;
// the memory mapped array to hold pixels
uint16_t* fbp;

int screensize = MAP_WIDTH*RENDER_TILE_SIZE * MAP_HEIGHT*RENDER_TILE_SIZE * 2; // 2 bytes per pixel


int setupFrameBuffer() {
  // http://stackoverflow.com/questions/4996777/paint-pixels-to-screen-via-linux-framebuffer

  if((fbfd = open("/dev/fb0", O_RDWR)) == -1) {
    printf("Couldn't open framebuffer'");
    return -1;
  }
  fbp = (uint16_t*) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

  if (!fbp){
    printf("MMAP FAILED!");
    return -1;
  }

  return 0;
}

int destroyFrameBuffer() {
  munmap(fbp, screensize);
  close(fbfd);
  return 0;
}


void drawMapState(int local_map[]) {

  // currently draws te whole thing,
  struct fb_copyarea rect;

  // i is each tile.
  for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; ++i) {
    if (unchanged[i])
      continue;

    unchanged[i] = TRUE;

    uint16_t* write;
    if (playerAtIndex(i)) {
      write = PIXEL_PLAYER;
    }  else if (local_map[i] == TILE_WALL) {
      write = PIXEL_WALL;
    } else if (enemyAtIndex(i)) {
      write = PIXEL_ENEMY;
    } else if (local_map[i] == TILE_SPACE) {
      write = PIXEL_SPACE;
    } else {
      // critical failure
      //      exit(1); or something
    }

    int map_row = i / MAP_WIDTH;
    int map_col = i % MAP_WIDTH;

    for (int tile_col = 0; tile_col < RENDER_TILE_SIZE; ++tile_col) {
      for (int tile_row = 0; tile_row < RENDER_TILE_SIZE; ++tile_row) {
	fbp[map_row  * MAP_WIDTH * RENDER_TILE_SIZE*RENDER_TILE_SIZE +
	    tile_row * MAP_WIDTH * RENDER_TILE_SIZE +
	    tile_col + map_col   * RENDER_TILE_SIZE] = (write[tile_col + tile_row*RENDER_TILE_SIZE]);
      }
    }
  }
  // (0,0) is top left of screen
  rect.dx = 0; //map_row;
  rect.dy = 0; //map_col;
  rect.width = MAP_WIDTH*RENDER_TILE_SIZE;
  rect.height = MAP_HEIGHT*RENDER_TILE_SIZE;
  // Tell framebuffer to update!
  ioctl(fbfd, 0x4680, &rect);
}

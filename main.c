#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include "./style.h"
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define AGENTS_COUNT 5 

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

#define CELL_WIDTH ((float)SCREEN_WIDTH / BOARD_WIDTH)
#define CELL_HEIGHT ((float)SCREEN_HEIGHT / BOARD_HEIGHT)


int scc(int code){
  if (code < 0 ) { 
    fprintf(stderr, "SDL Error : %s\n", SDL_GetError());
    exit(1);
  }
  return code;
}

void *scp(void *ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "SDL Error : %s\n", SDL_GetError());
    exit(1);
  }
  return ptr;
}

void sdl_set_color_hex (SDL_Renderer * renderer, Uint32 hex){
  scc(SDL_SetRenderDrawColor(renderer,
                             (hex >> (3 * 8)) & 0xFF,
                             (hex >> (2 * 8)) & 0xFF,
                             (hex >> (1 * 8)) & 0xFF,
                             (hex >> (0 * 8)) & 0xFF
                             )
      );
}

typedef enum {
  DIR_RIGHT = 0,
  DIR_UP = 1,
  DIR_LEFT = 2,
  DIR_DOWN = 3,
} Dir;

typedef struct {
  int pos_x, pos_y;
  Dir direction;
  int hunger;
  int health;
} Agent;

typedef enum {
  ACTION_NOP=0,
  ACTION_STEP,
  ACTION_EAT,
  ACTION_ATTACK,

} Agent_Actions;

Agent agents[AGENTS_COUNT];



void render_board_grid(SDL_Renderer *renderer){

  sdl_set_color_hex(renderer, GRID_COLOR);

  for (int x = 0 ; x < BOARD_WIDTH ; ++x)
  {
    scc(SDL_RenderDrawLine(renderer,
                          x * CELL_WIDTH, 
                          1, 
                          x * CELL_WIDTH,
                          SCREEN_HEIGHT));
  }
  for (int x = 0 ; x < BOARD_HEIGHT ; ++x)
  {
    scc(SDL_RenderDrawLine(renderer,
                          1, 
                          x * CELL_HEIGHT, 
                          SCREEN_WIDTH,  
                          x * CELL_HEIGHT));
  }
}

int random_int_range(int low, int high){
  return rand() % (high - low)  + low;
}

Dir random_dir(void){
  return (Dir) random_int_range(0, 4);
}

Agent random_agent(void){
  Agent agent = {0};
  agent.pos_x = random_int_range(0, BOARD_WIDTH); 
  agent.pos_y = random_int_range(0, BOARD_HEIGHT); 
  agent.direction = random_dir();
  agent.hunger = 100;
  agent.health = 100;
  return agent ;
}

void init_agents(void){
  for (size_t i = 0; i < AGENTS_COUNT ; i++){
    agents[i] = random_agent();
  }

}

void render_agent(SDL_Renderer * renderer, Agent agent) {
  sdl_set_color_hex(renderer, AGENT_COLOR);
  SDL_Rect rect = {
    (int) floorf(agent.pos_x * CELL_WIDTH),
    (int) floorf(agent.pos_y * CELL_HEIGHT),
    (int) floorf(CELL_WIDTH),
    (int) floorf(CELL_HEIGHT)
  };
  scc( SDL_RenderFillRect(renderer, &rect));

}

void render_all_agents(SDL_Renderer * renderer ) {
  for(size_t i = 0 ; i < AGENTS_COUNT; ++i) {
    render_agent(renderer, agents[i]);
  }  
}

int main (int argc, char * argv[])
{
  init_agents();
  scc(SDL_Init(SDL_INIT_VIDEO));
  srand(time(NULL));
  SDL_Window * const window = scp(SDL_CreateWindow("Game1",
                                       0, 0, 
                                       SCREEN_WIDTH, SCREEN_HEIGHT, 
                                       SDL_WINDOW_RESIZABLE));


  SDL_Renderer *const  renderer =  scp(SDL_CreateRenderer(window,
                                                      -1, 
                                                      SDL_RENDERER_ACCELERATED ));
  int quit= 0;
  while (!quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { 
      switch(event.type) {
        case SDL_QUIT: {
          quit= 1;
        }break;
      }

      sdl_set_color_hex(renderer, BACKGROUND_COLOR);
      scc(SDL_RenderClear(renderer));
      render_board_grid(renderer);
      render_all_agents(renderer);

      SDL_RenderPresent(renderer);
    }
  }
  SDL_Quit();
  printf("ran\n");
  return 0;
}

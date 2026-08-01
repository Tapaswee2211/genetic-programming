#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define AGENTS_COUNT 5 

#define BOARD_WIDTH 100
#define BOARD_HEIGHT 100

#define CELL_WIDTH ((float)SCREEN_WIDTH / BOARD_WIDTH)
#define CELL_HEIGHT ((float)SCREEN_HEIGHT / BOARD_HEIGHT)

#define BACKGROUND_COLOR "E8EEF2"
#define GRID_COLOR "0A1045"

Uint8 hex_to_dec(char nibble){
  if ( '0' <= nibble && nibble <= '9') return nibble - '0';
  if ( 'a' <= nibble && nibble <= 'f') return nibble - 'a' + 10;
  if ( 'A' <= nibble && nibble <= 'F') return nibble - 'A' + 10;
  printf("Incorrect Hex Character %c\n", nibble);
  exit(1);
}

Uint8 parse_hex_byte( const char *byte_hex) {
  return hex_to_dec(*byte_hex) * 0x10 + hex_to_dec(*(byte_hex+ 1) );
}

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

void sdl_set_color_hex (SDL_Renderer * renderer, const char * hex){
  size_t hex_len = strlen(hex);
  assert(hex_len == 6);
  scc(SDL_SetRenderDrawColor(renderer,
                             parse_hex_byte(hex),
                             parse_hex_byte(hex+2),
                             parse_hex_byte(hex+4),
                             255
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
  return rand() %   (high - low)  + low;
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
  for (size_t i =0; i < AGENTS_COUNT ; i++){
    agents[i] = random_agent();
  }

}

void render_agent(SDL_Renderer * renderer, Agent agent) {
  assert(0 && "TODO: render_agent is not yet implemented");
}

void render_all_agents(SDL_Renderer * renderer ) {

  for(size_t i = 0 ; i < AGENTS_COUNT; ++i) {
    render_agent(renderer, agents[i]);
  }  
}

int main (int argc, char * argv[])
{
  scc(SDL_Init(SDL_INIT_VIDEO));
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

      SDL_RenderPresent(renderer);
    }
  }
  SDL_Quit();
  printf("ran\n");
  return 0;
}

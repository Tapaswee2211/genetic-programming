#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BOARD_WIDTH 100
#define BOARD_HEIGHT 100

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


void render_board_grid(SDL_Renderer *renderer){

  scc(SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255));

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

      scc(SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255));
      scc(SDL_RenderClear(renderer));
      render_board_grid(renderer);

      SDL_RenderPresent(renderer);
    }
  }
  SDL_Quit();
  printf("ran\n");
  return 0;
}

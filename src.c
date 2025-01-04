#include "header.h"



/* Inistialisation de la SDL + Creation de fenêtre et d'un rendu */
void Init(const char *str, int Width, int Height, SDL_Window **window, SDL_Renderer **render)
{
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("%sEchec de l'initialisation\n", SDL_GetError());
        SDL_Quit();
    }

    *window = SDL_CreateWindow(str, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
    if(*window == NULL)
    {
        SDL_Log("%sEchec de la creation de la fenêtre\n", SDL_GetError());
        SDL_Quit();
    }

    *render = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(*render == NULL)
    {
        SDL_Log("%sEchec de la creation du rendu\n", SDL_GetError());
        SDL_Quit();
    }

}



/* Libère les espaces alloués */
void clear (SDL_Renderer **render, SDL_Window **window)
{
    SDL_DestroyRenderer(*render);
    SDL_DestroyWindow(*window);
    SDL_Quit();
}



/* Dessine un rectangle à l'écran */
void DrawRect(SDL_Renderer **render, SDL_Rect *rect, int R, int G, int B)
{
    SDL_SetRenderDrawColor(*render, R, G, B, 255);
    SDL_RenderFillRect(*render, rect);
}


/* Fait apparaitre aléatoirement un fruit à l'écran */
void R_Spawn_Fruits(SDL_Rect *fruit, int WIDTH, int HEIGHT, int SNAKE_SIZE)
{
    fruit->x = (rand() % (WIDTH / SNAKE_SIZE)) * SNAKE_SIZE; 
    fruit->y = (rand() % (HEIGHT / SNAKE_SIZE)) * SNAKE_SIZE; 

    fruit->w = SNAKE_SIZE;
    fruit->h = SNAKE_SIZE;
}







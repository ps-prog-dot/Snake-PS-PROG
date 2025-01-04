#ifndef header_h
#define header_h

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void Init(const char *str, int Width, int Height, SDL_Window **window, SDL_Renderer **render);
void clear (SDL_Renderer **render, SDL_Window **window);
void DrawRect(SDL_Renderer **render, SDL_Rect *rect, int R, int G, int B);
void R_Spawn_Fruits(SDL_Rect *fruit, int WIDTH, int HEIGHT, int SNAKE_SIZE);

#endif

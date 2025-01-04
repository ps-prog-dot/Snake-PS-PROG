#include <SDL2/SDL.h>
#include "header.h"

#define WIDTH 800
#define HEIGHT 600

#define SNAKE_SIZE 20
#define SPEED 20
#define MOVE_INTERVAL 100

int compteFruits;

typedef enum
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
}Direction;

int main()
{
    SDL_Window *window; SDL_Renderer *render; 
    Init("Snake Remake", WIDTH, HEIGHT, &window, &render);

    SDL_Rect Snake[100]; SDL_Rect fruit; SDL_Rect Head;
    Head.x = WIDTH / 2;
    Head.y = HEIGHT / 2;
    Head.w = SNAKE_SIZE;
    Head.h = SNAKE_SIZE;

    int SnakeL = 5;
    for(int i = 0; i < SnakeL; i++)
    {
        Snake[i].x = WIDTH / 2;
        Snake[i].y = HEIGHT / 2;
        Snake[i].w = SNAKE_SIZE;
        Snake[i].h = SNAKE_SIZE;
    }

    
    
    Direction dir = RIGHT;
    Uint32 LastMoveTime = SDL_GetTicks();
    
    srand(time(NULL));
    R_Spawn_Fruits(&fruit, WIDTH, HEIGHT, SNAKE_SIZE);
    
    SDL_Event e; bool running = true;
    while(running)
    {
        

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                running = false;
                break;
            }

            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP    : if (dir != DOWN)  dir = UP;    break;
                    case SDLK_DOWN  : if (dir != UP)    dir = DOWN;  break;
                    case SDLK_RIGHT : if (dir != LEFT)  dir = RIGHT; break;
                    case SDLK_LEFT  : if (dir != RIGHT) dir = LEFT;  break;
                }
            }
        }

        rand();

        /* Gestion des collisions au bords de la fenêtre  */
        if(Head.x < 0 || Head.y < 0 || Head.x + Head.w > WIDTH || Head.y + Head.h > HEIGHT)
        {  
            running = false;
        }    
        

        if(SDL_GetTicks() - LastMoveTime > MOVE_INTERVAL)
        {
            LastMoveTime = SDL_GetTicks();
            
            /* Chaque segment suit la tête en prenant la place de celui du qui est en face lui */
            for(int i = SnakeL - 1; i > 0; i--)
            {
                Snake[i].x = Snake[i - 1].x;
                Snake[i].y = Snake[i - 1].y;
            }   
            


            switch(dir)
            {
                case UP   : Head.y -= SPEED; break;
                case DOWN : Head.y += SPEED; break;
                case RIGHT: Head.x += SPEED; break;
                case LEFT : Head.x -= SPEED; break;
            }

            

            /* Gestion des collisions avec la tête et le corps du serpent  */
            for(int i = 1; i < SnakeL; i++) 
            {
                if(Head.x == Snake[i].x && Head.y == Snake[i].y)
                {
                    printf("Gourmand va\n");
                    running = false;
                }
            }

            /* Fait grandir le serpent si il mange un fruit et en fait réaparaitre un ailleurs */
            if(Head.x == fruit.x && Head.y == fruit.y)
            {
                SnakeL ++;
                Snake[SnakeL - 1] = Snake[SnakeL - 2];
    
                R_Spawn_Fruits(&fruit, WIDTH, HEIGHT, SNAKE_SIZE);
                compteFruits++;
            }

            /* Complète la boucle d'itération negative de Snake[i] */
            Snake[0].x = Head.x;
            Snake[0].y = Head.y;

            
            SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
            SDL_RenderClear(render);

            DrawRect(&render, &fruit, 255, 0, 0);

            DrawRect(&render, &Head, 61, 203, 64);
            SDL_SetRenderDrawColor(render, 3, 139, 5, 255);
            for(int i = 1; i < SnakeL; i++)
            {
                SDL_RenderFillRect(render, &Snake[i]);
            }         

            SDL_RenderPresent(render);
        }
    }

    SDL_Log("Nombre de fruit mangés : %d", compteFruits);
    
    clear(&render, &window);
}
#include <stdio.h>
#include <stdbool.h>

#include "globals.h"
int DEFAULT_WINDOW_WIDTH = 800;
int DEFAULT_WINDOW_HEIGHT = 600;
int SNAKE_SIZE = 50;
int SNAKE_R = 255;
int SNAKE_G = 255;
int SNAKE_B = 255;
int SNAKE_A = 255;

#include "sdl_cat.h"
#include "snake_logic.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int x_cells = DEFAULT_WINDOW_WIDTH / SNAKE_SIZE - 1;
    int y_cells = DEFAULT_WINDOW_HEIGHT / SNAKE_SIZE - 1;
    snake *head = forge_node(rand_range(0, x_cells), rand_range(0, y_cells));
    snake *tail = head;
    snake *snake_food = forge_node(rand_range(0, x_cells), rand_range(0, y_cells));

    SDL_Window *main_window = initMainWindow();
    if (main_window == NULL)
    {
        quit(NULL);
        return EXIT_FAILURE;
    }

    SDL_Renderer *main_window_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
    if (main_window_renderer == NULL)
    {
        printf("Renderer could not be created!\n");
        quit(main_window);
        return EXIT_FAILURE;
    }

    SDL_Event event;

    int score = 0;
    int is_alive = 1;
    int x = 150, y = 150;
    int vx = 1, vy = 0;
    grow_snake(&tail, vx, vy);
    grow_snake(&tail, vx, vy);
    // grow_snake(&tail, vx, vy);
    clock_t start = 0;
    clock_t end;
    while (is_alive)
    {
        SDL_SetRenderDrawColor(main_window_renderer, 0, 0, 0, 10);
        SDL_RenderClear(main_window_renderer);
        // SDL_RenderPresent(main_window_renderer);

        int xcount = DEFAULT_WINDOW_WIDTH / SNAKE_SIZE, ycount = DEFAULT_WINDOW_HEIGHT / SNAKE_SIZE;
        for (int i = 0; i < xcount; i++)
            lineRGBA(main_window_renderer, i * SNAKE_SIZE, 0, i * SNAKE_SIZE, DEFAULT_WINDOW_HEIGHT, 200, 200, 0, 255);
        for (int i = 0; i < ycount; i++)
            lineRGBA(main_window_renderer, 0, i * SNAKE_SIZE, DEFAULT_WINDOW_WIDTH, i * SNAKE_SIZE, 200, 200, 0, 255);

        // grow_snake(&tail, vx, vy);
        // filledCircleRGBA(main_window_renderer, 300, 300, 75, 255, 0, 0, 255);
        end = clock();
        start = why_move_snake(start, end);
        if (!start)
            move_snake(&head, &tail, vx, vy);
        check_boundary(head, &vx, &vy, x_cells, y_cells);
        is_alive = check_colison(head);
        eat_if_food(head, &tail, &snake_food, &score);

        snake *t = head;
        while (t)
        {
            boxRGBA(main_window_renderer, SNAKE_SIZE * t->x, SNAKE_SIZE * t->y, SNAKE_SIZE * t->x + SNAKE_SIZE, SNAKE_SIZE * t->y + SNAKE_SIZE, t->r, t->g, t->b, SNAKE_A);
            t = t->next;
        }
        boxRGBA(main_window_renderer, SNAKE_SIZE * snake_food->x, SNAKE_SIZE * snake_food->y, SNAKE_SIZE * snake_food->x + SNAKE_SIZE, SNAKE_SIZE * snake_food->y + SNAKE_SIZE, snake_food->r, snake_food->g, snake_food->b, SNAKE_A);

        SDL_RenderPresent(main_window_renderer);
        SDL_Delay(50);
        SDL_WaitEventTimeout(&event, 1);
        if (event.type == SDL_QUIT)
            is_alive = 0;
        else if (event.type == SDL_KEYDOWN)
        {
            // printf("%d\n", event.key.keysym.sym);
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {

                printf("ESC\n");

                is_alive = 0;
            }

            if (event.key.keysym.sym == SDLK_RIGHT && vx != -1)
            {
                // printf("RIGHT\n");
                vx = 1;
                vy = 0;
            }

            if (event.key.keysym.sym == SDLK_LEFT && vx != 1)
            {
                vx = -1;
                vy = 0;
                // printf("LEFT\n");
            }

            if (event.key.keysym.sym == SDLK_UP && vy != 1)
            {
                vx = 0;
                vy = -1;
                // printf("UP\n");
            }
            if (event.key.keysym.sym == SDLK_DOWN && vy != -1)
            {
                vx = 0;
                vy = 1;
                // printf("DOWN\n");
            }

            // grow_snake(&tail, vx, vy);
        }
    }
    SDL_DestroyRenderer(main_window_renderer);
    quit(main_window);

    printf("YOUR SCORE: %d\n", score);
    printf("probably you died\n:c\n");

    return EXIT_SUCCESS;
}
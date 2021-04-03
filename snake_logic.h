#ifndef SNAKE
#define SNAKE

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "globals.h"

typedef struct node snake;
struct node
{
    int x;
    int y;
    int r;
    int g;
    int b;
    struct node *next;
    struct node *prev;
};
snake *forge_node(int x, int y);
void grow_snake(snake **tail, int vx, int vy);
void move_snake(snake **head, snake **tail, int vx, int vy);
clock_t why_move_snake(clock_t start, clock_t end);
int rand_range(int min, int max);
void check_boundary(snake *head, int *vx, int *vy, int xlim, int ylim);
int check_colison(snake *head);
void eat_if_food(snake *head, snake **tail, snake **food, int *score);

#endif
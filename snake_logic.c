#include "snake_logic.h"
int speed = 2000;

snake *forge_node(int x, int y)
{
    snake *node = (snake *)malloc(sizeof(snake));
    node->x = x;
    node->y = y;
    node->r = rand() % 256;
    node->g = rand() % 256;
    node->b = rand() % 256;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
void grow_snake(snake **tail, int vx, int vy)
{
    (*tail)->next = forge_node((*tail)->x - vx, (*tail)->y - vy);
    (*tail)->next->prev = (*tail);
    (*tail) = (*tail)->next;
}
void move_snake(snake **head, snake **tail, int vx, int vy)
{
    snake *last = (*tail)->prev;
    last->next = NULL;
    (*tail)->next = (*head);
    (*tail)->prev = NULL;
    (*head)->prev = (*tail);
    (*head) = (*tail);
    (*tail) = last;
    (*head)->x = (*head)->next->x + vx;
    (*head)->y = (*head)->next->y + vy;
}
clock_t why_move_snake(clock_t start, clock_t end)
{
    if (start == 0)
        start = clock();
    if ((double)(end - start) > speed)
        start = 0;
    return start;
}
int rand_range(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
void check_boundary(snake *head, int *vx, int *vy, int xlim, int ylim)
{
    if (head->x < 0)
    {
        head->x = xlim;
        *vx = -1;
        *vy = 0;
    }
    if (head->x > xlim)
    {
        head->x = 0;
        *vx = 1;
        *vy = 0;
    }
    if (head->y < 0)
    {
        head->y = ylim;
        *vy = -1;
        *vx = 0;
    }
    if (head->y > ylim)
    {
        head->y = 0;
        *vy = 1;
        *vx = 0;
    }
}

int check_colison(snake *head)
{
    snake *t = head->next;
    while (t->next)
    {
        if (t->x == head->x && t->y == head->y)
            return 0;
        t = t->next;
    }
    return 1;
}
void eat_if_food(snake *head, snake **tail, snake **food, int *score)
{
    int xlim = DEFAULT_WINDOW_WIDTH / SNAKE_SIZE;
    int ylim = DEFAULT_WINDOW_HEIGHT / SNAKE_SIZE;
    if ((*food)->x == head->x && (*food)->y == head->y)
    {
        (*score) += 1;
        speed -= (*score);
        printf("YOUR SCORE: %d\n", *score);
        (*tail)->next = (*food);
        (*food)->prev = (*tail);
        (*tail) = (*food);
        (*food) = forge_node(rand_range(0, xlim - 1), rand_range(0, ylim - 1));
    }
}
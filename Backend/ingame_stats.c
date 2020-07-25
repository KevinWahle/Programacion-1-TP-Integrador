#include "ingame_stats.h"

static int lives;
static int points;

void reset_lives()
{
    lives=INIT_LIFE;
} 

void reset_points()
{
    points=0;
}

void increase_points(int cant)
{
    points += cant;
}

void decrease_lives()
{
    if(lives>0)
    lives--;
}

int get_lives()
{
    return lives;
}

int get_points()
{
    return points;
}
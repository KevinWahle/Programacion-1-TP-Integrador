void reset_lives(void);
void reset_points(void);

void increase_points(const int cant);
int decrease_lives(void);

int get_lives(void);
int get_points(void);
int* get_shields(void);

void kill_alien(const int tipo_alien);
void shield_collision(int shield, int parte);
void level_up();

#define INIT_LIFES 3

#define CRAB_POINTS     10
#define OCTOPUS_POINTS  20  
#define SQUID_POINTS    30  
#define UFO_POINTS      50
#define MIN_RAND        2
#define MAX_RAND        4

#define SHIELDS         5
#define SHIELD_PARTS    2
#define SHIELD_LIVES    2

enum INVADERS{
    CRAB = 0,
    OCTOPUS,
    SQUID,
    UFO,
};

enum PARTES_SHIELD{
    IZQUIERDA=0,
    DERECHA,
};



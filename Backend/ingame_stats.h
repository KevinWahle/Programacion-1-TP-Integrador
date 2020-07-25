#define INIT_LIFES 3

void reset_lives(void);
void reset_points(void);

void increase_points(const int cant);
int decrease_lives(void);

int get_lives(void);
int get_points(void);
int* get_shields(void);

void kill_alien(const int tipo_alien);
void break_shield();
void level_up();

#define CRAB_POINTS     10
#define OCTOPUS_POINTS  10
#define SQUID_POINTS    10
#define UFO_POINTS      250

#define SHIELDS         5
#define SHIELD_PARTS    2
#define SHIELD_LIVES    2

enum{
    CRAB = 0,
    OCTOPUS,
    SQUID,
    UFO,
};



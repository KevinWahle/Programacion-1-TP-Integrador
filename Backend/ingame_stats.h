void reset_lives(void);
void reset_points(void);
void reset_level(void);
void reset_speed(void);
void reset_killed_aliens(void);
void reset_aliens_matrix(void);

void increase_points(const int cant);
int decrease_lives(void);
void increase_lives(void); 
void increase_level(void);
void increase_speed(const int cant);

int get_lives(void);
int get_points(void);
int get_level(void);

void set_speed(int new_speed);
void set_level(int new_level);

void kill_alien(const int tipo_alien);


#define INIT_LIFES 3
//DUDA: a const.h o a ingame.c?

//Puntaje que asingan los aliens.
#define CRAB_POINTS     10
#define OCTOPUS_POINTS  20  
#define SQUID_POINTS    30  
#define UFO_POINTS      50
#define MIN_RAND        2
#define MAX_RAND        4
//DUDA: Las constantes anteriores: a const.h o a ingame.c?

#define MIN_SPEED        1
#define MAX_SPEED        100
#define STEP_SPEED       1
#define STEP_LEVEL_SPEED 10




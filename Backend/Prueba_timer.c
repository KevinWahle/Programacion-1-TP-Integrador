#include<stdio.h>
#include<time.h>
#define SPEED_STEP 10
#define SEG 1
float f;
clock_t start,end;
int speed_update(int seg, int actual_speed);
void reset_timer(void);

int main ()
{
    reset_timer();
    int speed=1;

    while(speed<100){
        speed= speed_update(SEG, speed);
    }

    return 0;
}

int speed_update(int seg, int actual_speed)
{
    end=clock();
    int difference =((float)(end-start)/CLOCKS_PER_SEC);
    if (difference >= seg)
    {
        reset_timer();
        actual_speed += SPEED_STEP;
        printf("La nueva velocidad es: %d \n", actual_speed);
    }        
    return actual_speed;
}

void reset_timer(void)
{
    start=clock();
}

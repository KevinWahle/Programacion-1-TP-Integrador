#include <time.h>
int msec = 0, trigger = 10; /* 10ms */
clock_t before = clock();

do {
  /*
   * Do something to busy the CPU just here while you drink a coffee
   * Be sure this code will not take more than `trigger` ms
   */

  clock_t difference = clock() - before;
  msec = difference * 1000 / CLOCKS_PER_SEC;
  iterations++;
} while ( msec < trigger );

printf("Time taken %d seconds %d milliseconds (%d iterations)\n",
  msec/1000, msec%1000, iterations);

/////////////////////////////////////////////////////////////////////////////////////////777  

time_t start,end;
start=clock();//predefined  function in c
//after the user defined function does its work
end=clock();
t=(end-start)/CLOCKS_PER_SEC;


////////////////////////////////////////
#include<stdio.h>

#include<time.h>

void main(void){

float f;

clock_t start,end;

start=clock();

//some code or function blocks whose time you want to check the time complexity

end=clock();

f=(float)(end-start)/CLOCKS_PER_SECONDS;(gives you the answer as a floating point value)

}
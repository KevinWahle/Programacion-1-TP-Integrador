#include<stdio.h>
#include<time.h>

float f;
clock_t start,end;

int main ()
{
    start=clock();
    int n=0;
    while(n<10){

        end=clock();
        if (((float)(end-start)/CLOCKS_PER_SEC) > 3)
        {
            start=clock();
            n++;
            printf("%d \n",n);
        }
    }

    
}

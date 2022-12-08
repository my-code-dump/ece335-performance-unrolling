#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LENGTH 10000
#define K 10000

double A[LENGTH];

void combine3(double *X, double *dest, int length) {
   int z = 0;

   while (z < K){
       for (int i = 0; i < length; i++) {
            *dest = *dest * X[i];
       }
       z++;
   }
}

void combine5(double *X, double *dest, int length) {
   int i;
   double temp = *dest;
   int z = 0;
   int newLen = length - 1;

   while (z < K) {
       for (i = 0; i < newLen; i+=2) {
            temp = (temp * X[i]) * X[i + 1];
       }
       // To get any odd remaining values
       for(; i < length; i++) {
            temp = temp * X[i];
       }
       z++;
   }
   *dest = temp;
}

void combine7(double *X, double *dest, int length) {
   int i;
   double temp = *dest;
   int z = 0;
   int newLen = length - 1;

   while (z < K) {
       for (i = 0; i < newLen; i+=2) {
            temp = temp * (X[i] * X[i + 1]);
       }  
       // To get any odd remaining values
       for(; i < length; i++) {
            temp = temp * X[i];
       }
       z++;
   }
   *dest = temp;
}

void handler(int choice) {
    double x = 1;
    switch(choice) {
        case 3:
            combine3(A, &x, LENGTH);
            break;
        case 5:
            combine5(A, &x, LENGTH);
            break;
        case 7:
            combine7(A, &x, LENGTH);
            break;
        default:
            printf("Invalid Case\n");
            break;
    }

}

int main () {
    // Fill array with randomized doubles
    int i;
    for (i = 0; i < LENGTH; i++) {
        A[i] = 0.90 + (double) (rand() % K) / 50000;     
    }

    clock_t start_t, end_t;
    double total_t;
    
    int a = 3;
    int iters;
    int max = 20;
    printf("For length %d\n", LENGTH);
    // Get the right combine, 3,5,7
    for (; a <= 7; a+=2) {
        iters = 0;
        total_t = 0;
        printf("--- Combine %d ---\n",a);
        // Calculate averages for 20 runs
        for (;iters < max; iters++) {
            start_t = clock();
            handler(a); 
            end_t = clock();
            total_t += (double) (end_t - start_t) / CLOCKS_PER_SEC;
        }
        float avgTime = total_t / max;
        printf("Avg Time: %lfs\n", avgTime);
    }
    return 0;

}

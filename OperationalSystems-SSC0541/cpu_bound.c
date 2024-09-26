#include <stdio.h>
#include <math.h>

#define ITERATIONS 10

double complex_calculation(double x) {
    double result = 0;
    for (int i = 0; i < 1000; i++) {
        result += sin(x) * cos(x) * tan(x) * exp(x);
        x = sqrt(fabs(result));
    }
    return result;
}

int main() {
    printf("Iniciando CPU-bound\n");
    double result = 0;
    unsigned long long int i = 0;
    while(1) {
        for (int j = 0; j < ITERATIONS; j++) {
            result += complex_calculation((double)j / ITERATIONS);
        }
        i++;
        printf("CPU-bound: Iteração %llu, Resultado parcial = %f\n", i, result);
    }
    return 0;
}
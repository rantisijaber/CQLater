#ifndef CQLATER_COMPLEX_H
#define CQLATER_COMPLEX_H

#include <stdbool.h>

typedef struct {
    double real;
    double imag;
} complex_num;


complex_num complex_add(complex_num num1, complex_num num2);
complex_num complex_subtract(complex_num num1, complex_num num2);
complex_num complex_multiply(complex_num num1, complex_num num2);
complex_num complex_conj(complex_num num);
bool complex_conj_check(complex_num num1, complex_num num2);
double complex_modulus_squared(complex_num num);
complex_num complex_divide(complex_num num1, complex_num num2);
double complex_modulus(complex_num num);
complex_num complex_scale(complex_num num, double scale);
double complex_argument(complex_num num);
complex_num complex_euler(double theta);
complex_num complex_normalize(complex_num num);









#endif 


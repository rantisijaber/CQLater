#ifndef CQLATER_COMPLEX_H
#define CQLATER_COMPLEX_H

#include <stdbool.h>

typedef struct {
    double real;
    double imag;
} ComplexNum;


ComplexNum complex_add(ComplexNum num1, ComplexNum num2);
ComplexNum complex_subtract(ComplexNum num1, ComplexNum num2);
ComplexNum complex_multiply(ComplexNum num1, ComplexNum num2);
ComplexNum complex_conj(ComplexNum num);
bool complex_conj_check(ComplexNum num1, ComplexNum num2);
double complex_modulus_squared(ComplexNum num);
ComplexNum complex_divide(ComplexNum num1, ComplexNum num2);
double complex_modulus(ComplexNum num);
ComplexNum complex_scale(ComplexNum num, double scale);
double complex_argument(ComplexNum num);
ComplexNum complex_euler(double theta);
ComplexNum complex_normalize(ComplexNum num);









#endif 


#include "complex.h"
#include <math.h>

ComplexNum complex_add(ComplexNum num1, ComplexNum num2) {
    return (ComplexNum) {
        .real = num1.real + num2.real,
        .imag = num1.imag + num2.imag
    };
}

ComplexNum complex_subtract(ComplexNum num1, ComplexNum num2) {
    return (ComplexNum) {
        .real = num1.real - num2.real,
        .imag = num1.imag - num2.imag
    };
}

ComplexNum complex_multiply(ComplexNum num1, ComplexNum num2) {
    double real_product = num1.real * num2.real;
    double mix1 = num1.real * num2.imag;
    double mix2 = num1.imag * num2.real;
    double imag_product = -1 * (num1.imag * num2.imag);
    
    return (ComplexNum) {
        .real = real_product + imag_product,
        .imag = mix1 + mix2
    };
}

ComplexNum complex_conj(ComplexNum num) {
    return (ComplexNum) {
        .real = num.real,
        .imag = -1 * num.imag
    };
}

bool complex_conj_check(ComplexNum num1, ComplexNum num2) {
    return num1.real == num2.real && num1.imag == (-1 * num2.imag);
}

double complex_modulus_squared(ComplexNum num) {
   return num.real * num.real + num.imag * num.imag; 
}

ComplexNum complex_divide(ComplexNum num1, ComplexNum num2) {
    ComplexNum denom_conj = complex_conj(num2);
    ComplexNum numerator = complex_multiply(denom_conj, num1);
    double denom = complex_modulus_squared(num2);

    return (ComplexNum) {
        .real = numerator.real / denom,
        .imag = numerator.imag / denom
    };

} 

double complex_modulus(ComplexNum num) {
    return sqrt(complex_modulus_squared(num));
}

ComplexNum complex_scale(ComplexNum num, double scale) {
    return (ComplexNum) {
        .real = num.real * scale,
        .imag = num.imag * scale
    };
}

double complex_argument(ComplexNum num) {
    return atan2(num.imag, num.real);
}

ComplexNum complex_euler(double theta) {
    return (ComplexNum) {
        .real = cos(theta),
        .imag = sin(theta)
    };
}

ComplexNum complex_normalize(ComplexNum num) {
    double modulus = complex_modulus(num);
    
    return (ComplexNum) {
        .real = num.real / modulus,
        .imag = num.imag / modulus
    };
}

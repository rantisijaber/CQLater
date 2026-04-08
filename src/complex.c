#include "complex.h"
#include <math.h>

complex_num complex_add(complex_num num1, complex_num num2) {
    return (complex_num) {
        .real = num1.real + num2.real,
        .imag = num1.imag + num2.imag
    };
}

complex_num complex_subtract(complex_num num1, complex_num num2) {
    return (complex_num) {
        .real = num1.real - num2.real,
        .imag = num1.imag - num2.imag
    };
}

complex_num complex_multiply(complex_num num1, complex_num num2) {
    double real_product = num1.real * num2.real;
    double mix1 = num1.real * num2.imag;
    double mix2 = num1.imag * num2.real;
    double imag_product = -1 * (num1.imag * num2.imag);
    
    return (complex_num) {
        .real = real_product + imag_product,
        .imag = mix1 + mix2
    };
}

complex_num complex_conj(complex_num num) {
    return (complex_num) {
        .real = num.real,
        .imag = -1 * num.imag
    };
}

bool complex_conj_check(complex_num num1, complex_num num2) {
    return num1.real == num2.real && num1.imag == (-1 * num2.imag);
}

double complex_modulus_squared(complex_num num) {
   return num.real * num.real + num.imag * num.imag; 
}

complex_num complex_divide(complex_num num1, complex_num num2) {
    complex_num denom_conj = complex_conj(num2);
    complex_num numerator = complex_multiply(denom_conj, num1);
    double denom = complex_modulus_squared(num2);

    return (complex_num) {
        .real = numerator.real / denom,
        .imag = numerator.imag / denom
    };

} 

double complex_modulus(complex_num num) {
    return sqrt(complex_modulus_squared(num));
}

complex_num complex_scale(complex_num num, double scale) {
    return (complex_num) {
        .real = num.real * scale,
        .imag = num.imag * scale
    };
}

double complex_argument(complex_num num) {
    return atan2(num.imag, num.real);
}

complex_num complex_euler(double theta) {
    return (complex_num) {
        .real = cos(theta),
        .imag = sin(theta)
    };
}

complex_num complex_normalize(complex_num num) {
    double modulus = complex_modulus(num);
    
    return (complex_num) {
        .real = num.real / modulus,
        .imag = num.imag / modulus
    };
}

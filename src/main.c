#include <stdio.h>
#include "../include/rational.h"

int main() {
    rational_t a, b, c;
    
    rational_create(1, 2, &a);
    rational_create(1, 3, &b);
    
    printf("a = %lld/%lld\n", a.numerator, a.denominator);
    printf("b = %lld/%lld\n", b.numerator, b.denominator);
    
    rational_add(&a, &b, &c);
    printf("a + b = %lld/%lld = %.3f\n", c.numerator, c.denominator, rational_to_double(&c));
    
    rational_mul(&a, &b, &c);
    printf("a * b = %lld/%lld = %.3f\n", c.numerator, c.denominator, rational_to_double(&c));
    
    return 0;
}

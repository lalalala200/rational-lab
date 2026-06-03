#include <stdio.h>
#include <assert.h>
#include "../include/rational.h"

int main() {
    rational_t a, b, c;
    
    // Test create and normalize
    assert(rational_create(2, 4, &a) == RATIONAL_OK);
    assert(a.numerator == 1 && a.denominator == 2);
    
    rational_create(1, 3, &b);
    
    // Test add
    rational_add(&a, &b, &c);
    assert(c.numerator == 5 && c.denominator == 6);
    
    // Test mul
    rational_mul(&a, &b, &c);
    assert(c.numerator == 1 && c.denominator == 6);
    
    // Test error handling
    assert(rational_create(1, 0, &c) == RATIONAL_ERROR_INVALID_DENOM);
    
    printf("All C tests passed!\n");
    return 0;
}

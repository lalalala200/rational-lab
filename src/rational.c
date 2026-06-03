#include "../include/rational.h"
#include <stdlib.h>

static long long gcd(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

rational_error_t rational_create(long long num, long long den, rational_t *result) {
    if (!result) return RATIONAL_ERROR_NULL;
    if (den == 0) return RATIONAL_ERROR_INVALID_DENOM;
    
    result->numerator = num;
    result->denominator = den;
    return rational_normalize(result);
}

void rational_free(rational_t *r) {
    (void)r;
}

rational_error_t rational_normalize(rational_t *r) {
    if (!r) return RATIONAL_ERROR_NULL;
    if (r->denominator == 0) return RATIONAL_ERROR_INVALID_DENOM;
    
    long long g = gcd(r->numerator, r->denominator);
    r->numerator /= g;
    r->denominator /= g;
    
    if (r->denominator < 0) {
        r->numerator = -r->numerator;
        r->denominator = -r->denominator;
    }
    
    return RATIONAL_OK;
}

rational_error_t rational_add(const rational_t *a, const rational_t *b, rational_t *result) {
    if (!a || !b || !result) return RATIONAL_ERROR_NULL;
    
    result->numerator = a->numerator * b->denominator + b->numerator * a->denominator;
    result->denominator = a->denominator * b->denominator;
    return rational_normalize(result);
}

rational_error_t rational_sub(const rational_t *a, const rational_t *b, rational_t *result) {
    if (!a || !b || !result) return RATIONAL_ERROR_NULL;
    
    result->numerator = a->numerator * b->denominator - b->numerator * a->denominator;
    result->denominator = a->denominator * b->denominator;
    return rational_normalize(result);
}

rational_error_t rational_mul(const rational_t *a, const rational_t *b, rational_t *result) {
    if (!a || !b || !result) return RATIONAL_ERROR_NULL;
    
    result->numerator = a->numerator * b->numerator;
    result->denominator = a->denominator * b->denominator;
    return rational_normalize(result);
}

rational_error_t rational_div(const rational_t *a, const rational_t *b, rational_t *result) {
    if (!a || !b || !result) return RATIONAL_ERROR_NULL;
    if (b->numerator == 0) return RATIONAL_ERROR_DIV_ZERO;
    
    result->numerator = a->numerator * b->denominator;
    result->denominator = a->denominator * b->numerator;
    return rational_normalize(result);
}

int rational_cmp(const rational_t *a, const rational_t *b) {
    if (!a || !b) return 2;
    
    long long lhs = a->numerator * b->denominator;
    long long rhs = b->numerator * a->denominator;
    
    if (lhs < rhs) return -1;
    if (lhs > rhs) return 1;
    return 0;
}

double rational_to_double(const rational_t *r) {
    if (!r || r->denominator == 0) return 0.0;
    return (double)r->numerator / (double)r->denominator;
}

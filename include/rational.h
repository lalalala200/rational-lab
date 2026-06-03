#ifndef RATIONAL_H
#define RATIONAL_H

typedef enum {
    RATIONAL_OK = 0,
    RATIONAL_ERROR_NULL,
    RATIONAL_ERROR_DIV_ZERO,
    RATIONAL_ERROR_INVALID_DENOM
} rational_error_t;

typedef struct {
    long long numerator;
    long long denominator;
} rational_t;

rational_error_t rational_create(long long num, long long den, rational_t *result);
void rational_free(rational_t *r);
rational_error_t rational_normalize(rational_t *r);
rational_error_t rational_add(const rational_t *a, const rational_t *b, rational_t *result);
rational_error_t rational_sub(const rational_t *a, const rational_t *b, rational_t *result);
rational_error_t rational_mul(const rational_t *a, const rational_t *b, rational_t *result);
rational_error_t rational_div(const rational_t *a, const rational_t *b, rational_t *result);
int rational_cmp(const rational_t *a, const rational_t *b);
double rational_to_double(const rational_t *r);

#endif

#pragma once

typedef struct {
	int p;
	int q;
} Q_t;

typedef Q_t mpq_t[1];

void Q_canonicalize (Q_t *op);
char *Q_get_str(const Q_t op, int base);
Q_t Q_sub (const Q_t minuend, const Q_t subtrahend);
int Q_cmp (const Q_t op1, const Q_t op2);
int Q_cmp_i (const Q_t op1, int i);
Q_t Q_div (const Q_t dividend, const Q_t divisor);
Q_t Q_add (const Q_t addend1, const Q_t addend2);
Q_t Q_mul (const Q_t multiplier, const Q_t multiplicand);
double Q_get_d (const Q_t op);

static inline int Q_equal (const Q_t op1, const Q_t op2)
{
	return !Q_cmp(op1, op2);
}

static inline int Q_is_zero (const Q_t op)
{
	return !Q_cmp_i(op, 0);
}

#define Q_zero (Q_t) {0, 1}

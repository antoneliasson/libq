#include <stdlib.h>
#include <stdio.h>

#include "ratnum.h"
#include "dbg.h"

static int gcd(int a, int b) {
	int t;
	while (b != 0) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

void Q_canonicalize (Q_t *op)
{
	if (op->p == 0) {
		op->q = 1;
	} else {
		int g = abs(gcd(op->p, op->q));
		op->p /= g;
		op->q /= g;
		if (op->q < 0) {
			op->p = -op->p;
			op->q = -op->q;
		}
	}
}

char *Q_get_str(const Q_t op, int base)
{
	if (base != 10) {
		log_warn("not implemented");
	}
	int size = 0;
	char *fmt;
	char *p = NULL;

	if (op.q == 1) {
		fmt = "%d";
	} else {
		fmt = "%d/%d";
	}
	size = snprintf(p, 0, fmt, op.p, op.q);
	if (size < 0)
		return NULL;

	size++;
	p = malloc(size);
	size = snprintf(p, size, fmt, op.p, op.q);
	if (size < 0) {
		free(p);
		return NULL;
	}
	return p;
}

void Q_swap (Q_t rop1, Q_t rop2)
{
	int t;
	t = rop1.p;
	rop1.p = rop2.p;
	rop2.p = t;
	t = rop1.q;
	rop1.q = rop2.q;
	rop2.q = t;
}

Q_t Q_sub (const Q_t minuend, const Q_t subtrahend)
{
        Q_t difference;
	if (minuend.q == subtrahend.q) {
		difference.p = minuend.p - subtrahend.p;
		difference.q = minuend.q;
	} else {
		difference.p = minuend.p * subtrahend.q - subtrahend.p * minuend.q;
		difference.q = minuend.q * subtrahend.q;
	}
	Q_canonicalize(&difference);
	return difference;
}

int Q_cmp (const Q_t op1, const Q_t op2)
{
	Q_t t = Q_sub(op1, op2);
	return t.p;
}

int Q_cmp_i (const Q_t op1, int i)
{
	Q_t t;
	t.p = i;
	t.q = 1;
	return Q_cmp(op1, t);
}

Q_t Q_div (const Q_t dividend, const Q_t divisor)
{
        Q_t quotient;
	quotient.p = dividend.p * divisor.q;
	quotient.q = dividend.q * divisor.p;
	Q_canonicalize(&quotient);
	return quotient;
}

Q_t Q_add (const Q_t addend1, const Q_t addend2)
{
        Q_t sum;
	if (addend1.q == addend2.q) {
		sum.p = addend1.p + addend2.p;
		sum.q = addend1.q;
	} else {
		sum.p = addend1.p * addend2.q + addend2.p * addend1.q;
		sum.q = addend1.q * addend2.q;
	}
	Q_canonicalize(&sum);
	return sum;
}

Q_t Q_mul (const Q_t multiplier, const Q_t multiplicand)
{
        Q_t product;
	product.p = multiplier.p * multiplicand.p;
	product.q = multiplier.q * multiplicand.q;
	Q_canonicalize(&product);
	return product;
}

double Q_get_d (const Q_t op)
{
	return (double) op.p / op.q;
}

#include "fraction.h"

int NOD(int max, int min) {
	if(max < 0) max *= (-1);
	if(min < 0) min *= (-1);
	
	while(max != 0 && min != 0) {
		if(max > min) max = max % min;
		else min = min % max;
	}
	return (max + min);
}

void def_number(double n, double d, struct fractions *fr) {
	int k;
	if(d != 0) {
	k = NOD(n, d);
		fr->nu = n / k;
		fr->den = d / k;
	}
	else fr->den = 1;

	if((fr->nu < 0 && fr->den < 0) || (fr->den < 0)) {
		fr->nu *=(-1);
		fr->den *=(-1);
	}
}

int fractEq(struct fractions a, struct fractions b) {
	if(a.den == 0 || b.den == 0) return 0;
    if((double)a.nu / a.den == (double)b.nu / b.den) 
        return 1; 
    else 
        return 0;
}

int fractNotEq(struct fractions a, struct fractions b) {
	if(a.den == 0 || b.den == 0) return 0;
    if((double)a.nu / a.den != (double)b.nu / b.den) 
        return 1; 
    else 
        return 0;
}

int fractMore(struct fractions a, struct fractions b) {
	if(a.den == 0 || b.den == 0) return 0;
    if((double)a.nu / a.den > (double)b.nu / b.den) 
        return 1; 
    else 
        return 0;
}

int fractLess(struct fractions a, struct fractions b) {
	if(a.den == 0 || b.den == 0) return 0;
    if((double)a.nu / a.den < (double)b.nu / b.den) 
        return 1; 
    else 
        return 0;
}

struct fractions fractAdd(struct fractions a, struct fractions b) {
	struct fractions t;
	int k, l, d;
	if (a.den == b.den) {
		t.nu = a.nu + b.nu;
		t.den = a.den;	
	}
	else {
		t.nu = a.nu * b.den + a.den * b.nu;
		t.den = a.den * b.den;
	}
	l = t.nu;
	d = t.den;
	k = NOD(l, d);
	t.nu = l / k;
	t.den = d / k;
	return t;
}

struct fractions fractSub(struct fractions a, struct fractions b) {
	struct fractions t;
	int k, l, d;
	if (a.den == b.den) {
		t.nu = a.nu - b.nu;
		t.den = a.den;	
	}
	else {
		t.nu = a.nu * b.den - a.den * b.nu;
		t.den = a.den * b.den;
	}
	l = t.nu;
	d = t.den;
	k = NOD(l, d);
	t.nu = l / k;
	t.den = d / k;
	return t;
}

struct fractions fractMul(struct fractions a, struct fractions b) {
	struct fractions t;
	int k, l, d;
	t.nu = a.nu * b.nu;
	t.den = a.den * b.den;
	if (t.nu < 0 && t.den < 0) {
		t.nu *= (-1);
		t.den *= (-1);
	}
	else if (t.den < 0){
		t.nu *= (-1);
		t.den *= (-1);		
	}
	l = t.nu;
	d = t.den;
	k = NOD(l, d);
	t.nu = l / k;
	t.den = d / k;
	return t;	
}

struct fractions fractDiv(struct fractions a, struct fractions b) {
	struct fractions t;
	int k, l, d;
	t.nu = a.nu * b.den;
	t.den = a.den * b.nu;
	if (t.nu < 0 && t.den < 0) {
		t.nu *= (-1);
		t.den *= (-1);
	}
	else if (t.den < 0){
		t.nu *= (-1);
		t.den *= (-1);		
	}
	l = t.nu;
	d = t.den;
	k = NOD(l, d);
	t.nu = l / k;
	t.den = d / k;
	return t;	
}

struct fractions fractAddInt(struct fractions a, int b) {	
	struct fractions frac;
	frac.nu = b;
	frac.den = 1;
	return fractAdd(a, frac);
}

struct fractions fractSubInt(struct fractions a, int b) {	
	struct fractions frac;
	frac.nu = b;
	frac.den = 1;
	return fractDiv(a, frac);
}

struct fractions fractMulInt(struct fractions a, int b) {	
	struct fractions frac;
	if(a.nu != 0){
		frac.nu = b;
	    frac.den = 1;
	}
	return fractMul(a, frac);	
}

struct fractions fractDivInt(struct fractions a, int b) {	
	struct fractions frac;
	if(a.nu != 0){
		frac.nu = b;
	    frac.den = 1;
	}
	return fractDiv(a, frac);
}

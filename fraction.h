#ifndef _FRACTION_
#define _FRACTION_

#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <malloc.h>

struct fractions {
    int nu;
    int den;
};

//int n, m;

int NOD(int, int);
void def_number(double, double, struct fractions *);
int fractEq(struct fractions, struct fractions);
int fractNotEq(struct fractions, struct fractions);
int fractMore(struct fractions, struct fractions);
int fractLess(struct fractions, struct fractions);
struct fractions fractAdd(struct fractions, struct fractions);
struct fractions fractSub(struct fractions, struct fractions);
struct fractions fractMul(struct fractions, struct fractions);
struct fractions fractDiv(struct fractions, struct fractions);
struct fractions fractAddInt(struct fractions, int);
struct fractions fractSubInt(struct fractions, int);
struct fractions fractMulInt(struct fractions, int);
struct fractions fractDivInt(struct fractions, int);

int rect(struct fractions **, int *, int, int);
void newZ(int *, struct fractions **, struct fractions *, int, int);
int bazis_line(int *, int, int);
int in_bazis(int *, int, int);
int opt(struct fractions *, int);
int max_mod_Z (struct fractions *, int);
int min_Q(struct fractions *, int);

void simplex_met(int *, struct fractions **, struct fractions *, struct fractions *, int, int);
void print(struct fractions **, int, int);
void print_simplex_table(int *, struct fractions **, struct fractions *, struct fractions *, int, int, int);
void copy(struct fractions **, struct fractions **, int, int);

#endif
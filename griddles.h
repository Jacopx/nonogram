//
//  griddles.h
//  eser10_1
//
//  Created by Jacopo Nasi on 08/12/15.
//  Copyright © 2015 Jacopo Nasi. All rights reserved.
//

#ifndef griddles_h
#define griddles_h

#include <stdio.h>

typedef struct {
    int **row, N;
    int **col, M;
} rules;

rules* read_ru(char *sr);
void read_f(FILE *fp, rules *rules);
void printR(rules *all);
void solv_puzz(rules *all);
void charge(int **chessb, rules *all);
int disp_sempl(int pos, int *val, int *sol, int *mark, int n, int k, int count, rules *all);
int good(rules *all, int *sol);
void powerset_disp_rep(int pos, int *val, int *sol, int k, rules *all);
int powerset(int pos, int *val, int *sol, int k, int start, int count, rules *all);

#endif /* griddles_h */

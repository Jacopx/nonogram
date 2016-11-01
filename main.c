//
//  main.c - Nonogram Solver by Jacopo Nasi

#include <stdio.h>
#include "griddles.h"

int main(int argc, char **argv) {
    rules *all;
    all=read_ru(argv[1]);
    //printR(all);
    solv_puzz(all);
    return 0;
}


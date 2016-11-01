//
//  main.c
//  eser10_1
//
//  Created by Jacopo Nasi on 08/12/15.
//  Copyright © 2015 Jacopo Nasi. All rights reserved.
//

#include <stdio.h>
#include "griddles.h"

int main(int argc, char **argv) {
    rules *all;
    all=read_ru(argv[1]);
    //printR(all);
    solv_puzz(all);
    return 0;
}


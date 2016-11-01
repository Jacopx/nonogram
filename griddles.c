//
//  griddles.c - Nonogram Solver by Jacopo Nasi

#include "griddles.h"

#include <stdio.h>
#include <stdlib.h>

rules* read_ru(char *sr) {
    FILE* fp=fopen(sr, "r");
    if(fp==NULL)
        exit(5);
    
    rules *rules=malloc(sizeof(*rules));
    read_f(fp, rules);
    printf("Lettura: SUCCESS\n");
    return rules;
}

void read_f(FILE *fp, rules *rules) {
    int i,j,t;
    fscanf(fp, "%d", &rules->N);
    rules->row=malloc(rules->N*sizeof(int*));
    for(i=0;i<rules->N;i++)
    {
        fscanf(fp, "%d", &t);
        rules->row[i]=malloc(t*sizeof(int));
        rules->row[i][0]=t;
        for(j=1;j<=rules->row[i][0];j++)
        {
            fscanf(fp, "%d", &rules->row[i][j]);
        }
    }
    fscanf(fp, "%d", &rules->M);
    rules->col=malloc(rules->M*sizeof(int*));
    for(i=0;i<rules->M;i++)
    {
        fscanf(fp, "%d", &t);
        rules->col[i]=malloc(t*sizeof(int));
        rules->col[i][0]=t;
        for(j=1;j<=rules->col[i][0];j++)
        {
            fscanf(fp, "%d", &rules->col[i][j]);
        }
    }
}

void printR(rules *all) {
    int t, i, j;
    
    printf("%d\n", all->N);
    for(i=0;i<all->N;i++)
    {
        t=all->row[i][0];
        for(j=0;j<=t;j++)
        {
            printf("%d ", all->row[i][j]);
        }
        printf("\n");
    }
    
    printf("----------\n");
    
    printf("%d\n", all->M);
    for(i=0;i<all->M;i++)
    {
        t=all->col[i][0];
        for(j=0;j<=t;j++)
        {
            printf("%d ", all->col[i][j]);
        }
        printf("\n");
    }
}

void solv_puzz(rules *all) {
    int **chessb=malloc(all->N*sizeof(int *)), i, j, count;
    for(i=0;i<all->N;i++)
        chessb[i]=malloc(all->M*sizeof(int));
    
    for(i=0;i<all->N;i++)
        for(j=0;j<all->M;j++)
        chessb[i][j]=0;
    
    charge(chessb, all);
    int *chessvet=malloc(all->N*all->M*sizeof(int));
    int *mark=malloc(all->N*all->M*sizeof(int));
    int *sol=malloc(all->N*all->M*sizeof(int));
    for(i=0;i<all->N;i++)
        for(j=0;j<all->M;j++)
        {
            chessvet[i*all->N+j]=chessb[i][j];
            mark[i*all->N+j]=0;
            sol[i*all->N+j]=0;
        }

    //printf("Soluzioni provate: %d", disp_sempl(0, chessvet, sol, mark, (all->N*all->M), (all->N*all->M), count, all));
    //powerset_disp_rep(0, chessvet, sol, (all->N*all->M), all);
    powerset(0, chessvet, sol, (all->N*all->M), 0, 0, all);
}

void charge(int **chessb, rules *all) {
    int i, j, t=0, x=0;
    for(i=0;i<all->N;i++)
    {
        for(j=0;j<all->row[i][0];j++)
        {
            while(t<all->row[i][j+1])
            {
                chessb[i][x]=1;
                t++; x++;
            }
            t=0;
        }
        x=0;
    }
}

int disp_sempl(int pos, int *val, int *sol, int *mark, int n, int k, int count, rules *all) {
    int i;
    if (pos >= k) {
        if(good(all,sol)==0)
        {
            for (i=0; i<k; i++)
                printf("%d ", sol[i]);
            printf("\n");
        }
        return count+1;
    }
    for (i=0; i<n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            count = disp_sempl(pos+1, val, sol, mark, n, k, count, all);
            mark[i] = 0;
        }
    }
    return count;
}

int good(rules *all, int *sol) {
    
    int *riga=malloc(all->M*sizeof(int)), pos=0, i=0, j=0, x=0;
    for(i=0; i<all->N; i++)
    {
        for(j=0; j<all->M; j++)
        {
            if(sol[i*all->N+j]==1)
                riga[pos]++;
            if(riga[pos]>1 && sol[i*all->N+j]==0)
                pos++;
        }
        pos=0;
        for(x=0;x<all->row[i][0];x++)
        {
            if(all->row[i][x]!=riga[x])
                {free(riga); return 1;}
        }
    }
    free(riga);
    
    int *colonna=malloc(all->M*sizeof(int));
    for(i=0; i<all->M; i++)
    {
        for(j=0; j<all->N; j++)
        {
            if(sol[j*all->M+i]==1)
                colonna[pos]++;
            if(colonna[pos]>1 && sol[j*all->M+i]==0)
                pos++;
        }
        pos=0;
        for(x=0;x<all->col[i][0];x++)
        {
            if(all->col[i][x]!=colonna[x])
               {free(colonna); return 1;}
        }
    }
    return 0;
}

void powerset_disp_rep(int pos, int *val, int *sol, int k, rules *all) {
    int j;
    
    if (pos >= k) {
        if(good(all,sol)==0)
        {
            printf("{ ");
            for (j=0; j<k; j++)
                if (sol[j]!=0)
                    printf("%d ", val[j]);
            printf("} \n");
        }
        return;
    }
    
    sol[pos] = 0;
    powerset_disp_rep(pos+1, val, sol, k, all);
    sol[pos] = 1;
    powerset_disp_rep(pos+1, val, sol, k, all);
}

int powerset(int pos, int *val, int *sol, int k, int start, int count, rules *all) {
    int i;
    if (start >= k) {
        if(good(all,sol)==0)
        {
        for (i = 0; i < pos; i++)
            printf("%d ", sol[i]);
        printf("\n");
        
        }
        return count+1;
    }
    for (i = start; i < k; i++) {
        sol[pos] = val[i];
        count = powerset(pos+1, val, sol, k, i+1, count, all);
    }
    count = powerset(pos, val, sol, k, k, count, all);
    return count;
}
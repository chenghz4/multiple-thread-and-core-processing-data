#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <pthread.h>

#include "p1_process.h"

extern double aver,median,var;

using namespace std;


struct value{
string id;
double grade;
};

extern value data[1000000];
void start_thread(int num,int size,value *p);
void merge(value a[],int x,int z);
void mergefinal(value a[],int x, int y, int z);
//void mergefinal1(value a[], int num);

#endif

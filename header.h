#include <stdio.h>
#include <math.h>
extern "C" {
#include <cblas.h>
}
#include <pthread.h>

#define TOT_NUM 50000
#define TOT_VAL 10000
#define TOT_TES 10000
#define PIXELS 784
#define NUM_COL 28
#define NLAYERS 2
#define TOT_RES 10

#define ALPHA 1.0
#define BTA 0.0
#define INCX 1
#define INCY 1

#define SEED 23457495
#define EPOCHS 50
#define MINI_BATCH_SIZE 30
#define BETA 0.9
#define H_N 512
#define ETA 0.01
#define LAMBDA 0
#define NUM_THREADS 1
#define NUM_MEMBERS 1

float tdata[TOT_NUM][PIXELS];
int tlabels[TOT_NUM];
float vdata[TOT_VAL][PIXELS];
int vlabels[TOT_VAL];
float rdata[TOT_TES][PIXELS];
int rlabels[TOT_TES];
void load_training_data();
void load_testing_data();


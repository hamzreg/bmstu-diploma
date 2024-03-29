#ifndef __ENTROPY_H__
#define __ENTROPY_H__

#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define BYTES_NUM 256
#define BITS_NUM 8

#define MSG_LEN 4

#define PAGE_SIZE_POW 12

#define LOG 0
#define LOG4 1


int get_sw_entropy(const unsigned char *const src,
                   const int type_log);

long long get_binomial_entropy(const unsigned char *const src,
                         const int type_log);

int get_khamzina_entropy(const unsigned char *const src,
                         const int type_log);

#endif

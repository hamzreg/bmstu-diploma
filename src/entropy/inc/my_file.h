#ifndef __MY_FILE_H__
#define __MY_FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../inc/codes.h"
#include "../inc/entropy.h"

#define SW_ENTROPY 0
#define BINOMAL_ENTROPY 1
#define KHAMZINA_ENTROPY 2

int analyze_file(const char *const file_name, 
                 const int entropy_method, const int type_log);

#endif

#include <stdio.h>

#include "../inc/codes.h"
#include "../inc/my_file.h"

#define ARG_NUM 4
#include <math.h>

int main(int argc, char **argv)
{
    if (argc != ARG_NUM)
    {
        printf("Нужно задать путь к файлу и метод энтропии.\n");
        return ERROR_ARGC;
    }

    return analyze_file(argv[1], atoi(argv[2]), atoi(argv[3]));
}

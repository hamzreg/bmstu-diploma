#include "../inc/entropy.h"

int log2_w(const int value, const int type_log)
{
    /* 
     * это дает неправильные результаты
     * возможно из-за того, что log2 работает с double
     * log2l аналогично
    */
    if (type_log == LOG4)
        return log2(value * value * value * value);

    return log2(value);
}

int get_sw_entropy(const unsigned char *const src,
                   const int type_log)
{
    long page_size = sysconf(_SC_PAGESIZE);
    int bytes_frequency[BYTES_NUM] = { 0 };

    for (int i = 0; i < page_size; ++i)
        bytes_frequency[src[i]]++;

    int a = log2_w(page_size, type_log);
    int entropy_sum = 0;

    for (int i = 0; i < BYTES_NUM; ++i) 
    {
        double probability = bytes_frequency[i];

        if (probability > 0)
            entropy_sum += probability * (a - log2_w(probability, type_log));
    }

    return entropy_sum;
}

int get_binomial_entropy(const unsigned char *const src,
                         const int type_log)
{
    long page_size = sysconf(_SC_PAGESIZE);
    int units_number = 0;

    for (int i = 0; i < page_size; ++i) 
        for (int j = 0; j < BITS_NUM; ++j) 
            units_number += (src[i] >> (BITS_NUM - j - 1)) & 0x01;

    // непонятно, как получать вероятности появления единицы и нуля
    int zero_number = (page_size * BITS_NUM - units_number) / page_size;
    units_number /= page_size;

    int binomial_factors[BITS_NUM + 1] = {1, 8, 28, 56, 70, 56, 28, 8, 1};

    // значения p и size большие
    unsigned long long size = pow(page_size, BITS_NUM);
    unsigned long long a = log2_w(size, type_log);
    unsigned long long entropy_sum = 0;

    for (int i = 0; i < BITS_NUM + 1; ++i) 
    {
        int p = 1;

        for  (int j = 0; j < i; ++j)
            p *= units_number;

        for  (int j = 0; j < BITS_NUM - i; ++j)
            p *= zero_number;

        // если p = 0, log2 возвращает -inf

        entropy_sum += binomial_factors[i] * p * (a - log2_w(p, type_log)); 
    }

    return entropy_sum;
}
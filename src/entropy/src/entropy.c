#include "../inc/entropy.h"

unsigned long long log2_w(const unsigned long long value, const int type_log)
{
    /* 
     * это дает неправильные результаты
     * возможно из-за того, что log2 работает с double
     * log2l аналогично
    */
    if (type_log == LOG4)
        return log2(value * value * value * value);

    return log2l(value);
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

long long get_binomial_entropy(const unsigned char *const src,
                         const int type_log)
{
    long page_size = sysconf(_SC_PAGESIZE);
    int units_number = 0;

    for (int i = 0; i < page_size; ++i) 
        for (int j = 0; j < BITS_NUM; ++j) 
            units_number += (src[i] >> (BITS_NUM - j - 1)) & 0x01;
    
    int max_bits_num = page_size * BITS_NUM;
    units_number = units_number * 100 / max_bits_num;
    int zero_number = 100 - units_number;

    //int binomial_factors[MSG_LEN + 1] = {1, 8, 28, 56, 70, 56, 28, 8, 1};
    int binomial_factors[MSG_LEN + 1] = {1, 4, 6, 4, 1};
    //int binomial_factors[MSG_LEN + 1] = {1, 2, 1};

    unsigned long long size = pow(100, MSG_LEN);
    unsigned long long a = log2_w(size, type_log);
    long long entropy_sum = 0;

    if (units_number == 0 || zero_number == 0)
        return entropy_sum;

    for (int i = 0; i < MSG_LEN + 1; ++i) 
    {
        unsigned long long p = 1;

        for  (int j = 0; j < i; ++j)
            p *= units_number;

        for  (int j = 0; j < MSG_LEN - i; ++j)
            p *= zero_number;

        entropy_sum += binomial_factors[i] * p * (a - log2_w(p, type_log));
    }

    return entropy_sum;
}

int get_khamzina_entropy(const unsigned char *const src,
                         const int type_log)
{
    long page_size = sysconf(_SC_PAGESIZE);
    int logs[PAGE_SIZE_POW + 1] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 4096};

    int bytes_frequency[BYTES_NUM] = { 0 };

    for (int i = 0; i < page_size; ++i)
        bytes_frequency[src[i]]++;

    int entropy_sum = 0;
    int j = 0;

    for (int i = 0; i < BYTES_NUM; ++i) 
    {
        double p = bytes_frequency[i];

        if (p > 0)
        {
            for (j = 0; p > logs[j]; j++) {
            }

            entropy_sum += p * (PAGE_SIZE_POW - j);
        }
    }

    return entropy_sum;
}

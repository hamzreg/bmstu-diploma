#include "../inc/my_file.h"


static inline int get_file_size(FILE *file, long *const file_size)
{
    if (fseek(file, 0, SEEK_END))
        return FILE_ERROR;

    *file_size = ftell(file);

    if (fseek(file, 0, SEEK_SET))
        return FILE_ERROR;

    printf("Размер файла: %lu байтов.\n", *file_size);
    return OK;
}

int analyze_file(const char *const file_name, const int entropy_method,
                 const int type_log)
{
    FILE *file = fopen(file_name, "rb");

    if (file == NULL)
    {
        printf("Не удалось открыть файл.\n");
        return FILE_ERROR;
    }

    long file_size = 0;
    int rc = get_file_size(file, &file_size);

    if (rc != OK)
    {
        fclose(file);
        return rc;
    }

    long page_size = sysconf(_SC_PAGESIZE);
    long data_size = file_size + page_size - (file_size % page_size);
    printf("Размер данных: %lu байтов.\n", data_size);
    printf("Число страниц: %ld.\n\n", data_size / page_size);

    unsigned char *data = (unsigned char*)calloc(data_size, sizeof(unsigned char));

    if (data ==  NULL)
    {
        printf("Не удалось выделить память.\n");

        fclose(file);
        return MEMORY_ERROR;
    }

    size_t read_num = fread(data, sizeof(unsigned char), 
                            file_size, file);
    fclose(file);

    if (read_num != file_size)
    {
        printf("Не удалось считать данные.\n");
        return DATA_ERROR;
    }

    long size = pow(page_size, BITS_NUM);

    for (int i = 0; i < data_size / page_size; ++i)
    {
        printf("Страница %d:\n", i + 1);
        int entropy_sum = 0;
        

        if (entropy_method == SW_ENTROPY)
            entropy_sum = get_sw_entropy(data + page_size * (i + 1), type_log);
        else
            entropy_sum = get_binomial_entropy(data + page_size * (i + 1), type_log);

        printf("- /PAGE_SIZE: %d\n", entropy_sum);

        if (entropy_method == SW_ENTROPY)
            printf("+ /PAGE_SIZE: %ld\n\n", entropy_sum / page_size);
        else
            printf("+ /PAGE_SIZE: %ld\n\n", entropy_sum / size);
    }

    free(data);

    return OK;
}

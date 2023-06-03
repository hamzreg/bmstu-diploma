#define PAGE_SIZE_POW 12
#define BYTES_NUM 256

static inline s32 get_entropy(const u8 *src)
{
    u16 logs[PAGE_SIZE_POW + 1] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 4096};
    u16 bytes_frequency[BYTES_NUM] = { 0 };
    u32 i, j;

    for (i = 0; i < PAGE_SIZE; ++i) {
        bytes_frequency[src[i]]++;
    }

    s32 entropy = 0;

    for (i = 0; i < BYTES_NUM; ++i) {
        s32 k = bytes_frequency[i];

        if (k > 0) {
            j = 0;
            
            while (k > logs[j])
                j++;

            entropy += k * (PAGE_SIZE_POW - logs[j]);
        }
    }

    return entropy;
}

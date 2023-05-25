#define BYTES_NUM 256

static inline u32 ilog2_w(u64 n)
{
	return ilog2(n * n * n * n);
}

static inline s32 get_sw_entropy(const u8 *src)
{
    u16 bytes_frequency[BYTES_NUM] = { 0 };
    u32 i;

    for (i = 0; i < PAGE_SIZE; ++i) {
        bytes_frequency[src[i]]++;
    }

    u32 page_size = ilog2_w(PAGE_SIZE);
    s32 entropy = 0;

    for (i = 0; i < BYTES_NUM; ++i) {
        s32 probability = bytes_frequency[i];

        if (probability > 0) {
            entropy += probability * (page_size - ilog2_w((u64)probability));
        }
    }

    return entropy;
}

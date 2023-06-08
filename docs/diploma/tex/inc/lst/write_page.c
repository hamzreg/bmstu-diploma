static int __zram_bvec_write(struct zram *zram, 
    struct bio_vec *bvec, u32 index, struct bio *bio)
{
    ...
    unsigned int comp_len = 0;
    void *src, *dst, *mem;
    struct zcomp_strm *zstrm;
    struct page *page = bvec->bv_page;
    ...
compress_again:
    zstrm = zcomp_stream_get(zram->comp);
    src = kmap_atomic(page);
    if (get_entropy((const u8 *)src) < ENTROPY_LIMIT)
        ret = zcomp_compress(zstrm, src, &comp_len);
    else
        comp_len = PAGE_SIZE;
    ...
}

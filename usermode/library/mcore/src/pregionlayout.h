#ifndef _PERSISTENT_REGION_LAYOUT
#define _PERSISTENT_REGION_LAYOUT


/* 
 * We reserve a large hole in the 47-bit virtual space for mapping 
 * persistent memory segments.
 * FIXME: Even if we ensure persistent segments fall into the reserved space,
 * the kernel has to be aware about this reservation to make sure that no other 
 * memory is allocated there. Indead, when mmap is passed 0 as starting
 * address, it searches for an empty region starting from the end of the last
 * allocated region. So it could be very easily map a non-persistent region 
 * into the reserved space.
 *
 * Each region must be page aligned. We use PAGE_ALIGN to accomblish this.
 *
 * The end address of the region is not included in the region. More formally,
 * given a start and end address, the region is defined as [start, end) .
 *
 */

#define PSEGMENT_RESERVED_REGION_START   0x0000100000000000
#define PSEGMENT_RESERVED_REGION_SIZE    0x0000010000000000 /* 1 TB */
#define PSEGMENT_RESERVED_REGION_END     (PSEGMENT_RESERVED_REGION_START +    \
                                          PSEGMENT_RESERVED_REGION_SIZE)
/* Segment table */
#define SEGMENT_TABLE_START              PSEGMENT_RESERVED_REGION_START
#define SEGMENT_TABLE_NUM_ENTRIES        1024
#define SEGMENT_TABLE_SIZE               (sizeof(m_segtbl_entry_t) *          \
                                          SEGMENT_TABLE_NUM_ENTRIES)

#define SEGMENT_TABLE_HOLE               0x10000
#define SEGMENT_TABLE_END                PAGE_ALIGN(                          \
                                             SEGMENT_TABLE_START +            \
                                             SEGMENT_TABLE_HOLE +             \
                                             SEGMENT_TABLE_SIZE)
/* Log pool */										  
#define LOG_POOL_START                   SEGMENT_TABLE_END 
#define LOG_POOL_SIZE                    (32*16*1024*1024+32*32*64)
#define LOG_POOL_HOLE                    0x10000
#define LOG_POOL_END                     PAGE_ALIGN(                          \
                                             LOG_POOL_START +                 \
                                             LOG_POOL_HOLE +                  \
										     LOG_POOL_SIZE)
/* pmap segments start addr */										  
#define SEGMENT_MAP_START                LOG_POOL_END



#endif /* _PERSISTENT_REGION_LAYOUT */
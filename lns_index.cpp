#include <arm_neon.h>
#include <stdint.h>
#define F_BITS 3

__attribute__((always_inline)) inline void lns_mitchell_accumulate_16(int8x16_t p, int32x4_t& c0, int32x4_t& c1, int32x4_t& c2, int32x4_t& c3) {
    int8x16_t q = vshrq_n_s8(p, F_BITS);
    int8x16_t r = vandq_s8(p, vdupq_n_s8((1<<F_BITS)-1));
    int32x4_t cte = vdupq_n_s32(1<<F_BITS);
    c0 = vaddq_s32(c0, vshlq_s32(vaddq_s32(cte, vmovl_s16(vget_low_s16(vmovl_s8(vget_low_s8(r))))), vmovl_s16(vget_low_s16(vmovl_s8(vget_low_s8(q))))));
    c1 = vaddq_s32(c1, vshlq_s32(vaddq_s32(cte, vmovl_s16(vget_high_s16(vmovl_s8(vget_low_s8(r))))), vmovl_s16(vget_high_s16(vmovl_s8(vget_low_s8(q))))));
    c2 = vaddq_s32(c2, vshlq_s32(vaddq_s32(cte, vmovl_s16(vget_low_s16(vmovl_s8(vget_high_s8(r))))), vmovl_s16(vget_low_s16(vmovl_s8(vget_high_s8(q))))));
    c3 = vaddq_s32(c3, vshlq_s32(vaddq_s32(cte, vmovl_s16(vget_high_s16(vmovl_s8(vget_high_s8(r))))), vmovl_s16(vget_high_s16(vmovl_s8(vget_high_s8(q))))));
}

extern "C" void lns_search_flat(int N, int D, const int8_t* query, const int8_t* db, int32_t* scores) {
    for(int i=0; i<N; ++i) {
        int32x4_t c0=vdupq_n_s32(0), c1=vdupq_n_s32(0), c2=vdupq_n_s32(0), c3=vdupq_n_s32(0);
        const int8_t* db_v = db + i*D;
        #pragma GCC unroll 4
        for(int d=0; d<D; d+=16) {
            lns_mitchell_accumulate_16(vaddq_s8(vld1q_s8(query+d), vld1q_s8(db_v+d)), c0, c1, c2, c3);
        }
        scores[i] = vaddvq_s32(c0) + vaddvq_s32(c1) + vaddvq_s32(c2) + vaddvq_s32(c3);
    }
}

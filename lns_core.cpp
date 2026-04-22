#include <arm_neon.h>
#include <stdint.h>
#include <stdlib.h>

#define F_BITS 3

__attribute__((always_inline)) inline void lns_mitchell_accumulate_16(
    int8x16_t p_matrix,
    int32x4_t& c0, int32x4_t& c1, int32x4_t& c2, int32x4_t& c3)
{
    const int8x16_t mask_f = vdupq_n_s8((1 << F_BITS) - 1);
    int8x16_t q = vshrq_n_s8(p_matrix, F_BITS);
    int8x16_t r = vandq_s8(p_matrix, mask_f);

    int16x8_t q_low16  = vmovl_s8(vget_low_s8(q));
    int16x8_t q_high16 = vmovl_s8(vget_high_s8(q));
    int16x8_t r_low16  = vmovl_s8(vget_low_s8(r));
    int16x8_t r_high16 = vmovl_s8(vget_high_s8(r));

    int32x4_t q0 = vmovl_s16(vget_low_s16(q_low16));
    int32x4_t q1 = vmovl_s16(vget_high_s16(q_low16));
    int32x4_t q2 = vmovl_s16(vget_low_s16(q_high16));
    int32x4_t q3 = vmovl_s16(vget_high_s16(q_high16));

    int32x4_t r0 = vmovl_s16(vget_low_s16(r_low16));
    int32x4_t r1 = vmovl_s16(vget_high_s16(r_low16));
    int32x4_t r2 = vmovl_s16(vget_low_s16(r_high16));
    int32x4_t r3 = vmovl_s16(vget_high_s16(r_high16));

    int32x4_t cte = vdupq_n_s32(1 << F_BITS);
    int32x4_t lin0 = vshlq_s32(vaddq_s32(cte, r0), q0);
    int32x4_t lin1 = vshlq_s32(vaddq_s32(cte, r1), q1);
    int32x4_t lin2 = vshlq_s32(vaddq_s32(cte, r2), q2);
    int32x4_t lin3 = vshlq_s32(vaddq_s32(cte, r3), q3);

    c0 = vaddq_s32(c0, lin0);
    c1 = vaddq_s32(c1, lin1);
    c2 = vaddq_s32(c2, lin2);
    c3 = vaddq_s32(c3, lin3);
}

extern "C" {
    void lns_mac_neon_16x4(int kc_depth, const int8_t* a_pack, const int8_t* b_pack, int32_t* c_tile) {
        int32x4_t c00 = vdupq_n_s32(0), c01 = vdupq_n_s32(0), c02 = vdupq_n_s32(0), c03 = vdupq_n_s32(0);
        int32x4_t c10 = vdupq_n_s32(0), c11 = vdupq_n_s32(0), c12 = vdupq_n_s32(0), c13 = vdupq_n_s32(0);
        int32x4_t c20 = vdupq_n_s32(0), c21 = vdupq_n_s32(0), c22 = vdupq_n_s32(0), c23 = vdupq_n_s32(0);
        int32x4_t c30 = vdupq_n_s32(0), c31 = vdupq_n_s32(0), c32 = vdupq_n_s32(0), c33 = vdupq_n_s32(0);

        #pragma GCC unroll 4
        for (int p = 0; p < kc_depth; ++p) {
            int8x16_t a_vec = vld1q_s8(a_pack);
            a_pack += 16;

            int8x16_t b_vec0 = vdupq_n_s8(b_pack[0]);
            int8x16_t b_vec1 = vdupq_n_s8(b_pack[1]);
            int8x16_t b_vec2 = vdupq_n_s8(b_pack[2]);
            int8x16_t b_vec3 = vdupq_n_s8(b_pack[3]);
            b_pack += 4;

            int8x16_t p0 = vaddq_s8(a_vec, b_vec0);
            int8x16_t p1 = vaddq_s8(a_vec, b_vec1);
            int8x16_t p2 = vaddq_s8(a_vec, b_vec2);
            int8x16_t p3 = vaddq_s8(a_vec, b_vec3);

            lns_mitchell_accumulate_16(p0, c00, c01, c02, c03);
            lns_mitchell_accumulate_16(p1, c10, c11, c12, c13);
            lns_mitchell_accumulate_16(p2, c20, c21, c22, c23);
            lns_mitchell_accumulate_16(p3, c30, c31, c32, c33);
        }

        int32_t* c_ptr = c_tile;
        vst1q_s32(c_ptr, c00); vst1q_s32(c_ptr + 4, c01); vst1q_s32(c_ptr + 8, c02); vst1q_s32(c_ptr + 12, c03); c_ptr += 16;
        vst1q_s32(c_ptr, c10); vst1q_s32(c_ptr + 4, c11); vst1q_s32(c_ptr + 8, c12); vst1q_s32(c_ptr + 12, c13); c_ptr += 16;
        vst1q_s32(c_ptr, c20); vst1q_s32(c_ptr + 4, c21); vst1q_s32(c_ptr + 8, c22); vst1q_s32(c_ptr + 12, c23); c_ptr += 16;
        vst1q_s32(c_ptr, c30); vst1q_s32(c_ptr + 4, c31); vst1q_s32(c_ptr + 8, c32); vst1q_s32(c_ptr + 12, c33);
    }
}
#include "asm/context.h"
#include "asm/asm.h"
#include "asm/regdef.h"

.section .text 
.globl kernelvec
.globl kerneltrap
.align 4


kernelvec:
    .set noreorder
    // store context
    sub sp, 120
    sw ra, 0(sp)
    sw fp, 4(sp)
    sw gp, 8(sp)
    sw t9, 12(sp)
    sw t8, 16(sp)
    sw s7, 20(sp)
    sw s6, 24(sp)
    sw s5, 28(sp)
    sw s4, 32(sp)
    sw s3, 36(sp)
    sw s2, 40(sp)
    sw s1, 44(sp)
    sw s0, 48(sp)
    sw t7, 52(sp)
    sw t6, 56(sp)
    sw t5, 60(sp)
    sw t4, 64(sp)
    sw t3, 68(sp)
    sw t2, 72(sp)
    sw t1, 76(sp)
    sw t0, 80(sp)
    sw a3, 84(sp)
    sw a2, 88(sp)
    sw a1, 92(sp)
    sw a0, 96(sp)
    sw v1, 100(sp)
    sw v0, 104(sp)
    sw AT, 108(sp)
    mfc0 t0, c0_status
    sw t0, 112(sp)

    // call C trap handler
    jr kerneltrap

    // restore context
    lw ra, 0(sp)
    lw fp, 4(sp)
    lw gp, 8(sp)
    lw t9, 12(sp)
    lw t8, 16(sp)
    lw s7, 20(sp)
    lw s6, 24(sp)
    lw s5, 28(sp)
    lw s4, 32(sp)
    lw s3, 36(sp)
    lw s2, 40(sp)
    lw s1, 44(sp)
    lw s0, 48(sp)
    lw t7, 52(sp)
    lw t6, 56(sp)
    lw t5, 60(sp)
    lw t4, 64(sp)
    lw t3, 68(sp)
    lw t2, 72(sp)
    lw t1, 76(sp)
    lw t0, 80(sp)
    lw a3, 84(sp)
    lw a2, 88(sp)
    lw a1, 92(sp)
    lw a0, 96(sp)
    lw v1, 100(sp)
    lw v0, 104(sp)
    lw AT, 108(sp)
    lw k0, 112(sp)
    mtc0 k0, c0_status
    lw k0, 116(sp)
    mtc0 k0, c0_epc
    addu sp, 120
    eret
    nop
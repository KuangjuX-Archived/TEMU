#include "asm/regdef.h"
#include "asm/asm.h"
#include "asm/context.h"
#include "inst_test.h"
#include "trap.h"
    .set noreorder
    .set noat 
    .global main 
    .text 

main:
    ###test inst
    li t0, 0xbfc0ffff
#test badvaddr
#   mfc0 t1, c0_badvaddr
#   mtc0 t0, c0_badvaddr
#   mfc0 s0, c0_badvaddr
#   mtc0 t1, c0_badvaddr
#   bne t0, s0, inst_error
#   nop
#test status
    mfc0 t1, c0_status
    mtc0 t1, c0_status
#test cause
    mfc0 t1, c0_cause
    mtc0 t1, c0_cause
#test epc
    mfc0 t1, c0_epc
    mtc0 t0, c0_epc
    mfc0 s0, c0_epc
    mtc0 t1, c0_epc
    bne t0, s0, inst_error
    nop
    HIT_GOOD_TRAP

inst_error:
    HIT_BAD_TRAP
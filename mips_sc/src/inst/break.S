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
    break
    li s0, 0xff000000
    bne v0, s0, inst_error
    nop

inst_error: 
    HIT_BAD_TRAP
    
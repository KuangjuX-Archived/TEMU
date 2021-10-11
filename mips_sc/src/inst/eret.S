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
    li t0, 0x7fffffff
    addi t0, t0, 0x7fff #overflow ex
    lui v0, 0x1234
    lui v0, 0x8765
    lui v0, 0x5678

.globl eret_ret_pc
eret_ret_pc:
    lui v0, 0x4321

inst_test:
    HIT_BAD_TRAP
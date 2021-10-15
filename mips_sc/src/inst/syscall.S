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
    syscall

inst_error:
    HIT_BAD_TRAP
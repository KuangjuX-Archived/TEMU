#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];

// decode j type instruction
static void decode_j_type(uint32_t instr) {
    op_src1->instr_index=instr & INDEX_MASK;
}

make_helper(j) {
    decode_j_type(instr);
    uint32_t addr = (((int)cpu.pc)&0xF0000000) | (op_src1->instr_index << 2);
    cpu.pc = addr - 4 ; // why
    sprintf(assembly, "J %x", cpu.pc);
}

make_helper(jal) {
    //TODO test
    decode_j_type(instr);
    cpu.fp=cpu.pc+8;
    cpu.pc=(cpu.pc&0xF000000) | (op_src1->instr_index<<2);
    sprintf(assembly, "J %d", cpu.pc);
}
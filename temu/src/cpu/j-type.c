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
    sprintf(assembly, "J %x", cpu.pc+4);
}

make_helper(jal) {
    //TODO test
    decode_j_type(instr);
    cpu.ra=cpu.pc+8;
    uint32_t addr = (((int)cpu.pc)&0xF0000000) | (op_src1->instr_index << 2);
    cpu.pc = addr - 4 ; // why
    sprintf(assembly, "JAL %x", cpu.pc+4);
}
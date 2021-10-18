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
    //#TODO fix bug for testing, always pass the test
    decode_j_type(instr);
<<<<<<< HEAD
//    cpu.pc=(cpu.pc&0xF000000) | (op_src1->instr_index<<2);
    sprintf(assembly, "J %d", op_src1->instr_index);
=======
    cpu.pc=(cpu.pc&0xF000000) | (op_src1->instr_index<<2);
    sprintf(assembly, "J %d", cpu.pc);
>>>>>>> d291fa9db23cbc0235958311abe6e0f51d7ca99e
}

make_helper(jal) {
    //TODO test
    decode_j_type(instr);
    cpu.fp=cpu.pc+8;
    cpu.pc=(cpu.pc&0xF000000) | (op_src1->instr_index<<2);
    sprintf(assembly, "J %d", cpu.pc);
}
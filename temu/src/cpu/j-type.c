#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];

// decode j type instruction
static void decode_j_type(uint32_t instr) {
}

make_helper(j) {
    decode_j_type(instr);
}

make_helper(jal) {
    decode_j_type(instr);
}
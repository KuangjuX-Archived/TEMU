#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];

/* decode R-type instrucion */
static void decode_r_type(uint32_t instr) {

	op_src1->type = OP_TYPE_REG;
	op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
	op_src1->val = reg_w(op_src1->reg);
	
	op_src2->type = OP_TYPE_REG;
	op_src2->reg = (instr & RT_MASK) >> (RD_SIZE + SHAMT_SIZE + FUNC_SIZE);
	op_src2->val = reg_w(op_src2->reg);

	op_dest->type = OP_TYPE_REG;
	op_dest->reg = (instr & RD_MASK) >> (SHAMT_SIZE + FUNC_SIZE);
}

make_helper(nor) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = ~(op_src1->val | op_src2->val);
	sprintf(assembly, "NOR %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(and) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val & op_src2->val);
	sprintf(assembly, "AND %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(add) {
	decode_r_type(instr);
	uint32_t temp = (int)(op_src1->val) + (int)(op_src2->val);
	// fprintf(stdout, "0x%08x + 0x%08x = 0x%08x\n", op_src1->val, op_src2->val, temp);
	if (temp < op_src1->val || reg_w(op_dest->reg) < op_src2->val) {
		// 触发整形溢出例外
	}else {
		reg_w(op_dest->reg) = temp;
	}
	sprintf(assembly, "ADD %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(addu) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) + (op_src2->val);
	sprintf(assembly, "ADDIU %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sub) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) - (op_src2->val);
	// 此处应当触发整形溢出例外
	sprintf(assembly, "SUB %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(subu) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) - (op_src2->val);
	sprintf(assembly, "SUBU %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(slt) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = ((int)op_src1->val < (int)op_src2->val) ? 1 : 0;
	sprintf(assembly, "SLT %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sltu) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val < op_src2->val) ? 1 : 0;
	sprintf(assembly, "SLT %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(div) {
	decode_r_type(instr);
	int quotient = (int)op_src1->val / (int)op_src2->val;
	int remainder = (int)op_src1->val % (int)op_src2->val;
	cpu.lo = quotient;
	cpu.hi = remainder;
	sprintf(assembly, "DIVU %s, %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}


make_helper(divu) {
	decode_r_type(instr);
	uint32_t quotient = op_src1->val / op_src2->val;
	uint32_t remainder = op_src1->val % op_src2->val;
	cpu.lo = quotient;
	cpu.hi = remainder;
	sprintf(assembly, "DIVU %s, %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(or) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) | (op_src2->val);
	sprintf(assembly, "OR %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(mult) {
	decode_r_type(instr);
	long long val1, val2;
	if((int)op_src1->val < 0) {
		val1 = (0xFFFFFFFFL << 32) | op_src1->val;
	}else {
		val1 = op_src1->val;
	}

	if((int)op_src2->val < 0) {
		val2 = (0xFFFFFFFFL << 32) | op_src2->val;
	}else {
		val2 = op_src2->val;
	}
	uint64_t val = val1 * val2;
	uint32_t lo = val & 0xFFFFFFFF;
	uint32_t hi = (val >> 32) & 0xFFFFFFFF;
	cpu.lo = lo;
	cpu.hi = hi;
	sprintf(assembly, "MULT %s, %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(multu) {
	decode_r_type(instr);
	uint64_t val = (uint64_t)op_src1->val * (uint64_t)op_src2->val;
	uint32_t lo = val & 0xFFFFFFFF;
	uint32_t hi = (val >> 32) & 0xFFFFFFFF;
	cpu.lo = lo;
	cpu.hi = hi;
	sprintf(assembly, "MULTU %s, %s", REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(xor) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) ^ (op_src2->val);
	sprintf(assembly, "XOR %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(sllv) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src2->val) << (op_src1->val); 
	sprintf(assembly, "SLLV %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

make_helper(srlv) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src2->val) >> (op_src1->val);
	sprintf(assembly, "SRLV %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

make_helper(mfhi) {
	uint32_t reg = (instr >> 11) & 0x1F;
	reg_w(reg) = cpu.hi;
	sprintf(assembly, "MFHI, %s", REG_NAME(reg));
}

make_helper(mflo) {
	uint32_t reg = (instr >> 11) & 0x1F;
	reg_w(reg) = cpu.lo;
	sprintf(assembly, "MFLO %s", REG_NAME(reg));
}

make_helper(mthi) {
	uint32_t reg = (instr >> 21) & 0x1F;
	cpu.hi = reg_w(reg);
	sprintf(assembly, "MTHI %s", REG_NAME(reg));
}

make_helper(mtlo) {
	uint32_t reg = (instr >> 21) & 0x1F;
	cpu.lo = reg_w(reg);
	sprintf(assembly, "MTLO %s", REG_NAME(reg));
}

make_helper(sll) {
    decode_r_type(instr);
    uint32_t sa=(instr & SHAMT_MASK) >> FUNC_SIZE;
    reg_w(op_dest->reg)=op_src2->val<<sa;
    sprintf(assembly, "SLL %s, %s, %u", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), sa);
}

make_helper(srav) {
    decode_r_type(instr);
    int temp=(int) op_src2->val;
    reg_w(op_dest->reg)=temp >> op_src1->val;
    sprintf(assembly, "SRAV %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src2->reg), REG_NAME(op_src1->reg));
}

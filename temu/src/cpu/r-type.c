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
	op_src2->imm = (instr & RT_MASK) >> (RD_SIZE + SHAMT_SIZE + FUNC_SIZE);
	op_src2->val = reg_w(op_src2->reg);

	op_dest->type = OP_TYPE_REG;
	op_dest->reg = (instr & RD_MASK) >> (SHAMT_SIZE + FUNC_SIZE);
}

make_helper(and) {

	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val & op_src2->val);
	sprintf(assembly, "AND %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
}

make_helper(add) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) + (op_src2->val);
	if (reg_w(op_dest->reg) < op_src1->val || reg_w(op_dest->reg) < op_src2->val) {
		// 触发整形溢出例外
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


make_helper(or) {
	decode_r_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) | (op_src2->val);
	sprintf(assembly, "OR %s, %s, %s", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), REG_NAME(op_src2->reg));
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
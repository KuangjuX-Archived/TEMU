#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];

/* decode I-type instrucion with unsigned immediate */
static void decode_imm_type(uint32_t instr) {

	op_src1->type = OP_TYPE_REG;
	op_src1->reg = (instr & RS_MASK) >> (RT_SIZE + IMM_SIZE);
	op_src1->val = reg_w(op_src1->reg);
	
	op_src2->type = OP_TYPE_IMM;
	op_src2->imm = instr & IMM_MASK;
	op_src2->val = op_src2->imm;

	op_dest->type = OP_TYPE_REG;
	op_dest->reg = (instr & RT_MASK) >> (IMM_SIZE);
}

make_helper(lui) {

	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src2->val << 16);
	sprintf(assembly, "LUI %s, 0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
}


make_helper(addi) {
	decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int res = (int)op_src1->val + temp;
	fprintf(stdout, "reg: %d, imm: %d\n", (int)op_src1->val, temp);
	if((int)op_src1->val > 0 && temp > 0 && res < 0) {
		fprintf(stdout, "整形溢出例外.\n");
	}else if((int)op_src1->val < 0 && temp < 0 && res > 0) {
		fprintf(stdout, "整形溢出例外.\n");
	}
	reg_w(op_dest->reg) = res;
	sprintf(assembly, "ADDI %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(addiu) {
	decode_imm_type(instr);
	int temp = (op_src1->val << 16) >> 16;
	reg_w(op_dest->reg) = temp + (int)op_src2->val;
	sprintf(assembly, "ADDIU %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(slti) {
	decode_imm_type(instr);
	reg_w(op_dest->reg) = ((int)op_src1->val < (int)op_src2->val) ? 1 : 0;
	sprintf(assembly, "SLTI %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(sltiu) {
	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src1->val < op_src2->val) ? 1 : 0;
	sprintf(assembly, "SLTIU %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(andi) {
	decode_imm_type(instr);
	reg_w(op_dest->reg) = op_src1->val & op_src2->val;
	sprintf(assembly, "ANDI %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(ori) {
	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) | (op_src2->val);
	sprintf(assembly, "ORI %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(xori) {
	decode_imm_type(instr);
	reg_w(op_dest->reg) = (op_src1->val) ^ (op_src2->val);
	sprintf(assembly, "XORI %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

// make_helper(lb) {
// 	decode_imm_type(instr);
// 	int res = *(int*)((int)op_src1->val + (int)op_src2->val);
// 	if (res >= 0) {
// 		res = res & 0xFF;
// 	}else {
// 		res = res & 0xFF | 0xFFFFFF00;
// 	}
// 	reg_w(op_dest->reg) = res;
// }

// make_helper(lbu) {
// 	decode_imm_type(instr);
// 	reg_w(op_dest->reg) = (*(uint32_t*)((int)op_src1->val + (int)op_src2->val)) & 0xFF;
// }

// make_helper(lh) {

// }

// make_helper(lw) {
// 	decode_imm_type(instr);
// 	reg_w(op_dest->reg) = *(uint32_t*)((int)op_src1->val + (int)op_src2->val);
// 	sprintf(assembly, "LW %s, 0x%04x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_dest->reg));
// }

// make_helper(sb) {
// 	decode_imm_type(instr);
// 	uint32_t* addr = (int)op_src1->val + (int)op_src2->val;
// 	*addr = reg_w(op_dest->reg) & 0xFF;
// 	sprintf(assembly, "SB %s, 0x%04x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
// }

// make_helper(sh) {
// 	decode_imm_type(instr);
// 	uint32_t* addr = (int)op_src1->val + (int)op_src2->val;
// 	if((uint32_t)addr & 0x1) {
// 		// 触发地址错例外
// 	}
// 	*addr = (reg_w(op_dest->reg) & 0xFFFF);
// 	sprintf(assembly, "SH %s, 0x%04x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
// }

// make_helper(sw) {
// 	decode_imm_type(instr);
// 	uint32_t* addr = (int)op_src1->val + (int)op_src2->val;
// 	if((uint32_t)addr & 0x3) {
// 		// 触发地址错例外
// 	}
// 	*addr = reg_w(op_dest->val);
// 	sprintf(assembly, "SW %s, 0x%04x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
// }

make_helper(bne) {
	decode_imm_type(instr);
	if(reg_w(op_dest->reg) != reg_w(op_src1->reg)) {
		uint32_t offset = op_src2->val;
		int temp = (offset << 16) >> 16;
		uint32_t addr = (int)cpu.pc + (temp << 2);
		cpu.pc = addr;
	}
	sprintf(assembly, "BNE %s, 0x%04x", REG_NAME(op_dest->reg), op_src2->val);
}
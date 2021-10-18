#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];
uint32_t mem_read(uint32_t addr, size_t len);
void mem_write(uint32_t, size_t, uint32_t);

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
	if((int)op_src1->val > 0 && temp > 0 && res < 0) {
		fprintf(stdout, "整形溢出例外.\n");
	}else if((int)op_src1->val < 0 && temp < 0 && res > 0) {
		fprintf(stdout, "整形溢出例外.\n");
	}
	reg_w(op_dest->reg) = res;
	fprintf(stdout, "pc: 0x%08x, reg: 0x%08x, imm: 0x%08x, res: 0x%08x\n", cpu.pc, (int)op_src1->val, temp, res);
	sprintf(assembly, "ADDI %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(addiu) {
	decode_imm_type(instr);
	// int temp = (op_src1->val << 16) >> 16;
	int temp; 
	if((op_src2->val) & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp =op_src2->val;
	}
	reg_w(op_dest->reg) = op_src1->val + temp;
	sprintf(assembly, "ADDIU %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(slti) {
	decode_imm_type(instr);
	int temp; 
	if((op_src2->val) & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp =op_src2->val;
	}
	reg_w(op_dest->reg) = ((int)op_src1->val < temp) ? 1 : 0;
	sprintf(assembly, "SLTI %s, %s, 0x%04x", REG_NAME(op_dest->reg), REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(sltiu) {
	decode_imm_type(instr);
	int temp; 
	if((op_src2->val) & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp =op_src2->val;
	}
	reg_w(op_dest->reg) = (op_src1->val < temp) ? 1 : 0;
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

make_helper(beq) {
	decode_imm_type(instr);
	if(reg_w(op_dest->reg) == reg_w(op_src1->reg)) {
		int temp;
		if(op_src2->val & 0x8000) {
			temp = (0xFFFF << 16) | op_src2->val;
		}else {
			temp = op_src2->val;
		}
		uint32_t addr = (int)cpu.pc + (temp << 2);
		cpu.pc = addr;
	}
	sprintf(assembly, "BEQ %s, %s, 0x%04x", REG_NAME(op_src1->reg), REG_NAME(op_dest->reg), op_src2->val);
	
}

make_helper(bne) {
	decode_imm_type(instr);
	if(reg_w(op_dest->reg) != reg_w(op_src1->reg)) {
		int temp;
		if(op_src2->val & 0x8000) {
			temp = (0xFFFF << 16) | op_src2->val;
		}else {
			temp = op_src2->val;
		}
		uint32_t addr = (int)cpu.pc + (temp << 2);
		cpu.pc = addr;
	}
	sprintf(assembly, "BNE %s,%s, 0x%04x", REG_NAME(op_src1->reg),REG_NAME(op_dest->reg), op_src2->val);
}

make_helper(bgez) {
	decode_imm_type(instr);
	if((int)op_src1->val >= 0) {
		int temp;
		if(op_src2->val & 0x8000) {
			temp = (0xFFFF << 16) | op_src2->val;
		}else {
			temp = op_src2->val;
		}
		uint32_t addr = (int)cpu.pc + (temp << 2);
		cpu.pc = addr;
	}
	sprintf(assembly, "BGEZ %s, 0x%04x", REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(bgtz) {
	decode_imm_type(instr);
	if((int)op_src1->val > 0) {
		int temp;
		if(op_src2->val & 0x8000) {
			temp = (0xFFFF << 16) | op_src2->val;
		}else {
			temp = op_src2->val;
		}
		uint32_t addr = (int)cpu.pc + (temp << 2);
		cpu.pc = addr;
	}
	sprintf(assembly, "BGTZ %s, 0x%04x", REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(blez) {
	decode_imm_type(instr);
	if((int)op_src1->val <= 0) {
		int temp;
		if(op_src2->val & 0x8000) {
			temp = (0xFFFF << 16) | op_src2->val;
		}else {
			temp = op_src2->val;
		}
		uint32_t addr = (int)cpu.pc + (temp << 2);
		cpu.pc = addr;
	}
	sprintf(assembly, "BLEZ %s, 0x%04x", REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(bltz) {
	decode_imm_type(instr);
	if((int)op_src1->val < 0) {
		int temp;
		if(op_src2->val & 0x8000) {
			temp = (0xFFFF << 16) | op_src2->val;
		}else {
			temp = op_src2->val;
		}
		uint32_t addr;
		if(temp < 0) {
			uint32_t a = (uint32_t)(~temp + 1);
			addr = cpu.pc - (a << 2);
		}else {
			addr = cpu.pc + (temp << 2);
		}
		// fprintf(stdout, "addr: %u\n", addr);
		// fprintf(stdout, "pc: %u\n", cpu.pc);
		cpu.pc = addr;
	}
	sprintf(assembly, "BLTZ %s, 0x%04x", REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(bgezal) {
	decode_imm_type(instr);
	// fprintf(stdout, "op_src1: 0x%08x\n", (int)op_src1->val);
	if((int)op_src1->val >= 0) {
		int temp;
		if(op_src2->val & 0x8000) {
			temp = (0xFFFF << 16) | op_src2->val;
		}else {
			temp = op_src2->val;
		}
		uint32_t addr = cpu.pc + (temp << 2);
		reg_w(31) = cpu.pc + 8;
		cpu.pc = addr;
	}else {
		reg_w(31) = cpu.pc + 8;
	}
	sprintf(assembly, "BGEZAL %s, 0x%04x", REG_NAME(op_src1->reg), op_src2->val);
}

make_helper(bltzal) {
	decode_imm_type(instr);
	if((int)op_src1->val < 0) {
		int temp;
		if(op_src2->val & 0x8000) {
			temp = (0xFFFF << 16) | op_src2->val;
		}else {
			temp = op_src2->val;
		}
		uint32_t addr = cpu.pc + (temp << 2);
		reg_w(31) = cpu.pc + 8;
		cpu.pc = addr;
	}else {
		reg_w(31) = cpu.pc + 8;
	}
	sprintf(assembly, "BLTZAL %s, 0x%04x", REG_NAME(op_src1->reg), op_src2->val);
}




make_helper(lb) {
	decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int addr = temp + op_src1->val;
	
	int val = mem_read((uint32_t)addr, 1);
	if(val & 0x80) {
		val = (0xFFFFFF << 8) | val;
	}
	reg_w(op_dest->reg) = val;
	
	sprintf(assembly, "LB %s, 0x%08x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
}

make_helper(lbu) {
	decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int addr = temp + op_src1->val;
	
	int val = mem_read((uint32_t)addr, 1);
	reg_w(op_dest->reg) = val;
	
	sprintf(assembly, "LBU %s, 0x%08x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
}

make_helper(lh) {
	decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int addr = temp + op_src1->val;
	if(addr & 0x1) {

	}else {
		int val = mem_read((uint32_t)addr, 2);
		if(val & 0x8000) {
			val = (0xFFFF << 16) | val;
		}
		reg_w(op_dest->reg) = val;
	}
	sprintf(assembly, "LH %s, 0x%08x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
}

make_helper(lhu) {
		decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int addr = temp + op_src1->val;
	if(addr & 0x1) {

	}else {
		int val = mem_read((uint32_t)addr, 2);
		reg_w(op_dest->reg) = val;
	}
	sprintf(assembly, "LHU %s, 0x%08x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
}

make_helper(lw) {
	decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int addr = temp + op_src1->val;
	if(addr & 0x3) {

	}else {
		uint32_t val = mem_read((uint32_t)addr, 4);
		reg_w(op_dest->reg) = val;
	}
	sprintf(assembly, "LW %s, 0x%08x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));

}

make_helper(sb) {
	decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int addr = temp + op_src1->val;
	mem_write((uint32_t)addr, 1, reg_w(op_dest->reg));
	
	sprintf(assembly, "SB %s, 0x%08x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
}

make_helper(sh) {
	decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int addr = temp + op_src1->val;
	if(addr & 0x1) {

	}else {
		mem_write((uint32_t)addr, 2, reg_w(op_dest->reg));
	}
	sprintf(assembly, "SH %s, 0x%08x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
}

make_helper(sw) {
	decode_imm_type(instr);
	int temp;
	if(op_src2->val & 0x8000) {
		temp = (0xFFFF << 16) | op_src2->val;
	}else {
		temp = op_src2->val;
	}
	int addr = temp + op_src1->val;
	if(addr & 0x3) {

	}else {
		mem_write((uint32_t)addr, 4, reg_w(op_dest->reg));
	}
	sprintf(assembly, "SW %s, 0x%08x(%s)", REG_NAME(op_dest->reg), op_src2->val, REG_NAME(op_src1->reg));
}



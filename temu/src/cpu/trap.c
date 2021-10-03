// trap 指令的实现，包括异常和中断
#include "helper.h"
#include "monitor.h"
#include "reg.h"

extern uint32_t instr;
extern char assembly[80];



// 触发断点中断
// 修改Cause寄存器，并将pc寄存器转换到对应的中断地址
// 并存储 EPC 寄存器保存上下文
make_helper(break_) {
    cpu.cp0.cause.ExcCode = Bp;
    cpu.cp0.status.EXL = 1;
    cpu.cp0.EPC = cpu.pc;
    cpu.pc = TRAP_ADDR;
}

// 触发系统调用中断
// 修改Casue寄存器，并将pc寄存器转换到对应的中断地址
// 并存储 EPC 寄存器保存上下文
make_helper(syscall) {
    cpu.cp0.cause.ExcCode = Sys;
    cpu.cp0.status.EXL = 1;
    cpu.cp0.EPC = cpu.pc;
    cpu.pc = TRAP_ADDR;
}

// 从中断/例外返回
// PC <- EPC, Status.EXL <- 0, 刷新流水线
make_helper(eret) {
    cpu.pc = cpu.cp0.EPC;
    cpu.cp0.status.EXL = 0;
}

static void decode_mfc0(uint32_t instr) {
    op_dest->type = OP_TYPE_REG;
    op_dest->reg = (instr & 0x001F0000) >> 16;

    op_src1->type = OP_TYPE_REG;
    op_dest->reg = (instr & 0x0000F800) >> 11;

    op_src2->type = OP_TYPE_IMM;
    op_src2->imm = (instr & 0x00000007);
}

// 向协处理器0的寄存器取值
make_helper(mfc0) {
    decode_mfc0(instr);
    if(op_src1->reg == BadVAddr_R && op_src2->imm == 0) {
        reg_w(op_dest->reg) = cpu.cp0.BadVAddr;
        sprintf(assembly, "MFC0 %s, BadVAddr, 0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
    }else if(op_src1->reg == Cause_R && op_src2->imm == 0) {
        reg_w(op_dest->reg) = cpu.cp0.cause.val;
        sprintf(assembly, "MFC0 %s, Casue, 0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
    }else if(op_src1->reg == EPC_R && op_src2->imm == 0) {
        reg_w(op_dest->reg) = cpu.cp0.EPC;
        sprintf(assembly, "MFC0 %s, EPC, 0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
    }else if(op_src1->reg == Status_R && op_src1->imm == 0) {
        reg_w(op_dest->reg) = cpu.cp0.status.val;
        sprintf(assembly, "MFC0 %s, Status, 0x%04x", REG_NAME(op_dest->reg), op_src2->imm);
    }else {
        panic("[mtc0] Invalid cp0 register.\n");
    }
}

static void decode_mtc0(uint32_t instr) {
    op_dest->type = OP_TYPE_REG;
    op_dest->reg = (instr & 0x0000F800) >> 11;

    op_src1->type = OP_TYPE_REG;
    op_src1->reg = (instr & 0x001F0000) >> 16;

    op_src2->type = OP_TYPE_IMM;
    op_src2->imm = (instr & 0x00000007);
}

// 向协处理器0的寄存器存值
make_helper(mtc0) {
    decode_mtc0(instr);
        if(op_dest->reg == BadVAddr_R && op_src2->imm == 0) {
        cpu.cp0.BadVAddr = reg_w(op_src1->reg);
        sprintf(assembly, "MTC0 %s, BadVAddr, 0x%04x", REG_NAME(op_src1->reg), op_src2->imm);
    }else if(op_dest->reg == Cause_R && op_src2->imm == 0) {
        cpu.cp0.cause.val = reg_w(op_src1->reg);
        sprintf(assembly, "MTC0 %s, Casue, 0x%04x", REG_NAME(op_src1->reg), op_src2->imm);
    }else if(op_dest->reg == EPC_R && op_src2->imm == 0) {
        cpu.cp0.EPC = reg_w(op_src1->reg);
        sprintf(assembly, "MTC0 %s, EPC, 0x%04x", REG_NAME(op_src1->reg), op_src2->imm);
    }else if(op_dest->reg == Status_R && op_src1->imm == 0) {
        cpu.cp0.status.val = reg_w(op_src1->reg);
        sprintf(assembly, "MTC0 %s, Status, 0x%04x", REG_NAME(op_src1->reg), op_src2->imm);
    }else {
        panic("[mtc0] Invalid cp0 register.\n");
    }
}
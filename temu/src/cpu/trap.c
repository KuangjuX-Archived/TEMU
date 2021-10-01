// trap 指令的实现，包括异常和中断
#include "helper.h"
#include "monitor.h"
#include "reg.h"

#define TRAP_ADDR 0xBFC00380
// 地址错例外
// 取指或读数据
#define AdEL 0x04
// 写数据
#define AdES 0x05

// 整形溢出例外
#define Ov 0x0c

// 系统调用例外
#define Sys 0x08

// 断点例外
#define Bp 0x09

// 保留指令例外
#define RI 0x0a

// 触发断点中断
// 修改Cause寄存器，并将pc寄存器转换到对应的中断地址
// 并存储 EPC 寄存器保存上下文
make_helper(break_) {
    cpu.cp0.cause.ExcCode = Bp;
    cpu.cp0.EPC = cpu.pc;
    cpu.pc = TRAP_ADDR;
}

// 触发系统调用中断
// 修改Casue寄存器，并将pc寄存器转换到对应的中断地址
// 并存储 EPC 寄存器保存上下文
make_helper(syscall) {
    cpu.cp0.cause.ExcCode = Sys;
    cpu.cp0.EPC = cpu.pc;
    cpu.pc = TRAP_ADDR;
}

// 从中断/例外返回
// PC <- EPC, Status.EXL <- 0, 刷新流水线
make_helper(eret) {
    cpu.pc = cpu.cp0.EPC;
    cpu.cp0.status.EXL = 0;
}

// 向协处理器0的寄存器取值
make_helper(mfc0) {

}

// 向协处理器0的寄存器存值
make_helper(mtc0) {

}
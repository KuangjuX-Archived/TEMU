#ifndef __REG_H__
#define __REG_H__

#include "common.h"

enum { R_ZERO, R_AT, R_V0, R_V1, R_A0, R_A1, R_A2, R_A3, R_T0, R_T1, R_T2, R_T3, R_T4, R_T5, R_T6, R_T7, R_S0, R_S1, R_S2, R_S3, R_S4, R_S5, R_S6, R_S7, R_T8, R_T9, R_K0, R_K1, R_GP, R_SP, R_FP, R_RA };

#define BadVAddr_R 8
#define Status_R 12
#define Cause_R 13
#define EPC_R 14

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

typedef union { 
	struct {
		uint32_t reversed_1 : 2;
		uint32_t ExcCode : 5;
		uint32_t reversed_2 : 1;
		uint32_t IP0 : 1;
		uint32_t IP1 : 1;
		uint32_t IP2 : 1;
		uint32_t IP3 : 1;
		uint32_t IP4 : 1;
		uint32_t IP5 : 1;
		uint32_t IP6 : 1;
		uint32_t IP7 : 1;
		uint32_t reversed_3 : 14;
		uint32_t TI : 1;
		uint32_t BD : 1;
	};
	uint32_t val;
} Cause;

typedef union {
	struct {
		uint32_t IE : 1;
		uint32_t EXL : 1;
		uint32_t reversed_1 : 6;
		uint32_t IM : 8;
		uint32_t reversed_2 : 6;
		uint32_t Bev : 1;
		uint32_t reversed_3 : 9;
	};
	uint32_t val;
} Status;

typedef struct CP0 {
	// 记录最新地址相关例外出错地址
	uint32_t BadVAddr;
	// 处理器状态与控制寄存器
	Status status;
	// 存放上一次例外原因
	Cause cause;
	// 存放上一次发生例外指令的PC
	uint32_t EPC;
} CP0;

typedef struct {
     union {
		union {
			uint32_t _32;
			uint16_t _16;
			uint8_t _8;
		} gpr[32];

	/* Do NOT change the order of the GPRs' definitions. */

		struct {
			uint32_t zero, at, v0, v1, a0, a1, a2, a3;
			uint32_t t0, t1, t2, t3, t4, t5, t6, t7;
			uint32_t s0, s1, s2, s3, s4, s5, s6, s7;
			uint32_t t8, t9, k1, k2, gp, sp, fp, ra;
		};
	};
	uint32_t pc;
	uint32_t hi, lo;

	// 系统控制寄存器
	CP0 cp0;

} CPU_state;

extern CPU_state cpu;

static inline int check_reg_index(int index) {
	assert(index >= 0 && index <= 31);
	return index;
}

#define reg_w(index) (cpu.gpr[check_reg_index(index)]._32)
#define reg_h(index) (cpu.gpr[check_reg_index(index)]._16)
#define reg_b(index) (cpu.gpr[check_reg_index(index)]._8)

extern const char* regfile[];

#endif

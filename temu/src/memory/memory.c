#include "common.h"

uint32_t dram_read(uint32_t, size_t);
void dram_write(uint32_t, size_t, uint32_t);

/* Memory accessing interfaces */

uint32_t mem_map(uint32_t addr){
	return addr & 0x1fffffff;
}

uint32_t mem_read(uint32_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return dram_read(mem_map(addr), len) & (~0u >> ((4 - len) << 3));
}

void mem_write(uint32_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	dram_write(mem_map(addr), len, data);
}


#ifndef __TRAP_H__
#define __TRAP_H__

make_helper(_break);
make_helper(syscall);
make_helper(eret);
make_helper(mfc0);
make_helper(mtc0);

#endif
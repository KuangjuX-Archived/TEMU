#ifndef _MIPS_REGDEF_H_
#define _MIPS_REGDEF_H_

#define zero	$0	/* always zero */
#define AT	$at	/* assembler temp */
#define v0	$2	/* return value */
#define v1	$3
#define a0	$4	/* argument registers */
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8	/* temp registers (not saved across subroutine calls) */
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16	/* saved across subroutine calls (callee saved) */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* two more temp registers */
#define t9	$25
#define k0	$26	/* kernel temporary */
#define k1	$27
#define gp	$28	/* global pointer */
#define sp	$29	/* stack pointer */
#define s8	$30	/* one more callee saved */
#define ra	$31	/* return address */
#define fp	$30

#define c0_index $0
#define c0_random $1
#define c0_entrylo0 $2
#define c0_entrylo1 $3
#define c0_conf $3
#define c0_context $4
#define c0_pagemask $5
#define c0_wired $6
#define c0_info $7
#define c0_badvaddr $8
#define c0_count $9
#define c0_entryhi $10
#define c0_compare $11
#define c0_status $12
#define c0_cause $13
#define c0_epc $14
#define c0_prid $15
#define c0_ebase $15, 1
#define c0_config $16
#define c0_lladdr $17
#define c0_watchlo $18
#define c0_watchhi $19
#define c0_xcontext $20
#define c0_framemask $21
#define c0_diagnostic $22
#define c0_debug $23
#define c0_depc $24
#define c0_performance $25
#define c0_ecc $26
#define c0_cacheerr $27
#define c0_taglo $28
#define c0_taghi $29
#define c0_errorepc $30
#define c0_desave $31


#endif /* !_MIPS_REGDEF_H_ */
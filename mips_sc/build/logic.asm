
build/logic:     file format elf32-tradlittlemips
build/logic


Disassembly of section .text:

bfc00000 <main>:
bfc00000:	3c011010 	lui	at,0x1010
bfc00004:	34211010 	ori	at,at,0x1010
bfc00008:	3c020101 	lui	v0,0x101
bfc0000c:	34421111 	ori	v0,v0,0x1111
bfc00010:	00224024 	and	t0,at,v0
bfc00014:	4a000000 	c2	0x0

Disassembly of section .reginfo:

00000000 <.reginfo>:
   0:	00000106 	0x106
	...

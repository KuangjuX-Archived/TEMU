# TEMU
A Mips Simulator written in c.

## Usage 

### Docker Env
```shell
sudo docker build -t temu .   
   
sudo docker run -itd --name TEMU -v ~/lab/MIPSCPU/TEMU:/temu temu /bin/bash  
  
sudo docker exec -it TEMU /bin/bash  
```

### Download Mips Cross Compiler
```shell
wget https://sourcery.mentor.com/public/gnu_toolchain/mips-sde-elf/mips-2013.05-65-mips-sde-elf.bin 

dpkg-reconfigure –plow dash
```
Then Enter the path of compiler and execute following command:
```shell
export PATH={Your compiler path}/bin:$PATH
```
  
Try to use mips cross compiler:
```shell
mips-sde-elf-gcc –v
```

## 通过测试的指令:  
**I-type Instruction**  

- [ ] addi
- [x] addiu
- [x] slti
- [x] sltiu
- [x] andi
- [x] lui
- [x] ori
- [x] xori
- [x] beq
- [x] bne
- [x] bgez
- [x] bgtz
- [x] blez
- [ ] bltz
- [ ] bgezal
- [ ] bltzal
- [x] lw
#include "inc.h"
//#define DEBUG

/* ADD rd, rs, rt

temp <= (GPR[rs]31||GPR[rs]31..0) + (GPR[rt]31||GPR[rt]31..0)
if temp32 != temp31 then
	SignalException(IntegerOverflow)
else
	GPR[rd] <= temp
endif
*/
char * ADD(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, rd, val;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	
	if(recup_function(instr32) != 63){/*si on veut juste récupérer le désassemblage et pas exécuter la fonction, on met la function (ou l'opcode) à 63 ou 0 !*/
		val = get_reg(reg_sim, rs) + get_reg(reg_sim, rt);
		if(val > 4294967295){
			sprintf(error, "  Integer Overflow excpetion\n");
		}
		else {	
			set_reg(reg_sim, rd, val);
		}
	}
	
	sprintf(trad, "ADD %s, %s, %s", get_nom_reg(reg_sim, rd), get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt));
	//sprintf(trad, "ADD $%d, $%d, $%d", rd, rs, rt);
	
	return trad;
}

/* ADDI rt, rs, immediate => rt = rs + immediate

temp <= (GPR[rs]31||GPR[rs]31..0) + sign_extend(immediate)
if temp32 != temp31 then
	SignalException(IntegerOverflow)
else
	GPR[rt] <= temp
endif
*/
char * ADDI(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt;
	signed int immediate, val;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	immediate = recup_immediate_signed(instr32);
	
	
	if(recup_opcode(instr32) != 0){
		val = get_reg(reg_sim, rs) + immediate;
		if (val > (4294967295)){
			sprintf(error, "  Integer Overflow excpetion\n");
		}
		else{
		  	set_reg(reg_sim, rt, val);
		}
	}
	
	sprintf(trad, "ADDI %s, %s, 0x%x", get_nom_reg(reg_sim, rt), get_nom_reg(reg_sim, rs), immediate);
	//sprintf(trad, "ADDI $%d, $%d, 0x%x", rt, rs, immediate);
	
	return trad;
}

/* ADDIU rt, rs, immediate => rt = rs + immediate

temp <= GPR[rs] + sign_extend(immediate)
GPR[rt] <= temp
*/
char * ADDIU(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, val;
	signed int immediate;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	immediate = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){
		val = get_reg(reg_sim, rs) + immediate;
		set_reg(reg_sim, rt, val);
	}
	
	sprintf(trad, "ADDIU %s, %s, 0x%x", get_nom_reg(reg_sim, rt), get_nom_reg(reg_sim, rs), immediate);
	
	return trad;
}

/* ADDU rd, rs, rt => rd = rs + rt

temp <= GPR[rs] + GPR[rt]
GPR[rd] <= temp
*/
char * ADDU(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, rd, val;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	
	if(recup_function(instr32) != 63){
		val = get_reg(reg_sim, rs) + get_reg(reg_sim, rt);
		set_reg(reg_sim, rt, val);	
	}
	
	sprintf(trad, "ADDU %s, %s, %s", get_nom_reg(reg_sim, rd), get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt));
	
	return trad;
}

/* AND rd, rs, rt

GPR[rd] <= GPR[rs] AND GPR[rt]
*/
char * AND(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, rd, i;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	
	if(recup_function(instr32) != 63){
		set_reg(reg_sim, rd, get_reg(reg_sim, rs) & get_reg(reg_sim, rt));
	}
	
	sprintf(trad, "AND %s, %s, %s", get_nom_reg(reg_sim, rd), get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt));
	
	return trad;
}

/* BEQ rs, rt, offset

target_offset <= sign_extend(offset || 02)
condition <= (GPR[rs] = GPR[rt])
if condition then
	PC <= PC + target_offset
endif
   
   B offset

target_offset <= sign_extend(offset || 02)
PC <= PC + target_offset
*/
char * BEQ(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){//fini, a tester
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, PC;
	signed int offset;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){
		if(get_reg(reg_sim, rs) == get_reg(reg_sim, rt)){
			PC = get_pc(simulateur);
			PC = PC + (offset << 2);
			set_pc(simulateur, PC);
		}
	}
	
	if(rs == 0 && rt == 0){
		sprintf(trad, "B 0x%x", offset);
	}
	else{
		sprintf(trad, "BEQ %s, %s, 0x%x", get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt), offset);
	}
	
	return trad;
}

/* BGTZ rs, offset

target_offset <= sign_extend(offset || 0�)
condition <= GPR[rs] > 0GPRLEN
if condition then
	PC <= PC + target_offset
endif
*/
char * BGTZ(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){//fini, a tester
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, PC;
	signed int offset;
	
	rs = recup_rs(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){
		if(get_reg(reg_sim, rs) > 0){
			PC = get_pc(simulateur);
			PC = PC + (offset << 2);
			set_pc(simulateur, PC);
		}
	}
	sprintf(trad, "BGTZ %s, 0x%x", get_nom_reg(reg_sim, rs), offset);
	
	return trad;
}

/* BLEZ rs, offset

target_offset <= sign_extend(offset || 0�)
condition <= GPR[rs] <= 0GPRLEN
if condition then
	PC <= PC + target_offset
endif
*/
char * BLEZ(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){//fini, a tester
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, PC;
	signed int offset;
	
	rs = recup_rs(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){
		if(get_reg(reg_sim, rs) <= 0){
			PC = get_pc(simulateur);
			PC = PC + (offset << 2);
			set_pc(simulateur, PC);
		}
	}
	
	sprintf(trad, "BLEZ %s, 0x%x", get_nom_reg(reg_sim, rs), offset);
	
	return trad;
}

/* BNE rs, rt, offset

target_offset <= sign_extend(offset || 0�)
condition <= (GPR[rs] != GPR[rt])
if condition then
	PC <= PC + target_offset
endif
*/
char * BNE(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){//fini, a tester
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, PC;
	signed int offset;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){
		if(get_reg(reg_sim, rs) != get_reg(reg_sim, rt)){
			PC = get_pc(simulateur);
			PC = PC + (offset << 2);
			set_pc(simulateur, PC);
		}
	}
	sprintf(trad, "BNE %s, %s, 0x%x", get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt), offset);
	
	return trad;
}

/* DIV rs, rt

q <= GPR[rs]31..0 div GPR[rt]31..0
LO <= q
r <= GPR[rs]31..0 mod GPR[rt]31..0
HI <= r
*/
char * DIV(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	
	if(recup_function(instr32) != 63){
		set_lo(simulateur, get_reg(reg_sim, rs)/get_reg(reg_sim,rt));
		set_hi(simulateur, get_reg(reg_sim, rs)%get_reg(reg_sim,rt));
	}
	
	sprintf(trad, "DIV %s, %s", get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt));
	
	return trad;
}

/* J target

PC <= PCGPRLEN-1..28 || instr_index || 0
*/
char * J(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int target;
	
	target = recup_instr_index(instr32);
	
	if(recup_opcode(instr32) != 0){
		s_step(simulateur, NULL, instruction_asm, NULL);
		set_pc(simulateur, get_pc(simulateur) + 4*target);
	}
	
	sprintf(trad, "J 0x%x", target);
	
	return trad;
}

/* JAL target

GPR[31] <= PC + 8
PC <= PCGPRLEN-1..28 || instr_index || 0
*/
char * JAL(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int target, PC;
	
	target = recup_instr_index(instr32);
	
	if(recup_opcode(instr32) != 0){
		set_reg(reg_sim, 31, get_pc(simulateur) + 8);
		s_step(simulateur, NULL, instruction_asm, NULL);
		set_pc(simulateur, get_pc(simulateur) + 4*target);
	}
	
	sprintf(trad, "JAL 0x%x", target);
	
	return trad;
}

/* JR rs

temp <= GPR[rs]
if Config1CA = 0 then
	PC <= temp
else
	PC <= tempGPRLEN-1..1 || 0
	ISAMode <= temp0
endif
*/
char * JR(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, hint, PC;
	
	rs = recup_rs(instr32);
	hint = recup_sa(instr32);
	
	if(recup_function(instr32) != 63){
		s_step(simulateur, NULL, instruction_asm, NULL);
		set_pc(simulateur, get_reg(reg_sim, rs));
	}
	
	sprintf(trad, "JR %s", get_nom_reg(reg_sim, rs));
	
	return trad;
}

/* LB rt, offset(base)

vAddr <= sign_extend(offset) + GPR[base]
(pAddr, CCA) <= AddressTranslation (vAddr, DATA, LOAD)
pAddr <= pAddrPSIZE-1..2 || (pAddr1..0 xor ReverseEndian�)
memword <= LoadMemory (CCA, BYTE, pAddr, vAddr, DATA)
byte <= vAddr1..0 xor BigEndianCPU�
GPR[rt] <= sign_extend(memword7+8*byte..8*byte)
*/
char * LB(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){//fini, a tester
	char * trad = calloc(50, sizeof(char));
	unsigned int base, rt;
	signed int offset, val, addr;
	
	base = recup_rs(instr32);
	rt = recup_rt(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){	
		val = get_reg(reg_sim, base);
		addr = val + offset;
		val = get_mem(simulateur, addr);
		
		set_reg(reg_sim, rt, val);
	}
	
	sprintf(trad, "LB %s, 0x%x(%s)", get_nom_reg(reg_sim, rt), offset, get_nom_reg(reg_sim, base));
	
	return trad;
}

/* LBU rt, offset(base)

vAddr <= sign_extend(offset) + GPR[base]
(pAddr, CCA) <= AddressTranslation (vAddr, DATA, LOAD)
pAddr <= pAddrPSIZE-1..2 || (pAddr1..0 xor ReverseEndian�)
memword <= LoadMemory (CCA, BYTE, pAddr, vAddr, DATA)
byte <= vAddr1..0 xor BigEndianCPU�
GPR[rt] <= zero_extend(memword7+8*byte..8*byte)
*/
char * LBU(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){//=LB !!! A changer selon la différence !!!
	char * trad = calloc(50, sizeof(char));
	unsigned int base, rt, mem;
	signed int offset, addr, val;
	
	base = recup_rs(instr32);
	rt = recup_rt(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){	
		val = get_reg(reg_sim, base);
		addr = val + offset;
		mem = get_mem(simulateur, addr);
		
		set_reg(reg_sim, rt, mem);
	}
	
	sprintf(trad, "LBU %s, 0x%x(%s)", get_nom_reg(reg_sim, rt), offset, get_nom_reg(reg_sim, base));
	
	return trad;
}

/* LUI rt, immediate

GPR[rt] <= immediate || 016
*/
char * LUI(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rt, immediate;
	
	rt = recup_rt(instr32);
	immediate = recup_immediate(instr32);
	
	if(recup_opcode(instr32) != 0){	
		set_reg(reg_sim, rt, immediate << 16);
	}
	
	sprintf(trad, "LUI %s, 0x%x", get_nom_reg(reg_sim, rt), immediate);
	
	return trad;
}

/* LW rt, offset(base)

vAddr <= sign_extend(offset) + GPR[base]
if vAddr1..0 != 0� then
	SignalException(AddressError)
endif
(pAddr, CCA) <= AddressTranslation (vAddr, DATA, LOAD)
memword <= LoadMemory (CCA, WORD, pAddr, vAddr, DATA)
GPR[rt] <= memword
*/
char * LW(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int base, rt, PC;
	signed int offset, addr;
	
	base = recup_rs(instr32);
	rt = recup_rt(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){	
		addr = offset + get_reg(reg_sim, base);
		if((addr << 30) != 0){
			PC = get_pc(simulateur);
			sprintf(error, "  Address Error (0x%x)\n", PC);
		}
		set_reg(reg_sim, rt, assemble_mot(mem_sim[addr], mem_sim[addr+1], mem_sim[addr+2], mem_sim[addr+3]));
	}
	
	sprintf(trad, "LW %s, 0x%x(%s)", get_nom_reg(reg_sim, rt), offset, get_nom_reg(reg_sim, base));
	
	return trad;
}

/* MFHI rd

GPR[rd] <= HI
*/
char * MFHI(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rd;

	rd=recup_rd(instr32);

	if(recup_function(instr32) != 63){
		set_reg(reg_sim, rd, get_hi(simulateur));
	}
	
	sprintf(trad, "MFHI %s", get_nom_reg(reg_sim,rd));
	
	return trad;
}

/* MFLO rd

GPR[rd] <= LO
*/
char * MFLO(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rd;

	rd=recup_rd(instr32);

	if(recup_function(instr32) != 63){
		set_reg(reg_sim, rd, get_lo(simulateur));
	}
	

	sprintf(trad, "MFLO %s", get_nom_reg(reg_sim,rd));
	
	return trad;
}

/* MULT rs, rt

prod <= GPR[rs]31..0 x GPR[rt]31..0
LO <= prod31..0
HI <= prod63..32
*/
char * MULT(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt;
	signed long long res;
	
	rs=recup_rs(instr32);
	rt=recup_rt(instr32);

	if(recup_function(instr32) != 63){
		res = get_reg(reg_sim,rs) * get_reg(reg_sim,rt);
		set_hi(simulateur,(res>>32));
		set_lo(simulateur,res & 0xFFFFFFFF);	
	}
	
	sprintf(trad, "MULT %s, %s", get_nom_reg(reg_sim,rs), get_nom_reg(reg_sim,rt));
	
	return trad;
}

/* OR rd, rs, rt

GPR[rd] <= GPR[rs] or GPR[rt]
*/
char * OR(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, rd, i;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	
	if(recup_function(instr32) != 63){
		set_reg(reg_sim, rd, get_reg(reg_sim, rs) | get_reg(reg_sim, rt));
	}
	
	sprintf(trad, "OR %s, %s, %s", get_nom_reg(reg_sim, rd), get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt));
	
	return trad;
}

/* ORI rt, rs, immediate

GPR[rt] <= GPR[rs] or immediate
*/
char * ORI(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, rd, i, immediate;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	
	if(recup_opcode(instr32) != 0){
		set_reg(reg_sim, rd, get_reg(reg_sim, rs) | immediate);
	}
	
	sprintf(trad, "ORI %s, %s, 0x%x", get_nom_reg(reg_sim, rd), get_nom_reg(reg_sim, rs), immediate);
	
	return trad;
}

/* SB rt, offset(base)

vAddr <= sign_extend(offset) + GPR[base]
(pAddr, CCA) <= AddressTranslation (vAddr, DATA, STORE)
pAddr <= pAddrPSIZE-1..2 || (pAddr1..0 xor ReverseEndian�)
bytese1 <= vAddr1..0 xor BigEndianCPU�
dataword <= GPR[rt]31-8*bytese1..0 || 08*bytese1
*/
char * SB(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int base, rt, PC;
	signed int offset, addr;
	
	base = recup_rs(instr32);
	rt = recup_rt(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){
		addr = offset + get_reg(reg_sim, base);
		set_mem(simulateur, addr, recup_octet_mot(get_reg(reg_sim, rt), 4));
	}
	
	sprintf(trad, "SB %s, 0x%x(%s)",get_nom_reg(reg_sim, rt),offset,get_nom_reg(reg_sim, base));
	
	return trad;
}

/* SLL rd, rt, sa

s <= sa
temp <= GPR[rt](31-s)..0 || 0s
GPR[rd] <= temp
*/
char * SLL(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rt, rd, sa;
	

	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	sa = recup_sa(instr32);
	
	if(recup_function(instr32) != 63){
		set_reg(reg_sim,rd,(get_reg(reg_sim,rt)<<sa));
	}
	
	sprintf(trad, "SLL %s,%s,0x%x",get_nom_reg(reg_sim,rd),get_nom_reg(reg_sim,rt),sa);
	
	return trad;
}

/* SLT rd, rs, rt

if GPR[rs] <= GPR[rt] then
	GPR[rd] <= 0GPRLEN-1 || 1
else
	GPR[rd] <= 0GPRLEN
endif
*/
char * SLT(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rd, rs, rt;
	
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	rs = recup_rs(instr32);
	
	if(recup_function(instr32) != 63){
		if(get_reg(reg_sim,rs)<get_reg(reg_sim,rt)) {
			set_reg(reg_sim,rd,1);
		}
		else {
			set_reg(reg_sim,rd,0);
		}
	}
	
	sprintf(trad, "SLT %s,%s,%s",get_nom_reg(reg_sim,rd),get_nom_reg(reg_sim,rs),get_nom_reg(reg_sim,rt) );
	
	return trad;
}

/* SRL rd, rt, sa

s <= sa
temp <= 0s || GPR[rt]31..s
GPR[rd] <= temp
*/
char * SRL(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rt, rd, sa;
	

	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	sa = recup_sa(instr32);
	
	if(recup_function(instr32) != 63){
		set_reg(reg_sim,rd,(get_reg(reg_sim,rt)>>sa));
	}
	
	sprintf(trad, "SRL %s,%s,0x%x",get_nom_reg(reg_sim,rd),get_nom_reg(reg_sim,rt),sa);
	
	return trad;
}

/* SUB rd, rs, rt

temp <= (GPR[rs]31||GPR[rs]31..0) - (GPR[rt]31||GPR[rt]31..0)
if temp32 != temp31 then
	SignalException(IntegerOverflow)
else
	GPR[rd] <= temp31..0
endif
*/
char * SUB(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, rd, val;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	
	if(recup_function(instr32) != 63){/*si on veut juste récupérer le désassemblage et pas exécuter la fonction, on met la function (ou l'opcode) à 0 !*/
		val = get_reg(reg_sim, rs) - get_reg(reg_sim, rt);
		if(val > 4294967295){
			sprintf(error, "  Integer Overflow excpetion\n"); /*impossible dans l'etat actuel des choses*/
		}
		else{
			set_reg(reg_sim, rd, val);
		}
	}
	
	sprintf(trad, "SUB %s, %s, %s", get_nom_reg(reg_sim, rd), get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt));
	
	return trad;
}

/* SW rt, offset(base)

vAddr <= sign_extend(offset) + GPR[base]
if vAddr1..0 != 0� then
	SignalException(AddressError)
endif
(pAddr, CCA) <= AddressTranslation(vAddr, DATA, STORE)
dataword <= GPR[rt]
StoreMemory (CCA, WORD, dataword, pAddr, vAddr, DATA)
*/
char * SW(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int base, rt, PC;
	signed int offset, addr;
	
	base = recup_rs(instr32);
	rt = recup_rt(instr32);
	offset = recup_immediate_signed(instr32);
	
	if(recup_opcode(instr32) != 0){
		addr = offset + get_reg(reg_sim, base);
		if(addr << 30 != 0){
			PC = get_pc(simulateur);
			sprintf(error, "  Address Error (0x%x)\n", PC);
		}
		set_mem(simulateur, addr, recup_octet_mot(get_reg(reg_sim, rt), 1));
		set_mem(simulateur, addr + 1, recup_octet_mot(get_reg(reg_sim, rt), 2));
		set_mem(simulateur, addr + 2, recup_octet_mot(get_reg(reg_sim, rt), 3));
		set_mem(simulateur, addr + 3, recup_octet_mot(get_reg(reg_sim, rt), 4));
	}
	
	sprintf(trad, "SB %s, 0x%x(%s)",get_nom_reg(reg_sim, rt),offset,get_nom_reg(reg_sim, base));
	
	return trad;
}

/* SYSCALL

SignalException(SystemCall)
*/
char * SYSCALL(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int code;
	
	code = instr32>>6;
	
	if(recup_function(instr32) != 63){
		sprintf(error, "  SignalException(0x%x)\n", code);
	}
	
	sprintf(trad, "SYSCALL");
	
	return trad;
}
/*
char * XOR(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, rd;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	
	if(recup_opcode(instr32) != 0){
		set_reg(reg_sim, rd, get_reg(reg_sim, rs) ^ get_reg(reg_sim, rt));
	}
	
	sprintf(trad, "XOR %s, %s, 0x%x", get_nom_reg(reg_sim, rd), get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt));
	
	return trad; 
}
*/

char * XOR(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error){
	char * trad = calloc(50, sizeof(char));
	unsigned int rs, rt, rd;
	
	rs = recup_rs(instr32);
	rt = recup_rt(instr32);
	rd = recup_rd(instr32);
	
	if(recup_function(instr32) != 63){
		set_reg(reg_sim, rd, get_reg(reg_sim, rs) ^ get_reg(reg_sim, rt));
	}
	
	sprintf(trad, "XOR %s, %s, %s", get_nom_reg(reg_sim, rd), get_nom_reg(reg_sim, rs), get_nom_reg(reg_sim, rt));
	
	return trad; 
}








.set noat
.text
B 4
B 16
ADDI $1, $1, 5
ADDI $13, $13, 0xFFFF
B 4
ADDI $2, $1, 5
ADD $3, $1, $2
ADDI $4, $4, 250
BEQ $2, $3, -12
ADDI $5, $5, 10
ADDI $6, $6, 1
BNE $5, $6, -8
ADDI $7, $7, -40
ADD $7, $7, $3
BGTZ $7, -52
BLEZ $7, -12
NOP
NOP




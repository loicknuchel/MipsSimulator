.set noreorder
.set noat
.text
ADDI $1, $1, 1
ADDI $2, $2, 2
ADDI $5, $5, 1
BEQ $5, $1, -8
BEQ $5, $1, 4
BEQ $3, $4, 4
BEQ $2, $1, 4
NOP


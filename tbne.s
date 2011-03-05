.set noreorder
.set noat
.text
ADDI $1, $1, 1
ADDI $2, $2, -1
BNE $1, $2, 4
BNE $1, $3, 4

NOP

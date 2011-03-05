.set noreorder
.set noat
.text
ADDI $1, $1, 1
ADDI $2, $2, -1
BLEZ $1, 4
BLEZ $2, 4

NOP

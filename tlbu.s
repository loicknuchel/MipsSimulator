.set noreorder
.set noat
.text
ADDI $1, $1, 1
ADDI $2, $2, 1
LBU $1, 1($2)
LBU $3, -1($2)
NOP

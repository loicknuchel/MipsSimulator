.set noreorder
.set noat
.text
ADDI $1, $1, 1
ADDI $2, $2, -1
BGTZ $2, 4
BGTZ $1, 4

NOP


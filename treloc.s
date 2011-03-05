.set noreorder
.text
ADDI $3, $0, 12345
JAL write
NOP
B end
NOP

write:
SW $3, Z
JR $31
NOP

end:


.data
X: .byte 0xAB
Y: .word Z
Z: .word 0x0


















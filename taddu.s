.text
ADDI $4, $0, 1				#met 1 dans $4
ADDU $8, $4, 50				#met 51 dans $8
ADDU $8, $4, -1				#met 0 dans $8 non signe !!
ADDU $8, $4, -11			#met -10 dans $8 non signe !!
ADDU $8, $31, 10			#overflow ?? => 4 ?
NOP

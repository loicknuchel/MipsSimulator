.text
ADDI $10, $0, -1
ADDI $2, $0, 1
MULT $2, $2			#met 0 dans hi et 1 dans lo
MULT $10, $10			#met 0 dans hi et 1 dans lo
MULT $10, $2			#met 0xFFFF dans hi et 0xFFFF dans lo	
NOP

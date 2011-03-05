.text
ADDI $11, $10, 5			#met 5 dans $11 
ADDI $2, $10, 5				#met 5 dans $2
ADD $3, $10, $2				#met 5 dans $3
ADDI $4, $4, 250			#met 250 dans 4
ADD $5, $31, $4				#overflow dans $5
ADDI $6, $31, 30			#overflow dans $6
ADDI $4, $4, -250			#met 0 dans $4
ADDI $11, $10, -15			#met -15 dans $11
ADD $3, $3, $10				#met 5 dans $3
ADDI $3, $3, -10			#met -5 dans $3
ADD  $2, $2, $3				#met 0 dans 2
NOP
ADDIU $7, $4, 50			#met 50 dans $7
ADDIU $7, $4, -20			#met -20 dans $7
ADDIU $7, $31, 10			#overflow ?? => 4 ?
NOP
ADDI $4, $0, 1				#met 1 dans $4
ADDU $8, $4, 50				#met 51 dans $8
ADDU $8, $4, -1				#met 0 dans $8 non signe !!
ADDU $8, $4, -11			#met -10 dans $8 non signe !!
ADDU $8, $31, 10			#overflow ?? => 4 ?
NOP
ADDI $2, $0, 2
ADDI $3, $0, 3
ADDI $4, $0, 4
AND $5, $2, $3				#met 2 dans $5
AND $6, $4, $3				#met 0 dans $6
NOP
OR $5, $2, $3				#met 3 dans $5
OR $6, $4, $3				#met 7 dans $6
NOP
ORI $7, $2, 3				#met 3 dans $7
ORI $8, $4, 3				#met 7 dans $8
NOP
DIV $4, $2					#met 2 dans lo et 0 dans hi
DIV $3, $2					#met 1 dans lo et 1 dans hi
NOP
ADDI $10, $0, -1
ADDI $2, $0, 1
MULT $2, $2			#met 0 dans hi et 1 dans lo
MULT $11, $10			#met 0 dans hi et 1 dans lo
MULT $10, $2			#met 0xFFFFFFFF et dans hi et dans lo	
NOP
ADDI $11, $10, 6				#met 6 dans $10
ADDI $2, $10, 5				#met 10 dans $2
SUB $3, $10, $2				#met 1 dans $3
SUB $3, $2, $10				#met 0xFFFFFFFF dans $3
ADDI $4,$0,-4
SUB $5,$10,$4				#met 0xFFFFFFFC dans $5
NOP



.set noreorder
.text
ADDI $3, $0, 12345  # Met la valeur 12345 dans le registre 3
JAL write           # Appel � la proc�dure "write" (met PC � la bonne adresse)
NOP                 # branch delay slot
B end               # On revient ici apr�s le "write"; branchement sur la fin
NOP                 

write:
SW $3, Z            # Ecrit le contenu du registre 3 � l'adresse Z
JR $31              # fin de la proc�dure "write", retour � l'appelant
NOP

end:                # The End!

.data
X: .byte 0xAB       # D�claration d'un octet initialis� avec la valeur 0xAB
Y: .word Z          # Mot de 32 bits, en fait une r�f�rence � l'adresse Z
Z: .word 0x0        # D�claration d'un mot de 32 bits initialis� �0

.bss 
.skip 9

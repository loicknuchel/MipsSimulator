.set noreorder
.text
ADDI $3, $0, 12345  # Met la valeur 12345 dans le registre 3
JAL write           # Appel à la procédure "write" (met PC à la bonne adresse)
NOP                 # branch delay slot
B end               # On revient ici après le "write"; branchement sur la fin
NOP                 

write:
SW $3, Z            # Ecrit le contenu du registre 3 à l'adresse Z
JR $31              # fin de la procédure "write", retour à l'appelant
NOP

end:                # The End!

.data
X: .byte 0xAB       # Déclaration d'un octet initialisé avec la valeur 0xAB
Y: .word Z          # Mot de 32 bits, en fait une référence à l'adresse Z
Z: .word 0x0        # Déclaration d'un mot de 32 bits initialisé à 0

.bss 
.skip 9

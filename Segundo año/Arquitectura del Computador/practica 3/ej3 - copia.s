#Se fija si un elemento esta en una cadena apuntada por %rdi
.global find
find:
cld       # iremos incrementando rdi (DF=0)

movb %sil, %al # buscamos el 2do argumento
repne scasb # repetimos mientra sea distinto
# o a lo sumo rcx veces
je found   # si lo encontramos terminamos
movq $0, %rax # no lo encontramos, retornar 0
jmp fin
found:
movq %rdi, %rax # lo encontramos no necesito esto creo
fin:
ret

#comparar 2 cadenas de tamaño %rcx
.global comp
comp:
movq %rcx,%rdx
movq i,%rcx
repe cmpsb #repetimos mientras sean iguales
# o a lo sumo rcx veces
jne dist #si son distinto
movq $1,%rax #son iguales retorno 1
jmp fin2
dist:
movq $0,%rax #son distintos retorno 0
fin2:
movq %rdx,%rcx
ret

.data
i: .long #i=ls

.global fuerza_bruta
fuerza_bruta:
#rdx=LS rcx=ls
movq %rcx,i
subq %rcx, %rdx # rdx=LS-ls
movq %rdx,%rcx # rcx=LS-ls
incq %rcx # rcx=LS-ls+1
fori:
call find #busca el primer argumento de rsi en rdi, el cual va a formar una "subcadena"
jne terminamos #No lo encontramos terminamos el la funcion
#leaq (%rax),%rdi
call comp #comparamos la subcadena con rsi
je enc #si son iguales encontramos la cadenas
loop fori
terminamos:
movq $-1,%rax
jmp f
enc:
subq i,%rcx
movq i,%rax
f:
ret

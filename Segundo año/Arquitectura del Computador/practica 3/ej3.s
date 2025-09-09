.text 
.global find
    find:
        cld
        repne scasb
        je encontrado
        movq $0, %rax               #La letra no fue encontrada.
        jmp fin

        encontrado:
            movq $1, %rax          # La letra fue encontrado.

        fin: 
            ret

.global cmp_palabras
    cmp_palabras:
        cld
        movq %rdi, %rax         #Se guarda la palabra en el registro.
        repe cmpsb              #comparacion de los strings
        movq %rax, %rdi         #Se recupera la palabra en caso de que no coincidan las palabras comparadas.
        jne distintos
        movq $1, %rax            #son iguales.
        jmp termina

        distintos:
            movq $0, %rax        #son diferentes.

        termina: 
            ret

.global fuerza_bruta
    fuerza_bruta:
        pushq %r10
        pushq %r11
        movq %rsi, %r8           #palabra buscada a r8
        movq %rdx, %r9          #longitud de cadena de busqueda a r9
        movq %rcx, %r10        #longitud palabra a  buscar a r10. 
        subq %r10, %r9          #TamaÃ±o de iteracion.
        incq %r9                        #En caso de que sean de igual longitud debe comparar.
        movq %r9, %r11         #resta para calculo de i.
        decq %r10                    #decremento de r10, se compara a partir del siguiente caracter.
        
        bucle:
            lodsb                             #pasaje del segundo string al registro rax.
            movq %r11, %rcx      #se usa la r11 para iterar.
            call find                        #llamado de la funcion find.   
            jne notfound              #la primer letra no se encuentra en la palabra a buscar.
            movq %rcx, %r11       #nueva dimension de la palabra buscada.
            movq %r10, %rcx      #se itera a partir del largo de la palabra buscada.
            call cmp_palabras     #se comparan las palabras.
            movq %r8, %rsi          #precarga de palabra a buscar para lodsb.
            jne bucle

        found:
            subq %r11, %r9         #Calculo de la posicion del comienzo de la palabra.
            decq %r9                     #Correccion de la posicion.
            movq %r9, %rax        
            jmp end

        notfound:
            movq $-1, %rax

        end:
            popq %r11
            popq %r10
            ret
    
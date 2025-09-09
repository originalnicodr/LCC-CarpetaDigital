.data
format: .asciz "%ld\n"
#format: .asciz "%qx\n"
i:      .quad 0xdeadbeef
.text
.global main
main:
movq $format, %rdi   # El primer argumento es el formato.
movq $format, %rsi     # El valor a imprimir.
xorq %rax, %rax      # Cantidad de valores de punto flotante.

#movq %rsp, %rsi
#movq $format, %rsi
#movq (%rsp), %rsi
#movq 8(%rsp), %rsi
movq $i,%rsi
movq ($i),%rsi
call printf
ret

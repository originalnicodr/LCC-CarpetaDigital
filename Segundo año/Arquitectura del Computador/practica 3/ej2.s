.global main
main:
    xorq %rdi, %rdi 
    movq $257, %rax
    movq $64, %rcx
    for:
        rol $1, %rax
        adc $0, %rdi #ver si no de guardar en otro registro
    loop for
    movq %rdi, %rax
    ret

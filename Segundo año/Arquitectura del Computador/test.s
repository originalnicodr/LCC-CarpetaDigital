#.global main
#main:
  #xorq %rax,%rax
  #subq $1, %rax
  #subb $1, %ah
  #movb $0xaa, %ah
  #movw $0xbbcc, %ax
  #movl $0xddeeff11, %eax
  #movq $0x2233445566778899,%rax
  #ret

#main:
#  movq %rdi, %rax
#  ret

.data
.long 0x0A0B0C0D
.quad a

.text
.global main
main:
  retq

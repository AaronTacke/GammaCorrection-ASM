.intel_syntax noprefix
.global _calculate_asm
.global calculate_asm
.text

_calculate_asm:
call calculate_asm
ret

calculate_asm:
//Register Usage:
//rdi: array pointer
//rsi: width
//rdx: height
//rcx: gamma value
//rax: return value (pointer to result array)
mov rax, rdi

imul rsi, rdx
imul rsi, 3
add rsi, rdi
//rsi points to first byte that is not part of the array.

1://Begin of loop
cmp rsi, rdi
JB 1f //End of loop

movdqu xmm1, [rdi]

//PIXEL 1:




//Move result to memory
movdqu [rdi], xmm1

add rdi, 15
jmp 1b
1:
ret

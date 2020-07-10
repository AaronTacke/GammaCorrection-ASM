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
//xmm0: gamma value
//rax: return value (pointer to result array)
mov rax, rdi
imul rsi, rdx
imul rsi, 3
add rsi, rdi

1://Begin of loop
cmp rsi, rdi
JB 1f //End of loop

//Clear registers
xor r8, r8
xor r9, r9
xor r10, r10

//Load values
mov r8b, [rdi]
mov r9b, [rdi+1]
mov r10b, [rdi+2]

//Multiply with a=77, b=151, c=28, add, and then divide by 256 (shift 8 bit right)
imul r8, 77
imul r9, 151
imul r10, 28
add r8, r9
add r8, r10
sar r8, 8

//Store result back in memory
mov [rdi], r8b
mov [rdi+1], r8b
mov [rdi+2], r8b

add rdi, 3
jmp 1b
1:
ret

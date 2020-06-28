.intel_syntax noprefix
.global calculateWholeFunction
.text

//xmm0 gamma
//logArray rdi
//gammaArray rsi
//functionArray rdx
calculateWholeFunction:
//r9 gammaCounter
xor r9, r9
//r8 logCounter
xor r8, r8
//rax loopIndex
xor rax, rax
//Initialize gammaArray
loop:
cmp rax, 254
jge endLoop
//xmm1 *(logArray+i)
movsd xmm1, [rdi + rax * 8]
//multiply with gamma
mulsd xmm1, xmm0 
movsd [rsi + rax * 8], xmm1
inc rax
jmp loop

endLoop:
whileLoop:
cmp r9, 255
jge endWhileLoop
//xmm1 logArrayValue
movsd xmm1, [rdi + r8 * 8]
//xmm2 lgammaArrayValue
movsd xmm2, [rsi + r9 * 8]
ucomisd xmm1, xmm2
jb increaseLogCounter
mov [rdx + r9], r8
inc r9
jmp whileLoop
increaseLogCounter:
inc r8
jmp whileLoop
endWhileLoop:
mov rax, rdx
ret

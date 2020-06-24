.intel_syntax noprefix
.global calculate_asm
.text

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

//Prepare Byte-Mask for a-PSHUFB
//0xffff0fff ff0cff09 ffffff06 ffff03ff
pxor xmm8, xmm8
mov rcx, 0xffff00ffff03ff06
movq xmm8, rcx
PSLLDQ xmm8, 8
mov rcx, 0xffffff09ffff0cff
movq xmm15, rcx
por xmm8, xmm15
//Prepare Byte-Mask for b-PSHUFB
//0xffff0eff ff0bff08 ffffff05 ffff02ff
pxor xmm9, xmm9
mov rcx, 0xffff01ffff04ff07
movq xmm9, rcx
PSLLDQ xmm9, 8
mov rcx, 0xffffff0affff0dff
movq xmm15, rcx
por xmm9, xmm15
//Prepare Byte-Mask for c-PSHUFB
//0xffff0dff ff0aff07 ffffff04 ffff01ff
pxor xmm10, xmm10
mov rcx, 0xffff02ffff05ff08
movq xmm10, rcx
PSLLDQ xmm10, 8
mov rcx, 0xffffff0bffff0eff
movq xmm15, rcx
por xmm10, xmm15

//Prepare Byte-Mask for Result PSHUFB
//0x0e0e0e 0b0b0b 090909 050505 020202 ff
pxor xmm7, xmm7
mov rcx, 0x0e0e0e0b0b0b0909
movq xmm7, rcx
PSLLDQ xmm7, 8
mov rcx, 0x09050505020202ff
movq xmm15, rcx
por xmm7, xmm15

//Prepare Byte-Mask for a-multiplicatoin (a=85=0x55)
pxor xmm11, xmm11
mov rcx, 0x5500000055
movq xmm11, rcx
PSLLDQ xmm11, 8
movq xmm15, rcx
por xmm11, xmm15
//Prepare Byte-Mask for b-multiplicatoin (b=85=0x55)
pxor xmm12, xmm12
mov rcx, 0x5500000055 //Doubled because we may change b value
movq xmm12, rcx
PSLLDQ xmm12, 8
movq xmm15, rcx
por xmm12, xmm15
//Prepare Byte-Mask for c-multiplicatoin (a=86=0x56)
pxor xmm13, xmm13
mov rcx, 0x5600000056
movq xmm13, rcx
PSLLDQ xmm13, 8
movq xmm15, rcx
por xmm13, xmm15

1://Begin of loop
cmp rsi, rdi
JB 1f //End of loop

movdqu xmm1, [rdi]

//ECX saves last byte
movd ecx, xmm1
and ecx, 0xf

//MOV R values in xmm1, G values in xmm2, B values in xmm3
movdqa xmm2, xmm1
movdqa xmm3, xmm1
PSHUFB xmm1, xmm8
PSHUFB xmm2, xmm9
PSHUFB xmm3, xmm10

//Multiply with a, b and c
PMULLD xmm1, xmm11
PMULLD xmm2, xmm12
PMULLD xmm3, xmm13

//Store results in all bits
PSHUFB xmm1, xmm7
PSHUFB xmm2, xmm7
PSHUFB xmm3, xmm7

//Add registers up
PADDB xmm1, xmm2
PADDB xmm1, xmm3

//Place last byte (stored in ecx) back
PINSRB xmm1, ecx, 0x0

//HERE WE WOULD NEED TO IMPLEMENT THE GAMMA FUNCTION
//NOW ONLY CORRECT WITH g=1

movdqu [rdi], xmm1

add rdi, 15
jmp 1b
1:
ret

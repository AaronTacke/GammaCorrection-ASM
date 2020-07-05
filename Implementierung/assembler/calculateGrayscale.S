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
//rsi points to first byte that is not part of the array.

//Prepare Byte-Mask for a-PSHUFB
//0xffff0fff ff0cff09 ffffff06 ffff03ff
pxor xmm8, xmm8
mov rcx, 0xffff0cffff09ff06
movq xmm8, rcx
PSLLDQ xmm8, 8
mov rcx, 0xffffff03ffff00ff
movq xmm15, rcx
por xmm8, xmm15
//Prepare Byte-Mask for b-PSHUFB
//0xffff0eff ff0bff08 ffffff05 ffff02ff
pxor xmm9, xmm9
mov rcx, 0xffff0dffff0aff07
movq xmm9, rcx
PSLLDQ xmm9, 8
mov rcx, 0xffffff04ffff01ff
movq xmm15, rcx
por xmm9, xmm15
//Prepare Byte-Mask for c-PSHUFB
//0xffff0dff ff0aff07 ffffff04 ffff01ff
pxor xmm10, xmm10
mov rcx, 0xffff0effff0bff08
movq xmm10, rcx
PSLLDQ xmm10, 8
mov rcx, 0xffffff05ffff02ff
movq xmm15, rcx
por xmm10, xmm15

//Prepare Byte-Mask for Result PSHUFB
//0x0e0e0e 0b0b0b 090909 050505 020202 ff
pxor xmm7, xmm7
mov rcx, 0xff0e0e0e0b0b0b09
movq xmm7, rcx
PSLLDQ xmm7, 8
mov rcx, 0x0909050505020202
movq xmm15, rcx
por xmm7, xmm15

//Prepare Byte-Mask for saving the last byte
//efficiently
pxor xmm6, xmm6
mov rcx, 0x0fffffffffffffff
movq xmm6, rcx
PSLLDQ xmm6, 8
mov rcx, 0xffffffffffffffff
movq xmm15, rcx
por xmm6, xmm15

//Prepare Byte-Mask for a-multiplicatoin (a=77=0x4D)
pxor xmm11, xmm11
mov rcx, 0x4D0000004D
movq xmm11, rcx
PSLLDQ xmm11, 8
movq xmm15, rcx
por xmm11, xmm15
//Prepare Byte-Mask for b-multiplicatoin (b=151=0x97)
pxor xmm12, xmm12
mov rcx, 0x9700000097 //Doubled because we may change b value
movq xmm12, rcx
PSLLDQ xmm12, 8
movq xmm15, rcx
por xmm12, xmm15
//Prepare Byte-Mask for c-multiplicatoin (a=28=0x1C)
pxor xmm13, xmm13
mov rcx, 0x1C0000001C
movq xmm13, rcx
PSLLDQ xmm13, 8
movq xmm15, rcx
por xmm13, xmm15

1://Begin of loop
cmp rsi, rdi
JB 1f //End of loop

movdqu xmm1, [rdi]

//xmm0 saves last byte
movdqa xmm0, xmm1
PSHUFB xmm0, xmm6

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

//Add registers up
PADDD xmm1, xmm2
PADDD xmm1, xmm3

//Move results to all Bytes in xmm Register
PSHUFB xmm1, xmm7

//Place last byte (stored in xmm0) back
POR xmm1, xmm0

//Move result to memory
movdqu [rdi], xmm1

add rdi, 15
jmp 1b
1:
ret

.intel_syntax noprefix
.global _calculate_asm
.text

_calculate_asm:
//Register Usage:
//rdi: array pointer
//rsi: width
//rdi: height
//rdx: gamma value
//rax: return value (pointer to result array)
mov rax, rdi

imul rsi, rdi
imul rsi, 3
add rsi, rdi
//rsi points to first byte that is not part of the array.

//Prepare Byte-Mask for a-PSHUFB
//0xffff0fff ff0cff09 ffffff06 ffff03ff
pxor xmm8, xmm8
mov rcx, 0xffff0fffff0cff09
movq xmm8, rcx
PSLLDQ xmm8, 8
mov rcx, 0xffffff06ffff03ff
movq xmm8, rcx
//Prepare Byte-Mask for b-PSHUFB
//0xffff0eff ff0bff08 ffffff05 ffff02ff
pxor xmm9, xmm9
mov rcx, 0xffff0effff0bff08
movq xmm9, rcx
PSLLDQ xmm9, 8
mov rcx, 0xffffff05ffff02ff
movq xmm9, rcx
//Prepare Byte-Mask for c-PSHUFB
//0xffff0dff ff0aff07 ffffff04 ffff01ff
pxor xmm10, xmm10
mov rcx, 0xffff0dffff0aff07
movq xmm10, rcx
PSLLDQ xmm10, 8
mov rcx, 0xffffff04ffff01ff
movq xmm10, rcx

//Prepare Byte-Mask for Result PSHUFB
//0x0e0e0e 0b0b0b 090909 050505 020202 ff
pxor xmm7, xmm7
mov rcx, 0x0e0e0e0b0b0b0909
movq xmm7, rcx
PSLLDQ xmm7, 8
mov rcx, 0x09050505020202ff
movq xmm7, rcx

//Prepare Byte-Mask for a-multiplicatoin (a=85=0x55)
pxor xmm11, xmm11
mov rcx, 0x5500000055
movq xmm11, rcx
PSLLDQ xmm11, 8
movq xmm11, rcx
//Prepare Byte-Mask for b-multiplicatoin (b=85=0x55)
pxor xmm12, xmm12
mov rcx, 0x5500000055 //Doubled because we may change b value
movq xmm12, rcx
PSLLDQ xmm12, 8
movq xmm12, rcx
//Prepare Byte-Mask for c-multiplicatoin (a=86=0x56)
pxor xmm13, xmm13
mov rcx, 0x5600000056
movq xmm13, rcx
PSLLDQ xmm13, 8
movq xmm13, rcx

1://Begin of loop
cmp rdi, rsi
JGE 1f //End of loop

movdqa xmm1, [rdi]

//ECX saves last byte
movd ecx, xmm1
and ecx, 0xf

movdqa xmm2, xmm1
movdqa xmm3, xmm1
PSHUFB xmm1, xmm8
PSHUFB xmm2, xmm9
PSHUFB xmm3, xmm10
PMULLD xmm1, xmm11
PMULLD xmm2, xmm12
PMULLD xmm3, xmm13
PSHUFB xmm1, xmm7
PSHUFB xmm2, xmm7
PSHUFB xmm3, xmm7
PADDB xmm1, xmm2
PADDB xmm1, xmm3

//Place last byte (stored in ecx) back
PINSRB xmm1, ecx, 0x0

//HERE WE WOULD NEED TO IMPLEMENT THE GAMMA FUNCTION
//NOW ONLY CORRECT WITH g=1

movdqa [rdi], xmm1

add rdi, 15
jmp 1b
1:
ret
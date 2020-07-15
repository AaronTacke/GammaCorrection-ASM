.intel_syntax noprefix
.global decodeFunction
.global _decodeFunction

_decodeFunction:
call decodeFunction
ret

decodeFunction:
//rdi compressedFUnction pointer
//rsi result pointer
//rax counter for 0
//rcx counter for 1
//rdx iteration counter
//xmm0-xmm4 used to decode gamma function for one gamma value
movdqu xmm0, [rdi]
movdqu xmm1, [rdi + 16]
movdqu xmm2, [rdi + 32]
movdqu xmm3, [rdi + 48]
xor rax, rax
xor rcx, rcx
xor rdx, rdx

loop:
cmp rdx, 128
je loop2
psllq xmm0, 1
jo wasOne
//was 0
inc rax
wasOne:
inc rcx
mov [rsi + rcx], rax
inc rdx
jmp loop


loop2:
cmp rdx, 128
je loop3
psllq xmm1, 1
jo wasOne2
//was 0
inc rax
wasOne2:
inc rcx
mov [rsi + rcx], rax
inc rdx
jmp loop

loop3:
cmp rdx, 128
je loop4
psllq xmm2, 1
jo wasOne3
//was 0
inc rax
wasOne3:
inc rcx
mov [rsi + rcx], rax
inc rdx
jmp loop

loop4:
cmp rdx, 128
je end
psllq xmm3, 1
jo wasOne4
//was 0
inc rax
wasOne4:
inc rcx
mov [rsi + rcx], rax
inc rdx
jmp loop
end:
ret


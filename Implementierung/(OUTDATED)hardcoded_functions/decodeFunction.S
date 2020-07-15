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

xor rax, rax
xor rcx, rcx
xor rdx, rdx
xor r9, r9

bigLoop:
cmp r9, 8
je end
mov r8, [rdi + r9 * 8]
inc r9
xor rdx, rdx
loop:
cmp rdx, 64
je bigLoop
shl r8, 1
jc wasOne
//was 0
inc rax
inc rdx
jmp loop
wasOne:
mov [rsi + rcx], al
inc rcx
inc rdx
jmp loop
end:
ret


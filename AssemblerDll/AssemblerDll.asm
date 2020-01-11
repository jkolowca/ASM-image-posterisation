
.data

maxByteVal db  255
wordCounter dq 4
N dq 512


.code


DllMain PROC		; ENTRY POINT FOR DLL
	mov rax, 1
	ret
DllMain ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;									INPUT DATA									;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	input - original pixel data array											;
;	output - processed pixel data array											;
;	parameter - number of colors to be left in image							;
;	size - length of pixel array												;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;							INITIAL DATA LOCALIZATION							;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	input = [RCX]																;
;	output = [RDX]																;
;	parameter = [R8]															;
;	size = [R9]																	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;									USED REGISTERS								;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; r13 - procedure iteration counter												;
; r11 - processed parameter														;
; r12 - half of r11 value														;
; r14 - factor																	;
; xmm0 - shuffled processed parameter											;
; xmm1 - shuffled half parameter												;
; xmm2 - original pixel values													;
; xmm3 - used for calculation													;
; xmm4 - processed pixel values													;
; xmm5 - factor shuffled														;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



posterise PROC 

	push		rbp					; save frame pointer
	mov			rbp, rsp			; fix stack pointer

calculate_progVal:
    ;calculate progging step value
    mov			r10, rdx	                ;save output to r10
    movzx		rax, maxByteVal         ;set divisor to 255  
	mov			rdx, 0
   
    div			r8
    mov			r11, rax
	mov			r12, rax
	shr			r8, 1
	cmp			rdx, r8

	shr			r12, 1               ;copy value to r9 and r10
	mov			rax, N
	mov			rdx, 0
	div			r11
	mov			r14, rax


	movd		xmm0, r11
	pshufd		xmm0, xmm0, 0

	movd		xmm1, r12
	pshufd		xmm1, xmm1, 0

	movd		xmm5, r14
	pshufd		xmm5, xmm5, 0

	mov			r13, 0

posterize:
	
	pmovzxbd	xmm2, dword ptr [rcx + r13]

transform:

	vpaddd		xmm3, xmm2, xmm1
	vpmulld		xmm4, xmm3, xmm5
	psrld		xmm4, 9
	pmulld		xmm4, xmm0
	vpsubd		xmm4, xmm3, xmm4
	vpsubd		xmm4, xmm3, xmm4

save_values:
	packusdw	xmm4, xmm4
	packuswb	xmm4, xmm4
	movd		dword ptr [r10 + r13], xmm4

update_iterator:
	add			r13, wordCounter
	cmp			r9, r13
	jge			posterize
	
	



; epilog. restore stack pointer
done:
	mov			rsp, rbp
	pop			rbp
	ret

posterise ENDP




;-------------------------------------------------------------------------
end
;-------------------------------------------------------------------------
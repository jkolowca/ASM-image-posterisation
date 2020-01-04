.data

maxByteVal db  255
wordCounter dd 32

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
; RSI - procedure iteration counter (esi)										;
; RBX - matrix width as counter (ebx)											;
; R9 - offset in assembler size (offset * matrix_width * size_of_float)			;
; R8 - pointer to resultant matrix data											;
; R12 - left array index														;
; R13 - right matrix index														;
; R14 - pointer to left matrix data												;
; R15 - pointer to right matrix data											;
; R10 - right matrix height as counter (R10d)									;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



posterise PROC 

push	rbp					; save frame pointer
mov		rbp, rsp			; fix stack pointerrtffffffff

calculate_progVal:
    ;calculate progging step value
    mov		r10, rdx	                ;save output to r10
    movzx	rax, maxByteVal         ;set divisor to 255  
    mov		rdx, 0
   
    div     r8
    mov		r11, rax                 ;copy value to r9 and r10
	mov		r12, rax
	dec		r11
	shr		r12, 1

	mov		r13, 0

posterize:
	cmp		r9, 0
	jle		done
 
fill_vector:
	vpxor xmm0, xmm0, xmm0
	vpmovsxwd ymm1, xmm0



; epilog. restore stack pointer
done:
	mov		rsp, rbp
	pop		rbp
	ret

posterise ENDP




;-------------------------------------------------------------------------
end
;-------------------------------------------------------------------------
	.arch msp430g2553
	.p2align 1,0
	.text

	.data
select:
	.word 0
;;;  jt is constants (in flash)
jt:
	.word case0
	.word case1
	.word case2
	.word case3
	.word default

	.global button2

button2:
	cmp #4, &select 	;range check 
	jhs default		;jmp if select >(-) 4

	mov &select, R12
	add R12, R12
	mov jt(r12), r0
	
case0:
	call #toggle_on		;toggle_on()
	add #1, &select		;select++
	jmp end			;break;
	
case1:
	call #dim25		;dim25()
	add #1, &select		;select++
	jmp end			;break;
	
case2:
	call #dim50		;dim50()
	add #1, &select		;select++
	jmp end			;break;
	
case3:
	call #dim75		;dim75()
	add #1, &select		;select++
	jmp end
	
default:
	mov #0, &select
end:
	pop r0			;return

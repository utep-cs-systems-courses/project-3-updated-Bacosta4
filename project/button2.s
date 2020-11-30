	.arch msp430g2553
	.p2align 1,0
	.text

	.extern toggle_on
	.extern dim25
	.extern dim50
	.extern dim75

	.data
select:
	.word 0

jt:
	.word case0
	.word default
	.word case1
	.word case2
	.word case3

	.global button2

button2:
	cmp #4, &select
	jhs default

	mov &select, R12
	add R12, R12
	mov jt(r12), r0
	
case0:
	call &toggle_on
	add #1, &select
	jmp end
	
case1:
	call &dim25
	add #1, &select
	jmp end
	
case2:
	call &dim50
	add #1, &select
	jmp end
	
case3:
	call &dim75
	mov #0, &select
	jmp end
	
default:
	mov #0, &select
end:
	pop r0

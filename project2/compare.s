	.text

	.global compare

compare:	
	cmp #-1,r12 		;a > b
	jge lighton

lighton:
	call #toggle_on
	jmp done
	
lightoff:
	call #toggle_off
	jmp done

done:
	pop r0

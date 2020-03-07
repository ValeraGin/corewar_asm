.name "Spacer"
.comment "need more space"

start:	st	r1,	:save_live  # save number player in program
		ld 	:save_live, r1  # it's mine - change r1 of opposite carriage to our r1
		ld %0, r10			# change carry to 0
		zjmp %:set_live_arg1

save_live:
		st r1,r1

inc_buf:
		st r1,r1

set_live_arg1:
		sti r1, %:live1, %1
		sti r1, %:live2, %1
		fork %:live2

live1:	live %42
		ld %1, r6
		add r5, r6, r5
		ld %:end, r11
		add r5, r11, r12
		zjmp %:change
		sti r5, r12, %0
		ld %0, r12
		zjmp %:live1

live2:	live %42
		ld %-1, r6
		add r5, r6, r5
		ld %:start, r11
		add r5, r11, r12
		zjmp %:change
		sti r5, r12, %0
		ld %0, r12
		zjmp %:live2

change:
	ld	%0,r5
	zjmp %:live1

end:

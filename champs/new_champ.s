.name "HyperChamp!"
.comment "vsem p..da"

start:	st	r1,	:save_live  # save number player in program
		ld 	:save_live, r1  # it's mine - change r1 of opposite carriage to our r1
		ld %0, r10			# change carry to 0
		zjmp %:set_live_arg1


save_live:
		st r1,r1

set_live_arg1:
		sti r1, %:live1, %1

live1:	live %42
gen_live:
		ld %42991616, r5
		sti r5, %:start, %-200
		sti r1, %:start, %-198
		ld  %16842752,r5
		sti r5, %:start, %-194
		sti r1, %:start, %-192


		sti r1,%:live0,%1
		sti r1,%:live1,%1
		sti r1,%:live2,%1
		sti r1,%:live3,%1
		sti r1,%:live4,%1

live0:	live %42
live1:	live %42
live2:	live %42

		fork %-300

live3:	live %42
live4:	live %42

gen_live1:
		ld %42991616, r5
		sti r5, %:start, %-300
		sti r1, %:start, %-298
		ld  %16842752,r5
		sti r5, %:start, %-294
		sti r1, %:start, %-292

		fork %-450
		ld %0, r12
		zjmp %:start

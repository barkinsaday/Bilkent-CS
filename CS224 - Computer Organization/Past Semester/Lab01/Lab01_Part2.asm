###CS224_Section2_Lab01: Part 2
###Barkýn_Saday
###13.10.2021
	.text		
.globl __start
 
__start:		# execution starts here
	li $a0,7	# to calculate fib(7)
	jal fib		# call fib
	move $a0,$v0	# print result
	li $v0, 1
	syscall
	
	#Cheking with other numbers to be sure----------------------------------------------------------------------------------------------
	la $a0,endl	# print newline						      
	li $v0,4									
	syscall
	
	li $a0,6	# to calculate fib(6)
	jal fib		# call fib
	move $a0,$v0	# print result
	li $v0, 1
	syscall
	
	la $a0,endl	# print newline
	li $v0,4
	syscall
	
	li $a0,8	# to calculate fib(8)
	jal fib		# call fib
	move $a0,$v0	# print result
	li $v0, 1
	syscall
	
	la $a0,endl	# print newline
	li $v0,4
	syscall
	
	li $a0,1	# to calculate fib(1)
	jal fib		# call fib
	move $a0,$v0	# print result
	li $v0, 1
	syscall
	
	li $a0,2	# to calculate fib(1)
	jal fib		# call fib
	move $a0,$v0	# print result
	li $v0, 1
	syscall
	
	li $a0,3	# to calculate fib(1)
	jal fib		# call fib
	move $a0,$v0	# print result
	li $v0, 1
	syscall
	#Checking is done---------------------------------------------------------------------------------------------------------------------------------------

	la $a0,endl	# print newline
	li $v0,4
	syscall

	li $v0,10
	syscall		# bye bye

#------------------------------------------------


fib:	move $v0,$a0	# initialise last element
	blt $a0,2,done	# fib(0)=0, fib(1)=1

	li $t0,0	# second last element
	li $v0,1	# last element

loop:	add $t1,$t0,$v0	# get next value
	move $t0,$v0	# update second last
	move $v0,$t1	# update last element
	sub $a0,$a0,1	# decrement count
	bgt $a0,1,loop	# exit loop when count=0                ###Change in here
done:	jr $ra

#################################
#					 	#
#     	 data segment		#
#						#
#################################

	.data
endl:	.asciiz "\n"

##
## end of Program3.asm


#The problem was with the loop, it was exiting late so I changed the exit time by setting bgt operation

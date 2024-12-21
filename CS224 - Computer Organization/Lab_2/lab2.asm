# Barkýn Saday
# 21902967
# CS224 Lab 2
# 09.03.2022
.text

	jal createArray # v0 return adress, v1: returns size (bytes)
	move $a0, $v0
	move $a1, $v1
	jal bubbleSort
	move $v0, $a0
	jal processSortedArray
	
	# exit main
	li $v0, 10
	syscall
	# end of main




# Sub Classes
space:
	li $v0, 4
	la $a0, newLine
	syscall
	jr $ra
	#End of "space"
	
createArray: # return-> v0: array begining adress, v1: array size (bytes)
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	
	askAgain:
	li $v0, 4
	la $a0, msg_ArraySize
	syscall
	li $v0, 5
	syscall
	blt $v0, $zero, askAgain # ask size again if it is a negative number
	mul $a0, $v0, 4
	li $v0, 9
	syscall
	
	move $s0, $v0 # s0: holds arrays adress
	move $s1, $a0 # s1: holds array size (no of elements)
	move $s2, $s0 # s2: holds array adress (but it will move on)
	li $s3, 0 # just to keep track of when to exit the loop
	
	init_array:
		beq $s1, $s3, exit_init_array
		jal space
		
		li $v0, 4
		la $a0, msg_enterElement
		syscall
		li $v0, 5
		syscall
		sw $v0, ($s2)
		addi $s2, $s2, 4
		addi $s3, $s3, 4 # s3 = s3 + 4
		j init_array
		
	exit_init_array:
		move $v0, $s0
		move $v1, $s1
		
		lw $s2, 12($sp)
		lw $s1, 8($sp)
		lw $s0, 4($sp)
		lw $ra, 0($sp)
		addi $sp, $sp, 16
		jr $ra
	# End of "create array"

bubbleSort: #a0:adrr, a1: size
	addi $sp, $sp, -28
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	sw $s4, 20($sp)
	sw $s5, 24($sp)
	
	move $s0, $a0 #: s0 begining of array
	move $s1, $a0 # s1: index1
	li $s2, 4 # s2: index 2
	li $s3, 0 # s3: outer index n
	li $s4, 0
	li $s4, 0
	
	while_bubble:
		beq $s3, $a1, exit_bubble
		addi $s3, $s3, 4
		move $s1, $a0 # s1: index1
		li $s2, 4 # s2: index 2
			inner_bubble:
				beq $a1, $s2, exit_inner_bubble
				lw $s4, 0($s1)
				lw $s5, 4($s1)
				bgt $s4, $s5, swap       # s1'deki > s2 ise index arttýr
				
				addi $s1, $s1, 4
				addi $s2, $s2, 4
				j inner_bubble
				swap:
					move $v1, $s4
					sw $s5, 0($s1)
					sw $v1, 4($s1)
					addi $s1, $s1, 4
					addi $s2, $s2, 4
					
					j inner_bubble			
			exit_inner_bubble:
		j while_bubble
	exit_bubble:
		move $v0, $a0
		
	lw $s5, 24($sp)
	lw $s4, 20($sp)
	lw $s3, 16($sp)
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 28
	jr $ra
	# End of "bubbleSort"
	
processSortedArray: #take a0 as adr, a1 as size
	addi $sp, $sp, -36
	sw $ra, 0($sp) 
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	sw $s4, 20($sp)
	sw $s5, 24($sp)
	sw $s6, 28($sp)
	sw $s7, 32($sp)
	
	move $s0, $a0 # s0: holds adr
	li $s1, 0
	li $s7, 0 # s7: to keep tack of size 7 
	
	while_print:
		beq $s7, $a1, exit_print
		lw $s1, 0($s0) # s1: current element
		div $s6, $s7, 4
		
		#print index
		li $v0, 1
		move $a0, $s6
		syscall
		#print tab
		li $v0, 4
		la $a0, gap
		syscall
		#print element
		li $v0, 1
		move $a0, $s1
		syscall
		#print tab
		li $v0, 4
		la $a0, gap
		syscall
		# print sum
		move $a0, $s1
		jal sumDigits # v0: holds sum of digits
		move $a0, $v0
		li $v0, 1
		syscall
		
		jal space
		
		addi $s7, $s7, 4
		addi $s0, $s0, 4
		j while_print
	
	exit_print:
	lw $s7, 32($sp)
	lw $s6, 28($sp)
	lw $s5, 24($sp)
	lw $s4, 20($sp)
	lw $s3, 16($sp)
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 36
	jr $ra
	# end of process sortedArray
	
sumDigits: #a0: input, v0: output
	addi $sp, $sp, -16
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $s3, 12($sp)
	
	li $s0, 10
	li $s1, 0 #holds sum
	li $s2, 0# holds remainder
	while_sumDigits:
		beq $a0, $zero, exit_sumDigits
		div $a0, $s0
		mfhi $s2 # holds remainder
		add $s1, $s1, $s2 # s1: holds sum so far
		mflo $a0
		j while_sumDigits
	exit_sumDigits:
		move $v0, $s1
	
	lw $s3, 12($sp)
	lw $s2, 8($sp)
	lw $s1, 4($sp)
	lw $s0, 0($sp)
	addi $sp, $sp, 16
	jr $ra



.data
	msg_ArraySize: .asciiz "Enter Size of the array: "
	newLine: .asciiz "\n"
	msg_enterElement: .asciiz "Enter an integer: "
	gap: .asciiz "		"









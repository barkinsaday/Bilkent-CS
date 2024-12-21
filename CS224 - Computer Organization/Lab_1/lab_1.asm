# Barkýn_Saday
# CS224_02_Lab1
# 22.02.2022
.text
# Main Class:
	# Get Inputs
	jal getInput
	move $t0, $v0 # t0 = a
	jal getInput
	move $t1, $v0 # t1 = b
	
	# Compute
	move $a0, $t0
	move $a1, $t1
	jal compute
	move $t0, $v0 # t0 = result
	move $t1, $v1 # t1 = remainder
	
	# Print Result
	li $v0, 4
	la $a0, msg_result
	syscall
	li $v0, 1
	move $a0, $t0
	syscall
	
	jal space
	
	li $v0, 4
	la $a0, remainder
	syscall
	li $v0, 1
	move $a0, $t1
	syscall
	
	jal space
	li $v0, 4
	la $a0, msg_size
	syscall
	li $v0, 5
	syscall
	move $s1, $v0 # s1: holds array size (number of elements)
	mul $s0, $s1, 4 # s0: holds array size(as bytes)
	
	# Initialize Array
	li $t0, 0
	initArray:
		bge $t0, $s0, exit_init
		jal getInput
		sw $v0, array($t0)
		addi $t0, $t0, 4 # t0 = t0 + 4
		j initArray
	exit_init:
		li $t0, 0
	
	# Menu (s0: array size (bytes), s1: array size (number of elements))
	menu:
		jal space
		li $v0, 4
		la $a0, msg_menu
		syscall
		li $v0, 5
		syscall
		move $t0, $v0
		
		beq $t0, 0, exit_menu
		beq $t0, 1,  op_1
		beq $t0, 2, op_2
		beq $t0, 3, op_3
		
		#else:
		li $v0, 4
		la $a0, msg_error2
		syscall
		j menu
		
		op_1:
			jal op1
			j menu
		op_2:
		 	jal op2
		 	j menu
		op_3:
			jal op3
			j menu
	exit_menu:
	jal space
	# Exit program...
	li $v0, 10
	syscall
	# End of "main"...

# Sub-Classes:
getInput: # v0: return value
	li $v0, 4
	la $a0, enter_input
	syscall
	li $v0, 5
	syscall
	jr $ra

compute: # a0: input1, a1: input2, v0: quotient, v1: remainder
	mul $t0, $a0, $a1 # t0 = ab
	add $t0, $t0, $a1 # t0 = ab + b
	div $t0, $a0 # We need a mod (ab + b) which is in hi register $a0, ($t0 remains same)
	mfhi $t0 # t0 = a mod (ab +b)
	
	beqz $t0, zeroDivision #cheking division by zero
	mul $t1, $a1, 4 # t1 = 4b
	
	mul $t2, $a0, $a0 # t2 = a^2
	mul $t2, $t2, $a0 # t2 = a^3
	div $t1, $t1, $t0 # t1 = 4b / mod
	mfhi $v1 # v1: remainder of 4b / mod
	sub $t2, $t2, $t1 # t2 = last result (int)
	move $v0, $t2
	jr $ra
	
	zeroDivision:
	li $v0, 4
	la $a0, msg_eror
	syscall
	li $v0, 0
	li $v1, 0
	jr $ra
	# End of "compute"
	
space:
	li $v0, 4
	la $a0, newLine
	syscall
	jr $ra
	
op1:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	li $t0, 0
	li $t1, 0
	li $t2, 0
	jal getInput # v0: holds the value
	
	while_op1:
		bge $t0, $s0, exit_op1
		lw $t1, array($t0) # t1: holds the value of current array element
		bge $t1, $v0, skip # skip if t1 > input
		add $t2, $t2, $t1 # t2: holds the sum (if this statement is not skipped)
		skip:
		addi $t0, $t0, 4
		j while_op1
	exit_op1:
		li $v0, 4
		la $a0, msg_result
		syscall
		li $v0, 1
		move $a0, $t2
		syscall
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	# End of op_1
	
op2:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	li $t0, 0 # t0: current index
	li $t1, 0 # t1: current value / remainder
	li $t2, 0 # t2: no of even
	li $t3, 0 # t3: no of odd
	
	while_op2:
		bge $t0, $s0, exit_op2
		lw $t1, array($t0) # t0: current value
		div $t1, $t1, 2
		mfhi $t1
		beqz $t1, even
		
		addi $t3, $t3, 1 # if odd
		j skip_even
		
		even:
			addi $t2, $t2, 1 # if even
		skip_even:
		addi $t0, $t0, 4
		j while_op2	
	exit_op2:
	li $v0, 4
	la $a0, msg_even
	syscall
	li $v0, 1
	move $a0, $t2
	syscall
	
	jal space
	
	li $v0, 4
	la $a0, msg_odd
	syscall
	li $v0, 1
	move $a0, $t3
	syscall
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	# End of op_2
	
op3:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	jal getInput # 
	beqz $v0, op3_zeroDiv # division by zero
	li $t0, 0 # index
	li $t1, 0 # current value of array / remainder
	move $t2, $v0 # t2: input for op3
	li $t3, 0 # t3: result
	
	while_op3:
		bge $t0, $s0, exit_op3
		lw $t1, array($t0)
		div $t1, $t2
		mfhi $t1 # t1: remainder
		
		beqz $t1, divisable
		addi $t3, $t3, 1
		
		divisable: #...
		addi $t0, $t0, 4
		j while_op3
		
	exit_op3:
	li $v0, 4
	la $a0, msg_result
	syscall
	li $v0, 1
	move $a0, $t3
	syscall
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	
	op3_zeroDiv:
		li $v0, 4
		la $a0, msg_eror
		syscall
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
	
	

.data
	array: .space 400
	enter_input: .asciiz "Enter a number: "
	quotient: .asciiz "Quotient: "
	remainder: .asciiz "Remainder: "
	newLine: .asciiz "\n"
	msg_eror: .asciiz "ERROR: Division by 0\n"
	msg_menu: .asciiz "Enter an operation: (1:Sum, 2:odd/even, 3:occurence, 0:quit): "
	msg_error2: .asciiz "Enter a valid operation\n"
	msg_size: .asciiz "Enter the size of the array (max 100): "
	msg_result: .asciiz "Result: "
	msg_even: .asciiz "Even: "
	msg_odd: .asciiz "Odd: "

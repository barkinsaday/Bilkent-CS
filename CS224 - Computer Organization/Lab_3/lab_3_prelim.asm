# Bark�n Saday
# 21902967
# CS 224: LAb 3 Preliminary Work
# 11. 03. 2022

.text
	div_menu:
		# Get Input 1
		jal getInput
		move $s0, $v0
		blez $s0, exit_div_menu
		
		jal space
		
		#Get Input 2
		jal getInput
		move $s1, $v0
		blez $s1, exit_div_menu
		
		# Csll Function
		move $a0, $s0
		move $a1, $s1
		jal RecursiveDivision
		move $s0, $v0
		
		li $v0, 1
		move $a0, $s0
		syscall
		jal space
		j div_menu
	exit_div_menu:
	
	
	
	# Exit Program
	li $v0, 10
	syscall
	# End of "main"...


#---------------------------------------------------------------------------------------------
# Sub Classes
space:
	li $v0, 4
	la $a0, newLine
	syscall
	jr $ra
	# End of "space" function
	
getInput:
	li $v0, 4
	la $a0, enter_Input
	syscall
	li $v0, 5
	syscall
	jr $ra

	
	
recFactorial: # a0: input, v0: output
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	
	# Base-Case
	beq $a0, 1, factorial_done
	
	# Recursion
	addi $a0, $a0, -1
	jal recFactorial
	
	# After returning
	mul $v0, $a0, $v0
	
	factorial_done:
		lw $ra, 0($sp)
		lw $a0, 4($sp)
		addi $sp, $sp, 8
		jr $ra
		
RecursiveDivision: # a0: int to be divided, #a1: divisive, v0: result
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	
	# Base Case
	li $v0, 0
	blt $a0, $a1, division_done
	sub $a0, $a0, $a1
	jal RecursiveDivision
	addi $v0, $v0, 1
	
	division_done:
		lw $ra, 0($sp)
		lw $a0, 4($sp)
		addi $sp, $sp, 8
		jr $ra
	# End of "RecursiveDivision"...
	
	
	
	

 #-------------------------------------------------------------------------------------------
.data
	newLine: .asciiz "\n"
	enter_Input: .asciiz "Enter an integer: "
	
	
	
	
	
	
	
	
	
	
	
	
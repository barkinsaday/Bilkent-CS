###CS224_Section2_Lab01: Part 4
###Barkýn_Saday
###13.10.2021
.data
	array: .space 400 # 100 * 4 = 400-bytes
	newLine: .asciiz "\n"              #new line
	str: .asciiz "\nEnter Value: "
	str2: .asciiz "\nEnter number of elements (max100): "
	bye: .asciiz "\n Bye..."
	msg: .asciiz "\nEnter an operaation (1, 2, 3, 4): "
	msg2: .asciiz "\nChoose a valid operation"
	resMsg: .asciiz "\nResult is: "

.text
main:	
	addi $t0, $zero, 0 # $t0 = 0 (will be used as index)
	addi $t1, $zero, 0 # $t1 = 0 (will be used to modify)
	addi $t6, $zero, 0 # $t6 = 0 (will be used as a element counter)
	addi $t7, $zero, 0  # $t7 = 0 (will be used as byte-size) 4 * $t6
	
	li $v0, 4
	la $a0, str2
	syscall #prints: "Enter Value:"
	
	li $v0, 5
	syscall
	move $t6, $v0 # $t6 = array size (no of elements)
	
	mul $t7, $t6, 4 #$ t7 = array size (bytes)
	
	initArray:
		beq $t0, $t7, exit #exit when array is initialized
		jal pEnter
		
		addi $t0 $t0, 4
		j initArray #looping
		
	exit:
		# contine...
	
	
	#Menu Code ==============================================================================================================================
	menu:
		addi $t0, $zero, 0 # reset t0 (index number)
		addi $t1, $zero, 0 # reset t1 (modeifier)
		addi $s0, $zero, 0 # reset s0 (operation number)
		addi $s1, $zero, 0 # reset s1 (result)
		addi $s0, $zero, 0 # reset s2 (result 2)
		addi $s7, $zero, 0 # reset t1 (new input)
	
		li $v0, 4
		la $a0, msg
		syscall
		
		li $v0, 5
		syscall
		move $s0, $v0 # $s0 = operation
		
		beq $s0, 1, op1 #find sum of number greater than an input
		beq $s0, 2, op2 #find sum of even and odd numbers
		beq $s0, 3, op3 #display numbere of elements divisible by a certain input number
		beq $s0, 4, exitMenu #exit menu
		
		else:
			li $v0, 4
			la $a0, msg2
			syscall # print: invalid operation
			j menu
		
		op1: # Op1--------------------------------------------------------------------------------------------------------------------------------------------
			li $v0, 4
			la $a0, str
			syscall # Print "Enter Value: "
			
			li $v0, 5
			syscall
			move $s7, $v0 # s7 is the input for operation 1
			
			
			myWhile:
				beq $t0, $t7, exitWhile #iterated all elements: exit
				lw $t1, array($t0)
				
				addi $t0, $t0, 4 # t0 + 4
				bgt $t1, $s7, ifGreater
				
				j myWhile #loop
				
				ifGreater:
					add $s1, $s1, $t1 # add to sum if greater
					j myWhile

			exitWhile:
				li $v0, 4
				la $a0, resMsg
				syscall # Print "result is: "
				
				li $v0, 1
				move $a0, $s1
				syscall #prints sum
				j menu # go back to menu
			# End Op: 1--------------------------------------------------------------------------------------------------------------------------------------------
			
		op2: # Op: 2--------------------------------------------------------------------------------------------------------------------------------------------
			myWhile2:
				beq $t0, $t7, exit_myWhile2
				lw $t1, array($t0)
				addi $s0, $zero, 2 # s0 = 2
				div $t1, $s0 #hi is remainder
				mfhi $s0 # s0 = remainder
				beqz $s0, even
			
				odd: #if not even than it is odd
					add $s1, $s1, $t1 # s1 = sum of odd
				
				even:
					add $s2, $s2, $t1 # s2 = sum of all
				addi $t0, $t0, 4 # t0 + 4
				j myWhile2
			exit_myWhile2:
				li $v0, 1
				move $a0, $s1
				syscall #print sum of odd
				
				jal line # new line
				
				li $v0, 1
				sub $s2, $s2, $s1 #all - odd = even
				move $a0, $s2
				syscall #print sum of even
		j menu
			
		#End of Op: 2--------------------------------------------------------------------------------------------------------------------------------------------
				
		op3:
			li $v0, 4
			la $a0, str
			syscall # print "Enter a value: "
			
			li $v0, 5
			syscall
			move $s7, $v0 # s7 is the input for operation 3
			
			myWhile3:
				beq $t0, $t7, exit_myWhile3
				lw $t1, array($t0)
				addi $t0, $t0, 4 # t0 + 4
				div $t1, $s7 # hi = remainder
				mfhi $s0 # s0 = reaminder
				beqz $s0, divisable # if s0 = 0 branch
				
				j myWhile3
				
				
				divisable:
					addi $s1, $s1, 1 # s1++
					j myWhile3
					
			exit_myWhile3:
				jal line #new line
				
				li $v0, 1
				move $a0, $s1
				syscall
				
				j menu
			
	
	exitMenu:
		#continue
	#End of Menu code =======================================================================================================================================

	li $v0, 4
	la $a0, bye
	syscall #prints: bye...
	
	#Exit Program
	li $v0, 10
	syscall
#end of "main" function

	
		
			
				
											
line:
	li $v0, 4
	la $a0, newLine
	syscall
	jr $ra
pEnter:
	li $v0, 4
	la $a0, str
	syscall
	
	li $v0, 5
	syscall
	sw $v0, array($t0)
	jr $ra
#End of Program
	
	
	

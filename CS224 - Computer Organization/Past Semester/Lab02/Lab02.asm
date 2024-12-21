###---CS224: Lab02---
###---Barkýn_Saday---
###---18.10.2021---
.data
	array: .space 4 # 1 byte allocated # ALSO WORKS ÝF ÝT ÝS 4 BYTES BUT STRÝNG MAY GET CORRUPTED
	
	sizeStr: .asciiz "Enter the size of the array: "
	newLine: .asciiz "\n"
	contentStr: .asciiz "\nEnter array contents: "
	gap: .asciiz "\n===============================================================================\n"
.text
main:	
	 # point to address of array
	
	li $v0, 4
	la $a0, sizeStr
	syscall

	li $v0, 5
	syscall # Read integer
	move $s7, $v0 # s7 = array size (number of elements not bit)
	mul $s6, $s7, 4 # s6= array size (as bits), also can be thought as index
	
	li $v0, 9  #allocate memory 
	move $a0, $s6 # memory for the array
	syscall

	la $s0, array
	sw $v0, 0($s0)
	
	jal monitor
	
	move $t2, $v0 # t2: max value
	move $t1, $v1# t1: median value
	
	printerWhile:
		beq $t0, $s6, exit_printerWhile
		
		li $v0, 4
		la $a0, newLine
		syscall # Print empty line
		
		li $v0, 1
		lw $a0, array($t0)
		syscall
		
		addi $t0, $t0, 4
		j printerWhile
		
	exit_printerWhile:
		# contiune...
	li $v0, 4
	la $a0, gap
	syscall
	
	li $v0, 1
	move $a0, $t1
	syscall
	
	li $v0, 4
	la $a0, gap
	syscall
	
	li $v0, 1
	move $a0, $t2
	syscall
	
	
	
	# Exit Program
	li $v0, 10
	syscall
	# End of "main"
	
	
	
# Sub functions:	
monitor:
	# s1 will be modified so we need to store them
	addi $sp, $sp, -8 #a alloate 8-bits
	sw $s1, 0($sp) # to store back s0
	sw $ra, 4($sp)
	
	myWhile:
		beq $s1, $s6, exit # s1 is counter
		
		li $v0, 4
		la $a0, contentStr
		syscall
		
		li $v0, 5 # read integer
		syscall
		sw $v0, array($s1)
		addi $s1, $s1, 4 # s1 + 4
		
		j myWhile # loop
	exit:
		
	jal bubbleSort
	jal medianMax
	lw $ra, 4($sp)
	lw $s1, 0($sp)
	addi $sp, $sp, 8
	jr $ra
	# End of "monitor"

bubbleSort:
	# s1, s2, s3, s4, s5, s0 will be modifed to we need to store them
	addi $sp, $sp, -24
	sw $s1, 0($sp)
	sw $s2, 4($sp)
	sw $s3, 8($sp)
	sw $s4, 12($sp)
	sw $s5, 16($sp)
	sw $s0, 20($sp)
	
	li $s0, 0
	
	sortLoop:
		loop1:
			li $s1, 4
			li $s2, 0
			loop2:
				beq $s1, $s6, exit_loop2# exit loop2 when we reach the end of the array
				
				lw $s3, array($s1)
				lw $s4, array($s2)
				bgt $s4, $s3, swap # swap numbers if previous number is greater
				
				addi $s1, $s1, 4 # s1 + 4
				addi $s2, $s1, -4 # s2 = s1 - 4
				j loop2
					swap:
						add $s5, $zero, $s3 # s5 = s3 temp. (not to lose value of s3)
						sw $s4, array($s1) # s4 is stored in next index
						sw $s3 array($s2) # s3 is moved to lower index
						j loop2
						
			exit_loop2:
				beq $s0, $s6, exit_sortLoop
				addi $s0, $s0, 4
				j loop1
		exit_loop1:	
	exit_sortLoop:
	lw $s0, 20($sp)
	lw $s5, 16($sp)
	lw $s4, 12($sp)
	lw $s3, 8($sp)
	lw $s2, 4($sp)
	lw $s1, 0($sp)
	addi $sp, $sp, 24
	jr $ra
	# End of "bubbleSort"
medianMax:
	addi $sp, $sp, -8
	sw $s0, 0($sp)
	sw $s7, 4($sp)
		
	getMax:
		addi $s0, $s6, -4
		lw $v0, array($s0)
				
	getMedian:
		div $s7, $s7, 2 # to check no of elemenets in array (odd or even) 
		mfhi $s7
		beqz $s7, even
		
		odd:
			addi $s0, $s6, -4 # last index
			div $s0, $s0, 2 # s0 = median index
			lw $v1, array($s0) # v1 = median
			j exit_getMedian
		
		even:
			addi $s0, $s6, -4 #last index
			div $s0, $s0, 2 # middle of two middle indexes
			addi $s0, $s0, 2 # right-mid
			addi $s1, $s0, -4 # left-mid index 
			lw $v1, array($s0) # right value (v1)
			lw $s0, array($s1) # left value (s0)
			add $v1, $v1, $s0 # v1 = v1 + s0
			div $v1, $v1, 2 # v1 = median
	exit_getMedian:	
		lw $s7, 4($sp)
		lw $s0, 0($sp)
		addi $sp, $sp, 8
		jr $ra
	

# End of Program...
# Note to self: If needed implement a getSize method like the one in "Lab02_Preliminary_Part2"
# Also, if needed put the whole "main" function in a loop (or monitor) to make a menu and link all sub function to "monitor" (by calling them from monitor and saving $ra registers)
	

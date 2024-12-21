####---Lab03_Preliminary---
####---Barkýn_Saday---
####---1.11.2021---
.data
	enterSize: .asciiz "\nEnter size: "
	enterValue: .asciiz "\nEnter a value: "
	coma: .asciiz ", "
	bye: .asciiz "bye...\n"
.text
main:
	jal generateLinkedList # v0 returns head node, v1 returns list size
	move $t0, $v0 # t0 stores head of linked list
	move $s0, $v0
	move $t1, $v1 # t1 stores size of the list
	
	li $t2, 0 # t2: counter
	#li $t3, 8 # to get the next data
	# Printing:
	printer:
		beq $t1, $t2, exit_printer
		addi $t2, $t2, 1
		
		li $v0, 1
		lw $a0, 4($t0)
		syscall
		
		li $v0, 4
		la $a0, coma
		syscall
		
		addi $t0, $t0, 8
		j printer
	exit_printer:
		li $v0, 4
		la $a0, bye
		syscall
	
	move $a0, $s0
	move $a1, $v1
	jal sortList # ipnut a0: takes head of the list, input a1: takes list size
	
	li $v0, 10
	syscall
	# Exit program
	#End of "main"========================================================================================================================================





generateLinkedList: 
# $v0: returns header
	
	addi	$sp, $sp, -24
	sw	$s0, 20($sp) # s0: list size
	sw	$s1, 16($sp) # s1: counter
	sw	$s2, 12($sp) # s2: list head
	sw	$s3, 8($sp) # s3: pointer to current/next (keep changing)
	sw	$s4, 4($sp) # s4: data to be stored (read from user each time)
	sw	$ra, 0($sp) # return adress saved just in case
	
	li $s1,  1 # counter = 1
	
	li $v0, 4
	la $a0, enterSize
	syscall
	
	li $v0, 5
	syscall
	move $s0, $v0 # s0: contains list size	
	
	li $v0, 9
	li $a0, 8 # allocate 8 byte 4-bytes for the data, 4-bytes for the next adress
	syscall
	
	move $s2, $v0 # s2: contains the adress of first node (header)
	move $s3, $v0 # s3: point to current/next node (currently it is header)
	
	li $v0, 4
	la $a0, enterValue
	syscall
	li $v0, 5
	syscall
	move $s4, $v0 # s4: contains data to be stored
	
	sw $s4, 4($s3) # data is stored
	
	# Using a loop for adding new nodes and storing data
	loop_addNode:
		beq $s0, $s1, exit_addNode # exit if size is reached
		addi $s1, $s1, 1 # s1++ (increament counter)
		
		li $v0, 9
		li $a0, 8
		syscall # allocate memory for next node (creating the node)
		
		sw $v0, 0($s3) # new node is linked to previous node
		move $s3, $v0, # s3 point to new node
		
		li $v0, 4
		la $a0, enterValue
		syscall
		li $v0, 5
		syscall
		move $s4, $v0 # s4: contains data to be stored
		
		sw $s4, 4($s3) # stored data
		
		j loop_addNode # loop
		
	exit_addNode:
		sw $zero, 0($s3) # last nodes links to 0
		move $v0, $s2 # v0 returns header
		move $v1, $s0 # v1 returns list size
	
	# Restore ra and s registers
	lw	$ra, 0($sp)
	lw	$s4, 4($sp)
	lw	$s3, 8($sp)
	lw	$s2, 12($sp)
	lw	$s1, 16($sp)
	lw	$s0, 20($sp)
	addi	$sp, $sp, 24
	
	jr	$ra # retrun
	# End of "generateLinkedList" ========================================================================================================================================
	
sortList:
	# Save registers
	addi $sp, $sp, -32
	sw $s0, 32($sp)
	sw $s1, 28($sp)
	sw $s2, 24($sp)
	sw $s3, 20($sp)
	sw $s4, 16($sp)
	sw $s5, 12($sp)
	sw $s6, 8($sp)
	sw $s7, 4($sp)
	sw $ra, 0($sp)
	
	
	move $s0, $a1 # s0: list size
	li $s1, 1 # s1: counter
	move $s2, $a0 # s2: head of original list
	move $s3, $a0 # s3: pointer of original list
	
	lw $s7, 4($s2)
	
	li $v0, 9
	li $a0, 8
	syscall 
	move $s4, $v0 # s4: new_Header
	move $s5, $v0 # s5: new_Pointer
	
	sw $s7, 4($s5) # store data in new list
	
	loop_duplicate:
		beq $s0, $s1, exit_duplicate # exit when all list is duplicated
		addi $s1, $s1, 1 # counter++
		
		li $v0, 9
		li $a0, 8
		syscall 
		
		sw $v0, 0($s5) # new node is linked to previous node
		move $s5, $v0, # s5 point to new node
		
		addi $s3, $s3, 8 # 8-bytes after the current location is the next data
		lw $s7, 4($s3)
		sw $s7, 4($s5)
		
		j loop_duplicate # loop it
		
	exit_duplicate:
		sw $zero, 0($s5) # last nodes links to 0
	li $s1, 1
	# s0: size of list
	# s1: counter
	# s2: head of original list(not needed)
	# s4: head of duplicate list
	# s3, s5, s6, s7: trash
	move $t7, $s2
	move $s3, $s5
	lw $s6, 4($t7) # First value (fix)
	lw $s7, 4($t7) # First value (s7 will get next value)
	li $t5, 1
	loop_sort:
		beq $s0, $s1, exit_sort
		addi $s1, $s1, 1
		move $t7, $s2
		loop_FindSmallest:
			beq $s0, $t5, exit_FindSmallest
			addi $t5, $t5, 1
			
			addi $t7, $t7, 8 # Go to next data
			lw $s7, 4($t7)
			
			bgt $s6, $s7, swapToSmaller
			
			j loop_FindSmallest
			swapToSmaller:
				move $t6, $s6
				move $s6, $s7
				move $s7, $t6 # s6 gets the smaller value
			j loop_FindSmallest
		
		exit_FindSmallest: 
			# smallest value is now on s6, we must add it to the head of our new list
			
		addSmallest:
			li $v0, 9
			li $a0, 8
			syscall
			sw $v0, 0($s3) # new node is linked to previous node
			move $s3, $v0, # s3 point to new node
			sw $s6, 4($s3)
			j loop_sort
		
		# get s3 and s5 values from s4+4(+8n), s4+12(+8n) compare them in between swap if needed
		
		
	exit_sort:	
		
		# Restore Registers
		lw $ra, 0($sp)
		lw $s7, 4($sp)
		lw $s6, 8($sp)
		lw $s5, 12($sp)
		lw $s4, 16($sp)
		lw $s3, 20($sp)
		lw $s2, 24($sp)
		lw $s1, 28($sp)
		lw $s0, 32($sp)
		addi $sp, $sp, 32
	jr $ra
# End of program...
	
	
	
	
	
	
	
	
		
	

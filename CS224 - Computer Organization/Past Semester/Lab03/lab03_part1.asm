###---CS224_lab03_part1---
###---Barkýn_Saday---
###---4.11.2021---
.data
	enterSize: .asciiz "\nEnter list size: "
	enterValue: .asciiz "\Enter a value: "
	coma: .asciiz ", "
	bye: .asciiz "bye...\n"
	line: .asciiz "\n==================================================\n"
.text
main:
	jal generateLinkedList
	
	
	move $t0, $v0 # t0 stores head of linked list
	move $t7, $v0
	move $s0, $v0
	move $t1, $v1 # t1 stores size of the list
	
	li $t2, 1# t2: counter
	mulu $t2, $t1, 8
	add $t0, $t0, $t2
	addi $t0, $t0, -8
	li $t2, 0 # t2: counter
	#jal printer
	
	jal DROR
	
	li $v0, 4
	la $a0 line
	syscall
	
	move $t0, $t7
	li $t2, 0
	jal printer
	
	li $v0, 10
	syscall
	# Exit program
	# End of "main"
	
	
	
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
	
	
DROR: # Display Reverse Order Recursive
	addi $sp, $sp, -8
	sw $ra, 0($sp) 
	sw $t0, 4($sp)
	
	beq $t1, $t2, exit_DROR
	addi $t2, $t2, 1
	
	li $v0, 1
	lw $a0, 4($t0)
	syscall
		
	li $v0, 4
	la $a0, coma
	syscall
		
	addi $t0, $t0, -8
	jal DROR	
	
exit_DROR:
	lw $ra, 0($sp)                      
	addi $sp, $sp, 8                  
	jr $ra   	
# End of program...	
	
	
	
	
	

#---CS 224 Lab 6 Preliminary Work---
#---Section: 2---
#---Bark�n Saday---
#---24.04.2022---

.text
main:
	menu:
		#Choose Operation
		li $v0, 4
		la $a0, msgOp
		syscall
		li $v0, 5
		syscall
		move $t0, $v0
		
		beq $t0, 1, op1
		beq $t0, 2, op2
		beq $t0, 3, op3
		beq $t0, 4, op4
		beq $t0, 5, op5
		beq $t0, $zero, exit_menu
		j menu #else (invalid operation)
		
		#Operations
		op1: #Create Matrix (Custom Inputs)
		li $v0, 4
		la $a0, msgEnterSize
		syscall
		li $v0, 5
		syscall
		move $s1, $v0 #s1->matrix size (n)
		mul $s2, $s0, $s0 #s2->number of entries in matrix
		mul $s2, $s2, 4
		jal space
		li $v0, 9
		move $a0, $s2
		move $s0, $v0 #s0-> adress of array (adress of matrix) 
		jal initMatrix
		j menu
		#end of op1
		
		op2: 
		li $v0, 4
		la $a0, msgEnterSize
		syscall
		li $v0, 5
		syscall
		move $s1, $v0 #s1->matrix size (n)
		mul $s2, $s0, $s0 #s2->number of entries in matrix
		mul $s2, $s2, 4
		jal space
		li $v0, 9
		move $a0, $s2
		move $s0, $v0 #s0-> adress of array (adress of matrix)
		jal autoMatrix
		j menu
		#end of op2
		
		op3:
		li $v0, 4
		la $a0, msgEnterIndex
		li $v0, 5
		move $a0, $v0
		li $v0, 5
		move $a1, $v0
		jal displayEntry
		j menu
		#End of op3
		op4:
		li $t0, 0
		move $s3, $s0
		display_loop:
		beq $t0, $s2, exit_display_loop #n*n many times
		li $v0, 1
		lw $a0, ($s3)
		addi $t0, $t0, 1
		addi $s3, $s3, 4
		j display_loop
		exit_display_loop:
		j menu
		#End of op4
		
		op5:
		li $v0, 4
		la $a0, msgRowCol
		syscall
		li $v0, 5
		syscall
		beqz $v0, rowWise
		jal colWiseCopy
		j menu
		rowWise: jal rowWiseCopy
		j menu
		#End of op5
	exit_menu:
	
	#Exit Program...
	li $v0, 10
	syscall
#End of "main"


space:
	li $v0, 4
	la $a0, newLine
	syscall
	jr $ra
#End of "space"

initMatrix:
	li $t0, 0
	move $s3, $s0
	init_loop:
		beq $t0, $s2, exit_init_loop
		li $v0, 4
		la $a0, msgEnterVal
		li $v0, 5
		syscall
		sw $v0, 0($s3)#put the entry in to the matrix
		addi $s3, $s3, 4 #ready for next index (next entry)
		addi $t0, $t0, 1
		j init_loop
	exit_init_loop:
		jr $ra
#End of "initMatrix"

autoMatrix:
	li $t0, 0
	move $s3, $s0
	init_auto_loop:
		beq $t0, $s2, exit_init_auto_loop
		sw $t0, 0($s3)#put the entry in to the matrix
		addi $s3, $s3, 4 #ready for next index (next entry)
		addi $t0, $t0, 1
		j init_auto_loop
	exit_init_auto_loop:
		jr $ra
#End of "autoMatrix"

displayEntry:
	move $t0, $s0
	mul $t0, $a1, $s2 #t0= n*col
	mul $t0, $t0, 4 #t0= col*4*x
	mul $a0, $a0, 4 #row*4
	add $t0, $t0, $a0 #t0 = 4*row + 4*n*col
	add $t0, $t0, $s0 #t0= adrr + 4*row + 4*n*col
	lw $t1, ($t0)
	li $v0, 1
	move $a0, $t0
	syscall
	jr $ra
#End of "displayEntry"

rowWiseCopy: #returns the copy matrix adress in v0
	move $s2, $a0 #a0= n
	mul $a0, $a0, 4 #a0= n*4
	li $v0, 9 #allocate new memory for the copy matrix
	syscall
	move $a0, $v0
	move $a1, $a0
	li $t0, 0
	move $s3, $s0
	row_copy_loop:
		beq $t0, $s2, exit_row_copy_loop
		lw $t1, ($s3)
		sw $t1, ($a1)
		addi $t0, $t0 1
		addi $s3, $s3, 4
		addi $a1, $a1, 4
		j row_copy_loop
	exit_row_copy_loop:
	move $v0, $a0
	jr $ra
#End of "rowWiseCopy"

colWiseCopy:
	addi $sp $sp, -4
	sw $ra, 0($sp)
	
	jal rowWiseCopy #v0: reeturns row wise copy
	move $a0, $v0 #a0 is the input parameter for "matrixTranspose" function
	jal matrixTranpose
	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
#End of "colWiseCopy"

matrixTranpose:
	li $t1, 0
	li $t2, 0
	move $t0, $s0
	transpose_loop:
		beq $t1, $s2, exit_transpose_loop
		mul $t2, $s1, $t1 #t2=n*i (i is the current index)
		add $t0, $t0, $t2
		lw $t3, ($a0)
		sw $t3, ($t0)
		add $a0, $a0, 4
		add $t1, $t1, 4
		j transpose_loop
	exit_transpose_loop:
	jr $ra
#End of "matrixTranspose"


.data
newLine: .asciiz "-----------------------------------------------------------\n"
msgEnterSize: .asciiz "Enter the size of matrix (nxn): "
msgEnterVal: .asciiz "Enter a matrix entry: "
msgOp: .asciiz "Enter an operation (1: create matrix, 2: create automatic, 3: display element, 4: display matrix, 5: comp, 0: exit): "
msgEnterIndex: .asciiz "Enter row/column to see the entry: "
msgRowCol: .asciiz "Enter 0 for row wise, enter 1 for col wise copying"
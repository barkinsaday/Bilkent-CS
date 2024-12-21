#---CS 224 Lab 6---
#---Section: 2---
#---Barkýn Saday---
#---24.04.2022---
.text
main: 
	# save return address to the stack
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	# Display intro message
	li $v0, 4 
	la $a0, prompt # Prompt the assignment Task
	syscall
	menu:
		# Call display
		jal display #display menu
		# Ask user to enter option
		li $v0, 4 
		la $a0, msgOption
		syscall
		#user option selection
		li $v0, 5 # v0 read integer
		syscall
		# Call sub programs according to options
		beq $v0, 1, opt1
		beq $v0, 2, opt2
		beq $v0, 3, opt3
		beq $v0, 4, opt4
		beq $v0, 5, opt5
	   	beq $v0, 9, optExit
	   	j loopBack #invalid operation
	    opt1:
	    	li $v0, 4 
 			la $a0, msgN # Message to read N (NxN matrix)
			syscall
			li $v0, 5 # Read N
			syscall
			move $s0, $v0 # Store size in  -> $s0
			mul $s2, $s0, $s0 # Elements in NxN array -> $s2
			# Now allocate the Matrix space in heap
			mul $a0, $s2, 4 # bytes to allocate
			li $v0, 9 # dynamic memory allocation
			syscall # base address -> $v0
			move $s1, $v0 # base address matrix -> $s1
			# call sub program read values from user
			jal fillCustomMatrix
 			j loopBack
 		opt2:
 			li $v0, 4 
 			la $a0, msgN # Message to read N (NxN matrix)
			syscall
			li $v0, 5 # Read N
			syscall
			move $s0, $v0 # Store size in  -> $s0
			mul $s2, $s0, $s0 # Elements in NxN array -> $s2
			# Now allocate the Matrix space in heap
			mul $a0, $s2, 4 # bytes to allocate
			li $v0, 9 # dynamic memory allocation
			syscall # base address -> $v0
			move $s1, $v0 # base address matrix -> $s1
			# call sub program fill matrix with consecutive elements
			jal fillConsecutiveMatrix
 			j loopBack
 		opt3:
 			# takes row and column and displays the element
 			li $v0, 4 # request to read row  ([i], j)
 			la $a0, msgRow
 			syscall 
 			li $v0, 5 # read row i
 			syscall
 			move $t0, $v0 # row -> $t0
 			li $v0, 4 # request to read col (i, [j])
 			la $a0, msgCol
 			syscall 
 			li $v0, 5 # read col j
 			syscall
 			move $t1, $v0 # col -> $t1
 			# calculate the position
 			subi $t0, $t0, 1 # (i - 1) -> $t0
 			mul $t0, $t0, $s0 # (i - 1) * N -> $t0
 			mul $t0, $t0, 4 # (i - 1) * N * 4 -> $t0
 			subi $t1, $t1, 1 # (j - 1) -> $t1
 			mul $t1, $t1, 4 # (j - 1) * 4 -> $t1
 			add $t0, $t0, $t1 # (i - 1) * N * 4 + (j - 1) * 4 -> $t0
 			add $t2, $t0, $s1 # effective address of the position
 			# display result prompt
 			li $v0, 4 
 			la $a0, msgOpt3Res # result
			syscall
			# display the item
 			lw $a0, 0($t2)
 			li $v0, 1
 			syscall
 			j loopBack
 		opt4:
 			# display the matrix row by row
 			jal displayMatrix
 			j loopBack
 		opt5:
 			#Copy Matrix
 			li $v0, 4
 			la $a0 msgCopyType
 			syscall
 			li $v0, 5
 			syscall
 			beq $v0, 1, rowCopyB
 			
 			jal colCopy
 			j loopBack
 			
 			rowCopyB:
 				jal rowCopy
 				j loopBack
 		
	    # loop menu
	    loopBack:
	    	j menu # go back to menu	
	    optExit:
	    #Keep going in "main"
	
	#Exit Program
	li $v0, 10
	syscall

# Finds the trace like summation of the matrix

	
	
# Get Item
# Returns item at the position
# row -> $a0 
# col -> $a0 
# item -> $v0
# WORKING [+]
getItem:
	addi $sp, $sp, -16 # malloc
	sw $ra, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $s0, 12($sp)
	# =================
	move $t0, $a0 # row -> $t0
 	move $t1, $a1 # col -> $t1
 	# calculate the position
 	subi $t0, $t0, 1 # (i - 1) -> $t0
 	mul $t0, $t0, $s0 # (i - 1) * N -> $t0
 	mul $t0, $t0, 4 # (i - 1) * N * 4 -> $t0
 	subi $t1, $t1, 1 # (j - 1) -> $t1
 	mul $t1, $t1, 4 # (j - 1) * 4 -> $t1
 	add $t0, $t0, $t1 # (i - 1) * N * 4 + (j - 1) * 4 -> $t0
 	add $t2, $t0, $s1 # effective address of the position
	# fetch the item
 	lw $v0, 0($t2)
	# =================
	# calloc
	lw $s0, 12($sp)
	lw $s2, 8($sp)
	lw $s1, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 16
	jr $ra # goto
	


# Displays matrix row by row
# WORKING [+]
displayMatrix:
	addi $sp, $sp, -12 # malloc
	sw $ra, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	# =================
	li $v0, 4 # matrix construction
 	la $a0, endl
    syscall 
    li $t0, 2 # use to control end of line (endl)
	sumRowLoop2:
		lw $a0, 0($s1) # current item -> $a0
		li $v0, 1
		syscall # print current element
		li $v0, 4 # matrix construction
     	la $a0, wSpace
        syscall 
		addi $s1, $s1, 4 # iterate matrix
		subi $s2, $s2, 1
		ble $t0, $s0, jEnter
		li $t0, 1 # use to control end of line (endl)
		li $v0, 4 # matrix construction
     	la $a0, endl
        syscall 
		jEnter:
		addi $t0, $t0, 1 
		bgt $s2, $0, sumRowLoop2
	# calloc
	lw $s2, 8($sp)
	lw $s1, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra # goto

# Obtains col by col summations of elements within the matrix
# Column-major representation
# WORKING [+]




	
# Fills the matrix with consecutive integers
# WORKING [+]
fillConsecutiveMatrix:	
	addi $sp, $sp, -12 # matrix base and return address saved
	sw $ra, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	# start filling from 1
	li $t1, 1 # item value -> $t1
	writeItems:
		sw $t1, 0($s1) # write to the array
		addi $s1, $s1, 4 # next item of the matrix
		addi $t1, $t1, 1 # increment element
		sle  $t3, $t1, $s2
		beq $t3, 1, writeItems
	lw $s2, 8($sp)
	lw $s1, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra # goto

# Fills the matrix with user defined values
# WORKING [+]
fillCustomMatrix:
	addi $sp, $sp, -12 # matrix base and return address saved
	sw $ra, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	# start filling from 1
	li $t1, 1 # iterator -> $t1
	writeItems2:
		# read items from the user
		li $v0, 5
		syscall
		move $t0, $v0 # user input -> $t0 
		sw $t0, 0($s1) # write to the array
		addi $s1, $s1, 4 # next item of the matrix
		addi $t1, $t1, 1 # increment element
		ble $t1, $s2, writeItems2
	lw $s2, 8($sp)
	lw $s1, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra # goto
	
# Menu display interface
# WORKING [+]
display:
	addi $sp, $sp, -4 # allocate stack space
	sw $ra, 0($sp)
	li $v0, 4 
	# print the options
	la $a0, msgMenu
	syscall
	la $a0, msgOpt1 
	syscall
	la $a0, msgOpt2
	syscall
	la $a0, msgOpt3
	syscall
	la $a0, msgOpt4
	syscall
	la $a0, msgOpt5
	syscall
	la $a0, msgExitOpt
	syscall 
	lw $ra, 0($sp) # goto return address
	addi $sp, $sp, 4
	jr $ra # goto
	
# Store size in  -> $s0
# base address matrix -> $s1
# Number of elements in NxN array -> $s2
# v0-> returns adr of new matrix
rowCopy:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	#Allocate memory
	li $v0, 9
	mul $a0, $s2, 4
	syscall
	# v0->holds the beggining adress of the new matrix
	move $s3, $s1 #s3-> index for original adr
	move $v1, $v0 #v1-> holds index for new adr
	li $s4, 0
	row_copy_loop:
		beq $s4, $s2, exit_row_copy_loop
		lw $t0, 0($s3)
		sw $t0, 0($v1)
		addi $s3, $s3, 4
		addi $v1, $v1, 4
		addi $s4, $s4, 1
		j row_copy_loop
	exit_row_copy_loop:
	#...
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
# Store size in  -> $s0
# base address matrix -> $s1
# Number of elements in NxN array -> $s2
# v0-> returns adr of new matrix
colCopy:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	li $v0, 4
	la $a0, msgDeneme
	syscall
	
	#Allocate memory
	li $v0, 9
	mul $a0, $s2, 4
	syscall
	# v0->holds the beggining adress of the new matrix
	move $v1, $v0
	move $s7, $v0
	li $t0, 0
	li $s5, 0 #counter to exit big loop
	li $s4, 0
	move $t0, $s0 # n counter
	#addi $t0, $t0, -1
	move $t1, $s1 # adr
	move $t2, $s2 # size
	mul $t4, $s0, 4 # constant 4n
	
	
	col_copy_loop:
		beq $s5, $s2, exit_col_copy_loop #outer loop
		bne $s4, $t0, here
		#reset s4
		li $s4, 0
		# copy adr+4 for next col 
		addi $s7, $s7, 4
		move $v1, $s7
		here:
		
		lw $t5, 0($t1)
		
		mul $a1, $t4 $s4 # 4n * i
		add $v1, $v1, $a1 # v1 = v1 +4n * i
		
		sw $t5, 0($v1)
		
		addi $t1, $t1, 4
		addi $s4, $s4, 1
		addi $s5, $s5, 1
		j col_copy_loop
	exit_col_copy_loop:
	#...
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra


.data 
prompt:		.asciiz	 "Interactive menu to perform operations on an user defined matrix \n"
msgOption:	.asciiz   "\n Please choose an option: "
msgMenu: .asciiz "\n =========== MENU =============="
msgOpt1: .asciiz	"\n  1. Create matrix (NxN) with user values"
msgOpt2: .asciiz	"\n  2. Create matrix (NxN) with consecutive values"
msgOpt3: .asciiz    "\n  3. Display the desired entry (row, col)"
msgOpt4: .asciiz    "\n  4. Display matrix (Row by row)"
msgOpt5: .asciiz    "\n  5. Copy Matrix"
msgExitOpt: .asciiz "\n  9. Exit"
msgN: .asciiz "\n Please enter N of (NxN) matrix: " 
msgRow: .asciiz "\n Please enter Row number i [1:N]: " 
msgCol: .asciiz "\n Please enter Column number j [1:N]: " 
msgOpt3Res: .asciiz "\n Item in the given row & col: " 
msgOpt7Res: .asciiz "\n Sum of elements obtained in terms of Row-Major iteration (row by row): " 
msgOpt8Res: .asciiz "\n Sum of elements obtained in terms of Column-Major iteration (col by col): " 
msgOpt5Res: .asciiz  "\n Trace of the NxN matrix: " 
msgOpt6Res: .asciiz  "\n Trace like summation of the NxN matrix: " 
endl: .asciiz "\n"
wSpace: .asciiz " "
msgCopyType: .asciiz "\n 1) For wor wise, 2) for column wise copy: "
msgDeneme: .asciiz "\n COLCOLCOLCOLCOLCOLCOLCOCLCOCLCOCLC"

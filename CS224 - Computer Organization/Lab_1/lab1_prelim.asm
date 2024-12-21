#Barkýn_Saday
#CS224 Lab 1 Preliminary Work
#21.02.2022
.text
	li $v0, 4
	la $a0, str1
	syscall
	li $v0, 5
	syscall # v0 holds the int read
	
	move $s1, $v0 # s1 holds the size of the array (in terms of number of elements)
	mul $s0, $s1, 4 # s0 hols the size of array (in terms of bits)
	div $s2, $s1, 2 # ignores fractional part
	mul $s2, $s2, 4
	div $s3, $s1, 2
	mfhi $s3 # 1 means odd, 0 means even
	
	# s0: size as bits
	# s1: size as number of elements
	# s2: middle index (first of second half for even numbered arrays)
	# s3: boolean for determinig even/odd
	
	la $t5, yes # By default "Both Halfs Identical" is "yes", after we call "twist" it will either remain same or change to "no"
	
	jal initialize
	jal print
	jal space
	jal twist
	jal space
	jal print
	jal space
	
	li $v0, 4
	la $a0, str3
	syscall
	jal space
	
	li $v0, 4
	move $a0, $t5
	syscall
	
	# Part 2: Arithmetic Expression ( first 3 index of the array is a, b, c respectively (default 0) ) (NOTE: array is twisted)
	jal space
	
	li $t3, 0 
	lw $t0, array($t3) # t0 = a
	
	li $t3, 4
	lw $t1, array($t3 )# t1 = b
	
	li $t3, 8
	lw $t2, array($t3) # t2 = c
	
	sub $t1, $t1, $2 # t1 = b - c
	mul $t0, $t0, $t1 # t0 = a * (b - c)
	addi $t1, $zero, 0 # t1 = 0
	
	bgez $t0, while_positive
	while_negative:
		bgez $t0, exit_arithmetic
		addi $t0, $t0, 16
		j while_negative
	
	while_positive:
		blt $t0, 16, exit_arithmetic
		addi $t0, $t0, -16 # t0 = t0-16
		addi $t1, $t1, 1 # t1++ (in case we need to find the division)
		j while_positive
		
	exit_arithmetic:
		li $v0, 4
		la $a0, result
		syscall
		li $v0, 1
		move $a0, $t0
		syscall
		
	jal space
	li $v0, 4
	la $a0, bye
	syscall
	
	#Exit Program...
	li $v0, 10
	syscall
	#End of main...

# Sub Classes:
initialize:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	
	li $t0, 0
	init:
		bge $t0, $s0, exit_init
		li $v0, 4
		la $a0, str2
		syscall
		li $v0, 5
		syscall # v0 holds the new element
		sw $v0, array($t0) # new element is added to array
		jal space
		addi $t0, $t0, 4 # t0 = t0+4 (go to next index)
		j init
		 
	exit_init:
		# Exit init loop...
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 8
	jr $ra
	
twist:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	
	li $t0, 0 # first half index
	move $t1, $s2 # second half index
	# odd even kullan bunun için yeni reg kullan ( $s3 ) odd'sa bi ilerden baþlat evensa düz baþlat t2'yi sonuna kadar götürüp deðiþtir
	beqz $s3, loop
	addi $t1, $t1, 4 # if odd: start after middle index
	# else skip to loop
	
	loop:
		beq $t1, $s0, exit_loop
		lw $t6, array($t0)
		lw $t7, array($t1)
		
		beq $t6, $t7, equal # Identical Half Check
		la $t5, no # if any pair are not equal than t5 will be "no"
		equal: 
		 
		sw $t6, array($t1)
		sw $t7, array($t0)
		addi $t0, $t0, 4
		addi $t1, $t1, 4
		j loop	
	exit_loop:
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 8	 
	jr $ra
	# End of "twist"
	
print:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	
	li $t0, 0
	print_while:
		beq $t0, $s0, exit_print
		li $v0, 1
		lw $a0, array($t0)
		syscall
		jal space
		addi $t0, $t0, 4
		j print_while
		
	exit_print:
		lw $s0, 4($sp)
		lw $ra, 0($sp)
		jr $ra
	# End of "print"

space:
	la $a0, gap
	li $v0, 4
	syscall
	jr $ra
	# End of "space"

.data
array: .space 80
gap: .asciiz "\n"
str1: .asciiz "Enter the size of the array: "
str2: .asciiz "Enter value: "
str3: .asciiz "Both Half Identical: "
yes: .asciiz "Yes"
no: .asciiz "No"
result: .asciiz "Result: "
bye: .asciiz "Bye..."

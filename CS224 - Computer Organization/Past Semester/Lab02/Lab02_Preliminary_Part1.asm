###---Lab02_Preliminiary: Part_1 Octal to Decimal---
###---Barkýn_Saday---
###---14.10.2021---
###1---19.10.2021 (Last Update)---
.data
	input: .space 100 
	newLine: .asciiz "\n"
	str: .asciiz "\nEnter the input size (bits): \n"
	bye: .asciiz "\n Bye..."
	notOctal_str: .asciiz "\nThe value is not an octal number.\n"
.text
	li $v0, 4
	la $a0, str
	syscall
	
	li $v0, 5
	syscall 
	move $t7, $v0
	addi $t7, $t7, -1
	
	li $v0, 8
	la $a0, input
	li $a1, 100
	syscall
	
	move $s0, $t7
	li $t2, 1
	
	while: # turn into int and store it in s1
		lbu $t0, input($s0)
		addi $t0, $t0, -48
		
		bge $t0, 8, notOctal
		
		mul $t1, $t0, $t2 # t1: temp value to be added to s1, t2: basamak için
		add $s1, $s1, $t1
		
		beq $s0, 0, exit
		addi $s0, $s0, -1
		mul $t2, $t2, 8 # converting to octal
		j while
		
		notOctal:
			li $v0, 4
			la $a0, notOctal_str
			syscall
			li $s1, -1 # if not octal int value is "-1"
			
	exit:
		jal line
		li $v0, 1
		move $a0, $s1
		syscall
	# s1: contains the octal represtation
	li $v0, 4
	la $a0, bye
	syscall # print: "bye"
	
	
	#Exit Program
	li $v0, 10
	syscall

line:
	li $v0, 4
	la $a0, newLine
	syscall
	jr $ra
#End of Program	


	
	
	
	
	
	

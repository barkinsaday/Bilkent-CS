###---CS224_Lab01_Preliminary_Work: Create Array and Reverse---
###---Barkýn_Saday---
###---13.10.2021---
.data
	array: .space 80 # 20 * 4 = 80-bytes at max
	#revAr: .space 80
	line: .asciiz "\n"              #new line
	str: .asciiz "\nEnter Value: \n"
	str2: .asciiz "\nEnter number of elements (max20): "
	bye: .asciiz "\n Bye..."
	no: .asciiz "\nNot Palindrome"
	yes: .asciiz "\nIt is Palindrome"

.text
main:	
	li $v0, 4
	la $a0, str2
	syscall #Prints str2
	
	li $v0, 5 #input stored in v0
	syscall
	addi $t7, $zero, 0 #$t7 = 0 (initialize it)
	move $t7, $v0 #input moved to $t7 (number of elements)
	
	addi $t0, $zero, 0 #$t0 = 0 (used as the first index of the array)
	mul $t7, $t7, 4 #Number of elements * 4-bytes
	addi $t1, $t7, 0
	
	while:
		beq $t0, $t7, exit #if all elements entered exit the loop
		
		li $v0, 4
		la $a0, str
		syscall #Print str
		
		li $v0, 5
		syscall #Get user input (int)
		sw $v0, array($t0)
		#sw $v0, revAr($t1)
		
		addi $t0, $t0, 4
		addi $t1, $t1, -4
		j while #stay in loop
		#Array is initialized
	exit:
		#contiune "main" function...
		
	addi $t0, $t0, -4
	reverse:
		beq $t0, -4, exit2 #after 0($t0) printed exit loop
		
		li $v0, 4
		la $a0, line
		syscall #print new line
		
		li $v0, 1
		lw $a0, array($t0)
		syscall #Print reverse array
		
		addi $t0, $t0, -4
		j reverse #stay in loop
		#Array is printed reverse	
	exit2:
		#continue "main" function...
		
	addi $t0, $zero, 0 #t0 = 0
	addi $t1, $t7, -4 # t1 = index of last element of the array
	
	compare:
		lw $t2, array($t0)
		lw $t3, array($t1)
		bne $t2, $t3, noPal #not palindrome
		addi $t0, $t0, 4
  		addi $t1, $t1, -4 # go to next elements (one straight one reverse)
  		ble $t0, $t1, compare #if there is still elements in between and still didnt exit from "noPal "keep comparing
  	j yesPal
  		
	noPal:
		li $v0, 4
		la $a0, no
		syscall
		j exitProg
	yesPal:
		li $v0, 4
		la $a0, yes
		syscall
		j exitProg
		
		
	exitProg:
		li $v0, 4
		la $a0, bye
		syscall#Prints "Bye..."
	#Exit Program
	li $v0, 10
	syscall
	#End of "main" function
###End of Program
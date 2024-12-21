###CS224_Section2_Lab01: Part 3
###Barkýn_Saday
###13.10.2021
.data
	str: .asciiz "\nEnter number: "
	newLine: .asciiz "\n"
	

.text
main:
	jal pEnter
	li $v0, 5
	syscall # $v0 = b
	move $t0, $v0 # $t0 = a
	
	jal pEnter
	li $v0, 5
	syscall # $v0 = b
	move $t1, $v0 # $t1 = b
	
	jal pEnter
	li $v0, 5
	syscall # $v0 = c
	move $t2, $v0 # $t2 = c
	
	#a / b
	div $s0, $t0, $t1 # s0 = a / b
	#mflo $s0 # $s0 = a / b

	# c - b
	sub $s1, $t2, $t1 # $s1 = c - b
		
	#$s0 % $s2
	rem $t7, $s0, $s1
	#hi is the result
	
	jal line #new line
	
	li $v0, 1
	move $a0, $t7
	syscall 

	#Exit Program
	li $v0, 10
	syscall
	#End of "main" function	
													
pEnter:
	li $v0, 4
	la $a0, str
	syscall
	jr $ra														
																												
line:
	li $v0, 4
	la $a0, newLine
	syscall
	jr $ra	
#End of Program...

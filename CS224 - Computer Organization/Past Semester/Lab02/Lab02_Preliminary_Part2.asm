###---Lab2 Preliminary Part 2: Switch Nibbles---
###---Barkýn_Saday---
###---19.10.2021---
.data
	str: .space 400
	newLine: .asciiz "\n===========================================================================================================\n"
	
.text
main:
	li $v0, 8
	la $a0, str
	li $a1, 100
	syscall
	
	la $s7, str
	
	move $a0, $s7 # a0 gets adress of str to be used in "getSize" function
	jal getSize # v0 is return result (elements * 4 )
	move $s6, $v0 # s6: got the size
		
	li $v0, 4
	la $a0, str
	syscall # print str before switching
	
	li $v0, 4
	la $a0, newLine
	syscall # print new line
	
	jal switchNibbles	
	li $v0, 4
	la $a0, str
	syscall # print str after switching
		
	
	# Exit Program
	li $v0, 10#######Delete this later
	syscall
	# End of "main"
	
# Sub Programs ################################################
# No:1
switchNibbles:
	addi $sp, $sp, -16
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s3, 8($sp)
	sw $s4, 12($sp)
	
	li $s0, 0
	li $s1, 1
	
	switch:
		beq $s0, $s6, exit_switch
		lbu $s3, str($s0)
		lbu $s4, str($s1)
	
		sb $s3, str($s1)
		sb $s4, str($s0)
	
		addi $s0, $s0, 2 # 0, 2, 4, 6, 8...
		addi $s1, $s1, 2 # 1, 3, 5, 7, 9...
	
		j switch
	exit_switch:
		lw $s4, 12($sp)
		lw $s3, 8($sp)
		lw $s1, 4($sp)
		lw $s0, 0($sp)
		addi $sp, $sp, 16
		# End of "switchNibbles"

# No: 2
getSize: # a0: to store addres, v0: returns size (bits)
	li $v0, 0
	#save s registers here
	addi $sp, $sp, -4
	sw $s0, 0($sp)
	loop:
		lb $s0, 0($a0)
		beqz $s0, exit_loop
		addi $a0, $a0, 1
		addi $v0, $v0, 4
		j loop
	exit_loop:
		lw $s0, 0($sp)
		addi $sp, $sp, 4
		jr $ra
		# End of "getSize"
# End of Program...

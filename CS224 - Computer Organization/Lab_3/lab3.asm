# CS 224
# Section: 2
# Lab: 3
# Barkýn Saday
# 21902967
# 16.03.2022
.text
	# Create List with 10 elements (1, 2, 3, ... 10)
	li $a0, 10
	jal createLinkedList
	move	$a0, $v0	# Pass the linked list address in $a0
	
	# Print List
	move $s0, $a0 # s0: also contains head
	jal 	printLinkedList
	move $a0, $s0 # Restore head to a0
	
	# Print Reverse List (Recursively)
	jal DROR
	
	li $a1, 10
	jal DuplicateListIterative
	move $s1, $v0 # s1: contains duplicate head
	
	move $a0, $s1
	jal 	printLinkedList
	
	
	

	# Exit program...
	li	$v0, 10
	syscall
	# End of main

# ---------------------------------------------------------------------------------------------------------------------------
# Sub Classes :
# Displat Reverse Ored Recursively (DROR)
DROR: #a0: node head, #a1: number of nodes, v0: returns head
	addi $sp, $sp, -20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $a0, 16($sp)
	
	# Base Case
	beq $s2, 10, DROR_done
	addi $s2, $s2, 1
	addi $a0, $a0, 8
	jal DROR
	# print here
	move $s1, $a0 # save a0 for now
	lw $s0, -4($a0)
	li $v0, 4
	la $a0, newLine
	syscall
	li $v0, 1
	move $a0, $s0
	syscall
	
	move $a0, $s1 # restore a0
	
	DROR_done:
	lw $a0, 16($sp)
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 20
	jr $ra
	# End of "DROR"
DuplicateListIterative: #a0: original head, a1: original size, v0: returns new head
	addi	$sp, $sp, -28
	sw 	$s5, 24($sp)
	sw	$s0, 20($sp)
	sw	$s1, 16($sp)
	sw	$s2, 12($sp)
	sw	$s3, 8($sp)
	sw	$s4, 4($sp)
	sw	$ra, 0($sp) 
	move $s0, $a0 # s0: contains original head
	move $s5, $a0 # s5: also contains original head, will change
	li $s1, 1 # start from 1 since first node is created out of the loop 
	
	# Create new head
	li $a0, 8
	li $v0, 9
	syscall # allocate new memory from heap, v0 currently holds the head of new list
	move $s2, $v0 # s2: contains new head, but it will change
	move $s3, $v0 # s3: also contains new head, it will remain still
	# Copy head data from original list to new list
	lw $s4, 4($s0)
	sw $s4, 4($s2)
	
	while_duplicate:
		beq $s1, $a1, duplicate_done
		addi $s1, $s1, 1
		addi $s5, $s5, 8
		li $a0, 8
		li $v0, 9
		syscall
		# Connect the nodes
		sw $v0, 0($s2) # connected
		move $s2, $v0, # s2: now point to new node
		# Copy Data
		lw $s4, 4($s5)
		sw $s4, 4($s2)
		j while_duplicate
	
	duplicate_done:	
		move $v0, $s3 # v0: returns head of new list
		
		lw $s5, 24($sp)
		lw $s4, 20($sp)
		lw $s3, 16($sp)
		lw $s2, 12($sp)
		lw $s1, 8($sp)
		lw $s0, 4($sp)
		lw $ra, 0($sp)
		addi $sp, $sp, 28
		jr $ra
		# End of "DuplicateListIterative"
		
DuplicateListRecursive:
	addi $sp, $sp, -20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $a0, 16($sp)
	
	# Base Case
	beq $s2, 10, m3_done
	addi $s2, $s2, 1
	addi $a0, $a0, 8
	jal DuplicateListRecursive
	jal DuplicateListIterative
	
	m3_done:
	lw $a0, 16($sp)
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 20
	jr $ra
	# End of "DuplicateListRecursive"...
	


# Creating Linked List is done with the program from Moodle under the Lab3 page
createLinkedList:
# $a0: No. of nodes to be created ($a0 >= 1)
# $v0: returns list head
# Node 1 contains 4 in the data field, node i contains the value 4*i in the data field.
# By 4*i inserting a data value like this
# when we print linked list we can differentiate the node content from the node sequence no (1, 2, ...).
	addi	$sp, $sp, -24
	sw	$s0, 20($sp)
	sw	$s1, 16($sp)
	sw	$s2, 12($sp)
	sw	$s3, 8($sp)
	sw	$s4, 4($sp)
	sw	$ra, 0($sp) 	# Save $ra just in case we may want to call a subprogram
	
	move	$s0, $a0	# $s0: no. of nodes to be created.
	li	$s1, 1		# $s1: Node counter
# Create the first node: header.
# Each node is 8 bytes: link field then data field.
	li	$a0, 8
	li	$v0, 9
	syscall
# OK now we have the list head. Save list head pointer 
	move	$s2, $v0	# $s2 points to the first and last node of the linked list.
	move	$s3, $v0	# $s3 now points to the list head.
	addi $s4, $s4, 1	
# sll: So that node 1 data value will be 4, node i data value will be 4*i
	sw	$s4, 4($s2)	# Store the data value.
	
addNode:
# Are we done?
# No. of nodes created compared with the number of nodes to be created.
	beq	$s1, $s0, allDone
	addi	$s1, $s1, 1	# Increment node counter.
	li	$a0, 8 		# Remember: Node size is 8 bytes.
	li	$v0, 9
	syscall
# Connect the this node to the lst node pointed by $s2.
	sw	$v0, 0($s2)
# Now make $s2 pointing to the newly created node.
	move	$s2, $v0	# $s2 now points to the new node.
	addi $s4, $s4, 1	
# sll: So that node 1 data value will be 4, node i data value will be 4*i
	sw	$s4, 4($s2)	# Store the data value.
	j	addNode
allDone:
# Make sure that the link field of the last node cotains 0.
# The last node is pointed by $s2.
	sw	$zero, 0($s2)
	move	$v0, $s3	# Now $v0 points to the list head ($s3).
	
# Restore the register values
	lw	$ra, 0($sp)
	lw	$s4, 4($sp)
	lw	$s3, 8($sp)
	lw	$s2, 12($sp)
	lw	$s1, 16($sp)
	lw	$s0, 20($sp)
	addi	$sp, $sp, 24
	
	jr	$ra
#=========================================================
printLinkedList:
# Print linked list nodes in the following format
# --------------------------------------
# Node No: xxxx (dec)
# Address of Current Node: xxxx (hex)
# Address of Next Node: xxxx (hex)
# Data Value of Current Node: xxx (dec)
# --------------------------------------

# Save $s registers used
	addi	$sp, $sp, -20
	sw	$s0, 16($sp)
	sw	$s1, 12($sp)
	sw	$s2, 8($sp)
	sw	$s3, 4($sp)
	sw	$ra, 0($sp) 	# Save $ra just in case we may want to call a subprogram

# $a0: points to the linked list.
# $s0: Address of current
# s1: Address of next
# $2: Data of current
# $s3: Node counter: 1, 2, ...
	move $s0, $a0	# $s0: points to the current node.
	li   $s3, 0
printNextNode:
	beq	$s0, $zero, printedAll
				# $s0: Address of current node
	lw	$s1, 0($s0)	# $s1: Address of  next node
	lw	$s2, 4($s0)	# $s2: Data of current node
	addi	$s3, $s3, 1
# $s0: address of current node: print in hex.
# $s1: address of next node: print in hex.
# $s2: data field value of current node: print in decimal.
	la	$a0, line
	li	$v0, 4
	syscall		# Print line seperator
	
	la	$a0, nodeNumberLabel
	li	$v0, 4
	syscall
	
	move	$a0, $s3	# $s3: Node number (position) of current node
	li	$v0, 1
	syscall
	
	la	$a0, addressOfCurrentNodeLabel
	li	$v0, 4
	syscall
	
	move	$a0, $s0	# $s0: Address of current node
	li	$v0, 34
	syscall

	la	$a0, addressOfNextNodeLabel
	li	$v0, 4
	syscall
	move	$a0, $s1	# $s0: Address of next node
	li	$v0, 34
	syscall	
	
	la	$a0, dataValueOfCurrentNode
	li	$v0, 4
	syscall
		
	move	$a0, $s2	# $s2: Data of current node
	li	$v0, 1		
	syscall	

# Now consider next node.
	move	$s0, $s1	# Consider next node.
	j	printNextNode
printedAll:
# Restore the register values
	lw	$ra, 0($sp)
	lw	$s3, 4($sp)
	lw	$s2, 8($sp)
	lw	$s1, 12($sp)
	lw	$s0, 16($sp)
	addi	$sp, $sp, 20
	jr	$ra

	
	
.data
newLine: .asciiz "\n"
line:	
	.asciiz "\n --------------------------------------"

nodeNumberLabel:
	.asciiz	"\n Node No.: "
	
addressOfCurrentNodeLabel:
	.asciiz	"\n Address of Current Node: "
	
addressOfNextNodeLabel:
	.asciiz	"\n Address of Next Node: "
	
dataValueOfCurrentNode:
	.asciiz	"\n Data Value of Current Node: "

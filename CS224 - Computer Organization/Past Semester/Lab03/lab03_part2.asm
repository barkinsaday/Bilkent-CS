###---CS224_lab03---
###---Barkýn_Saday---
###---4.11.2021---
.data
	enterInput: .asciiz "\nEnter number: "
	result: .asciiz "\nResult: "
	bye: .asciiz "\nbye..."
.text
main:	

	loop_menu:
		li $v0, 4
		la $a0, enterInput
		syscall
	
		li $v0, 5
		syscall
		move $t6, $v0 # t6 = input 1
		
		li $v0, 4
		la $a0, enterInput
		syscall
	
		li $v0, 5
		syscall
		move $t7, $v0 # t7 = input 1
		
		beqz $t7, exit_menu
		beqz $t6, exit_menu
		
		
		li $v0, 0
		move $a0, $t6
		move $a1, $t7
		jal RecursiveDivision # a0(input 1), a1( input 2), v0 (output)
		move $s0, $v0
	
		li $v0, 4
		la $a0, result
		syscall
	
		li $v0, 1
		move $a0, $s0
		syscall
		
		j loop_menu
		
	exit_menu:
		li $v0, 4
		la $a0 bye
		syscall

	li $v0, 10
	syscall
	# Exit program
       
        
RecursiveDivision:
	addi $sp, $sp, -8
	sw $ra, 0($sp) 
	sw $a0, 4($sp)	
        
        bgt $a1, $a0, exit_division
        sub $a0, $a0, $a1 # a0 = a0-a1
        addi $v0, $v0, 1 # t0++
        jal RecursiveDivision
        
        
        
exit_division:
	#li $v0, 0                          
	lw $ra, 0($sp)                     
	addi $sp, $sp, 8                 
	jr $ra   
          
            
             
              
               
                
                 
                  
                   
                    
                     
                      
                       
                        
                         
                          
                           
                            
                             
                              
                                

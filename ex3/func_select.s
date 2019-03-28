#Elad Israel 313448888

# set up the jump table 
.section    .rodata
    printLengthMsg:    .string "first pstring length: %d, second pstring length: %d\n"
    replaceCharMsg:    .string "old char: %c, new char: %c, first string: %s, second string: %s\n"
    replaceMultipleCharMsg:    .string "length: %d, string: %s\n"
    swapCaseMsg:   .string "length: %d, string: %s\n"
    compareResultMsg:   .string "compare result: %d\n"
    invalidOptionMsg:  .string "invalid option!\n"
    stringScan:    .string " %c %c"
    intScan:       .string "%d"
    .align 8
.Lswitch:
# jump table
    .quad .L0 # Case 50
    .quad .L1 # Case 51
    .quad .L2 # Case 52
    .quad .L3 # Case 53
    .quad .L4 # Case 54
    .quad .L5 # Default
    
.text # The beginning of the code

.globl func_select
    .type func_select, @function

func_select:
#rdi pointer to first pstring,rsi pointer to second pstring

    pushq %rbp                  # save the old frame pointer
    movq %rsp, %rbp             # create the new frame pointer

    subq $8,%rsp                #save first pstring on stack
    movq %rsi,(%rsp)    
    
    subq $8,%rsp                #save second pstring on stack
    movq %rdx,(%rsp)
    
    
    
    subq $50,%rdi
    cmpq $4,%rdi                # compare input-50 to 4
    ja .L5                      # if input-50 > 4 or < 0 jump to default
    jmp *.Lswitch(,%rdi,8)      #jump to Lswitch + 8*(input-50)
    
    
# Case 50
.L0:
    
    leaq 8(%rsp), %r9           #first pstring pointer
    movq (%r9), %rdi
        
    call    pstrlen             #get Pstring1 length. (pointer to pstr1 in rsi)
        
    subq $1,%rsp                #save length on stack
    movb %al,(%rsp)
        
    leaq 1(%rsp),%r8            #passing the second string to pstrlen
    movq (%r8),%rdi 
        
    call pstrlen                #get Pstring2 length.

    movq $printLengthMsg,%rdi   #place message as first parameter to printf
        
    movq $0,%rsi
    movb (%rsp),%sil            #place first length as second parameter to printf
        
    movq %rax,%rdx              #place second length returned from function as third parameter to printf
        
    movq $0, %rax
    call printf
    movq $0,%rax
        
    jmp .Ldone

    
# Case 51
.L1:
    
    movq $stringScan, %rdi      #first parameter to scanf- the string of inputs
                                       
    subq $1, %rsp
                                      
    movq %rsp, %rsi             #second parameter to scanf- first char place                  
                                        
    subq $1, %rsp
                                      
    movq %rsp, %rdx             #third parameter to scanf- second char place                         
                                        
    movq $0, %rax
    call scanf
    
    leaq 10(%rsp),%r8
    movq (%r8),%rdi             #first string- set as first parameter                 
   
    movq $0,%rdx
    movb (%rsp),%dl             #newChar as second parameter                           
           
    leaq 1(%rsp),%rcx           #old char in rcx
 
    movq $0,%rsi
    movb (%rcx),%sil            #oldChar as third parameter 
    
    call replaceChar

    leaq -8(%rsp),%rsp          #allocate room for changed pstring address returned from function
    movq %rax, (%rsp)           #save return value(changed pstring) in stack
    
    leaq 10(%rsp),%r9           #store the address of rsp+10 (second string address) in r9
    movq (%r9),%rdi                 

    movq $0,%rdx                # store new char in rdx
    leaq 8(%rsp),%rcx
    movb (%rcx),%dl  
    
    movq $0,%rsi                # store old char in rsi
    leaq 9(%rsp),%rcx
    movb (%rcx), %sil 
    
    call replaceChar

    movq %rax,%r8               #second changed string
    addq $1,%r8                 #skip length byte
    
    movq (%rsp),%rcx            #first changed string
    addq $1,%rcx                #skip length byte

    
    movq $0,%rdx                # store new char in rdx
    leaq 8(%rsp),%r9
    movb (%r9),%dl  
    
    movq $0,%rsi                # store old char in rsi
    leaq 9(%rsp),%r9
    movb (%r9), %sil 
    
    movq $replaceCharMsg, %rdi  # store print string as first parameter
   
    movq $0,%rax
    call printf
         
    jmp .Ldone


# Case 52
.L2:
    movq $intScan, %rdi         #first parameter to scanf- the string of inputs
    subq $4,%rsp                #save i on stack
    movq %rsp,%rsi              #scanf will save input in rsi(second parameter) location
    movq $0,%rax
    call scanf
    
    movq $intScan, %rdi         #first parameter to scanf- the string of inputs
    subq $4,%rsp                #save j on stack
    movq %rsp,%rsi
    movq $0,%rax
    call scanf
    
    leaq 16(%rsp), %r9          #second pstring pointer
    movq (%r9), %rdi
    
    leaq 8(%rsp), %r9           #first pstring pointer
    movq (%r9), %rsi
    
    movq $0,%rdx
    leaq 4(%rsp),%r9            #i
    movl (%r9),%edx
    movq $0,%rcx
    movl (%rsp), %ecx           #j
    
    call pstrijcpy
    
    subq $8,%rsp                #new array address
    movq %rax,(%rsp)
        
    movq %rax,%rdi              #get dst length
    call pstrlen
    movq %rax,%rsi              #length
    
    movq (%rsp),%rdx            #new array address
    addq $1,%rdx                #skip length byte

    movq $replaceMultipleCharMsg,%rdi #string to print
    
    movq $0,%rax 
    call printf
    
    leaq 16(%rsp), %r9          #second pstring pointer
    movq (%r9), %rdi
    
    call pstrlen                #length of second pstring
    movq %rax,%rsi
    
    leaq 16(%rsp), %r9          #second pstring pointer
    movq (%r9), %rdx
    addq $1,%rdx                #skip length byte
    
    movq $replaceMultipleCharMsg,%rdi #string to print

    movq $0,%rax
    call printf
    
    jmp .Ldone

# Case 53
.L3:
    leaq 8(%rsp), %r9           #first pstring pointer
    movq (%r9), %rdi
    
    call swapCase               #swap Pstring1
        
        
    subq $8,%rsp                # Pstring1 changed array address
    movq %rax,(%rsp)
    
    movq %rax,%rdi              #get length
    call pstrlen
    movq %rax,%rsi              #length
    
    movq (%rsp),%rdx            #changed array address
    addq $1,%rdx                #skip length byte
    
    movq $swapCaseMsg,%rdi      #string to print
    
    movq $0,%rax 
    call printf
        
        
    leaq 8(%rsp), %r9           #second pstring pointer
    movq (%r9), %rdi
    call swapCase               #swap Pstring2
        
    subq $8,%rsp                #changed array address
    movq %rax,(%rsp)
    
    movq %rax,%rdi              #get length
    call pstrlen
    movq %rax,%rsi              #length
    
    movq (%rsp),%rdx            #changed array address
    
    addq $1,%rdx                #skip length byte
    movq $swapCaseMsg,%rdi      #string to print
    
    movq $0,%rax 
    call printf
        
        
    jmp .Ldone


# Case 54
.L4:
       
    movq $intScan, %rdi         #first parameter to scanf- the string of inputs
    subq $4,%rsp                #save i on stack
    movq %rsp,%rsi              #scanf will save input in rsi(second parameter) location
    movq $0,%rax
    call scanf
    
    movq $intScan, %rdi         #first parameter to scanf- the string of inputs
    subq $4,%rsp                #save j on stack
    movq %rsp,%rsi
    movq $0,%rax
    call scanf
    
    leaq 16(%rsp), %r9          #second pstring pointer
    movq (%r9), %rdi
    
    leaq 8(%rsp), %r9           #first pstring pointer
    movq (%r9), %rsi
    
    movq $0,%rdx
    leaq 4(%rsp),%r9            #i
    movl (%r9),%edx
    movq $0,%rcx
    movl (%rsp), %ecx           #j
    
    call pstrijcmp
    movq %rax,%rsi
    movq $compareResultMsg,%rdi
    
    movq $0,%rax
    call printf
                
    jmp .Ldone


# Default
.L5:
    
    movq $invalidOptionMsg,%rdi #invalid option
    movq $0, %rax
    call printf
    jmp .Ldone
    
.Ldone:
    movq %rbp, %rsp
    popq %rbp
    ret 
    
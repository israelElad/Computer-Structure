#Elad Israel 313448888

.section    .rodata
    stringScan:      .string "%s\0"
    intScan:         .string "%d"

.text
.global main
.type main @function
main:
    movq %rsp, %rbp #for correct debugging

    pushq   %rbp
    movq    %rsp,%rbp
    
    #Get length of first Pstring.
    addq    $-4,%rsp                        #allocate 4 bytes.
    movq    %rsp,%rsi                       #set scanf 2nd parameter.
    movq    $intScan,%rdi                   #set scanf 1st parameter.
    xorq    %rax,%rax
    call    scanf                           #scan length.

    xorq    %rbx,%rbx                       #clear rbx.
    movb    (%rsp),%bl                      #copy length to bl.
    addq    $4,%rsp                         #remove allocation.
    
    #Get string of first Pstring.
    subq    %rbx,%rsp                       #allocate length+1 bytes.
    addq    $-1,%rsp
    movq    %rsp,%rsi                       #set scanf 2nd parameter.
    movq    $stringScan,%rdi                #set scanf 1st parameter.
    xorq    %rax,%rax
    call    scanf                           #scan string.
    
    addq    $-1,%rsp                        #allocate 1 byte.
    movb    %bl,(%rsp)                      #add size to Pstring.
    
    #Get length of second Pstring.
    addq    $-4,%rsp                        #allocate 4 bytes.
    movq    %rsp,%rsi                       #set scanf 2nd parameter.
    movq    $intScan,%rdi                   #set scanf 1st parameter.
    xorq    %rax,%rax
    call    scanf                           #scan the length.

    xorq    %rbx,%rbx                       #clear rbx.
    movb    (%rsp),%bl                      #copy length to bl.
    addq    $4,%rsp                         #remove allocation.
    
    #Get string of second Pstring.
    subq    %rbx,%rsp                       #allocate length+1 bytes.
    addq    $-1,%rsp
    movq    %rsp,%rsi                       #set scanf 2nd parameter.
    movq    $stringScan,%rdi                #set scanf 1st parameter.
    xorq    %rax,%rax
    call    scanf                           #scan the string.
    
    addq    $-1,%rsp                        #allocate 1 byte.
    movb    %bl,(%rsp)                      #add size to Pstring.
    
    #Get user's choice.
    addq    $-4,%rsp                        #allocate 4 bytes.
    movq    %rsp,%rsi                       #set scanf 2nd parameter.
    movq    $intScan,%rdi                   #set scanf 1st parameter.
    xorq    %rax,%rax
    call    scanf                           #scan the choice.
    
    leaq    4(%rsp),%rdx                    #run_func third parameter.
    
    xorq    %rax,%rax                       #clear rax.
    movb    (%rdx),%al                      #copy the size of the second Pstring to al.
    leaq    6(%rsp,%rax),%rsi               #run_func 2nd parameter.
    
    xorq    %rdi,%rdi                       #clear rdi.
    movl    (%rsp),%edi                     #run_func 1st parameter.
    xorq    %rax,%rax
    call    func_select
    
    xorq    %rax,%rax
    movq    %rbp, %rsp
    popq    %rbp
    ret
    
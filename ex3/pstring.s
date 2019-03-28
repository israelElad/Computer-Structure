#Elad Israel 313448888

.section    .rodata
    invalidInputMsg:    .string "invalid input!\n"

.text
.globl pstrlen
    .type pstrlen, @function
pstrlen:
    # pstring in %rdi(starting with length)
    
    xorq  %rax, %rax # clear rax
    movb (%rdi), %al # move first byte of rdi, to rax(al) as return value.
   
    ret 
    
    		          
.global replaceChar
        .type   replaceChar, @function
replaceChar: 
    # pstring in %rdi, old char in %sil(rsi), new char in %dl(rdx)
    xorq  %r8, %r8              # clear r8
    movb (%rdi), %r8b           # r8= length
    movq %rdi, %r10             # r10= pointer to length before string
    addq $1,%r10                # r10= pointer to the start of the string
    xorq  %r11, %r11            # clear r11
    xorq  %r9, %r9              # clear r12
    movb %sil,%r11b             # r11= old char
    movb %dl,%r9b               # r12= new char
    
    xorq  %rcx, %rcx            # clear counter
    
    cmpq %r8,%rcx               # if counter>len
    ja .done
                         
    .loop:
    cmpb (%r10), %r11b          # if current index == old char
    je .switch
   
    .update:
    addq $1,%r10                #current char in string ++
    addq $1,%rcx                #counter++
    cmpq %r8,%rcx               # if counter>len
    jae .done 
    
    jmp .loop                   # else - counter<len - continue loop

    .switch:
    movb %r9b,(%r10)
    jmp .update
    
    .done:
    movq %rdi,%rax
    ret
    

.globl pstrijcpy
    .type pstrijcpy, @function
pstrijcpy: 
    # pstring dst in %rdi, pstring src in %rsi, first index in %dl,second index in %cl.
    movq %rdi,%r8               #r8= pointer to dst string
    movq %rsi,%r9               #r9= pointer to src string
    
    xorq  %r10, %r10            # clear r10
    movb %dl, %r10b             # r10=i
    
    xorq %r11, %r11             # clear r11
    movb %cl, %r11b             #r11=j
    
    movq %r8,%rax               #backup r8 in rax
    
    addq $1,%r11                #j= j+1

    
    cmpb %r10b,(%r8)            #length first<i
    jl .error
    
    cmpb %r11b,(%r8)            #length first<j
    jl .error
    
    cmpb %r10b,(%r9)            #length second< i
    jl .error
    
    cmpb %r11b,(%r9)            #length second<i
    jl .error
    
    cmpb %r10b,%r11b            #j< i
    jle .error
    
    cmpb $0,%r10b               #second index<0
    jl .error
    
    cmpb $1,%r11b               #first index<1
    jl .error

    addq $1,%r10                #i= i+1
    
    addq %r10,%r8               #r8 + i -> r8
    addq %r10,%r9               #r9 + i -> r9
        
    .loop1:
    
    movq $0, %rcx 
    movb (%r9),%cl              #switch
    movb %cl, (%r8)
    
    addq $1,%r8                 #r8++
    addq $1,%r9                 #r9++

    addb $1,%r10b               #i++
    
    cmpb %r10b,%r11b            #j< i
    jl .done1
    
    jmp .loop1
    
    
    .done1:
        ret
    
    .error:
    
    pushq %rbp                  # save the old frame pointer
    movq %rsp, %rbp             # create the new frame pointer
    
    subq $8,%rsp
    movq %r8,(%rsp)
    
    
    movq $invalidInputMsg,%rdi #printf will print %rdi
    movq $0, %rax
    call printf
    
    movq (%rsp),%rax
    
    movq %rbp,%rsp
    popq %rbp
    ret
    
    
    
.globl swapCase
    .type swapCase, @function
swapCase:
    # pstring dst in %rdi.
    movq %rdi,%rax              # set return value(rax) as pointer to dst
    movq $0, %r8
    movb (%rdi), %r8b           #r8=length
    addq $1, %rdi               #rdi= points to string
    
    movq $0, %r9                # r9 =counter(initialized to 0)
    
      
    .loop2:
    cmpb $'A',(%rdi)            # not a letter - no need to change
    jl .continue
      
    cmpb $'Z',(%rdi)            # upper case letter - switch to lower
    jle .switchUpperToLower
    
    cmpb $'a',(%rdi)            # not a letter - no need to change
    jl .continue
    
    cmpb $'z',(%rdi)            # lower case letter - switch to upper
    jle .switchLowerToUpper
    
    .continue:
    addq $1, %r9                # counter++
    addq $1, %rdi               # next index on string
    cmpq %r8, %r9               # length<counter
    ja .done2
    jmp .loop2                  #else- continue loop
    
    .switchUpperToLower:
    movq $0,%r10
    movb (%rdi),%r10b           #get value of rdi(current index)
    addq $'a',%r10              #add the difference between 'a' and 'A' to the value
    subq $'A',%r10
    movb %r10b,(%rdi)           #insert the lower case to the current index value 
    jmp .continue
    
    .switchLowerToUpper:
    movq $0,%r10
    movb (%rdi),%r10b           #get value of rdi(current index)
    addq $'A',%r10              #add the difference between 'a' and 'A' to the value
    subq $'a',%r10
    movb %r10b,(%rdi)           #insert the lower case to the current index value 
   
    jmp .continue
    
    .done2:
    ret
    
    
    
    .globl pstrijcmp
    .type pstrijcmp, @function
pstrijcmp:

# pstring str1 in %rdi, pstring str2 in %rsi, first index in %dl,second index in %cl.
    movq %rdi,%r8               #r8= pointer to str1 string
    movq %rsi,%r9               #r9= pointer to str2 string
    
    xorq  %r10, %r10            # clear r10
    movb %dl, %r10b             # r10=i
    
    xorq %r11, %r11             # clear r11
    movb %cl, %r11b             #r11=j
    
    addq $1,%r11                #j= j+1
    
    cmpb %r10b,(%r8)            #length first<i
    jl .error1
    
    cmpb %r11b,(%r8)            #length first<j
    jl .error1
    
    cmpb %r10b,(%r9)            #length second< i
    jl .error1
    
    cmpb %r11b,(%r9)            #length second<i
    jl .error1
    
    cmpb %r10b,%r11b            #j< i
    jle .error1
    
    cmpb $0,%r10b               #second index<0
    jl .error1
    
    cmpb $1,%r11b               #first index<1
    jl .error1
    
    addq $1,%r10                #i= i+1
    
    addq %r10,%r8               #r8 + i -> r8
    addq %r10,%r9               #r9 + i -> r9
    
    .loop3:
    movq $0,%rax 
    movb (%r8),%al              #rax(al)= value of current index of str1
    cmpb (%r9),%al              #value of current index of str1> value of current index of str2
    ja .bigger
    
    cmpb (%r9),%al              #value of current index of str1< value of current index of str2
    jl .smaller
    
    addq $1,%r8                 #r8++
    addq $1,%r9                 #r9++

    addb $1,%r10b               #i++
    
    cmpb %r10b,%r11b            #j< i
    jl .done3
    jmp .loop3
    
    
    .done3:
    
        movq $0,%rax
        ret
    
    .bigger:
    movq $1,%rax
    ret
    
    
    .smaller:
    movq $-1,%rax
    ret
    
    
    .error1:
    movq $invalidInputMsg,%rdi  #printf will print %rdi
    movq $0, %rax
    call printf
    movq $-2,%rax
    ret
    
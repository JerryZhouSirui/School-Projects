        lw          0       1       n
        lw          0       2       r
        lw          0       4       Caddr        load combination function address
        lw          0       3       zr
        jalr        4       7                    call function, r7 = return, jump to function
        halt                                        
start   beq         0       2       base
        beq         1       2       base        base cases to return 1 in the recusive function
        noop
        sw          5       7       Stack          
        lw          0       6       one
        add         5       6       5
        sw          5       1       Stack       save stack ptr, local, n and r on the stack
        add         5       6       5
        sw          5       2       Stack
        add         5       6       5
        noop                                    
        lw          0       6       neg1        (n-1,r)
        add         6       1       1
        lw          0       6       Caddr
        jalr        6       7                  
        lw          0       6       neg1
        add         6       2       2
        lw          0       6       Caddr
        jalr        6       7
        lw          0       6       neg1
        add         6       5       5
        lw          5       2       Stack
        add         6       5       5
        lw          5       1       Stack
        add         6       5       5
        lw          5       7       Stack
        jalr        7       6
base    lw          0       4       one
        add         4       3       3
        jalr        7       6
n       .fill       14
r       .fill       7
Caddr   .fill       start
neg1    .fill       -1        
one     .fill       1
Stack   .fill       0
zr      .fill       0
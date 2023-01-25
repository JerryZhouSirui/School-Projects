        lw          0       1       n
        lw          0       2       r
        lw          0       4       Caddr        load combination function address
        jalr        4       7                    call function, r7 = return, jump to function
        halt                                        
start   sw          5       7       Stack           start the function here
        lw          0       6       one
        add         5       6       5
        sw          5       1       Stack       save stack ptr, local, n and r on the stack
        add         5       6       5
        sw          5       2       Stack
        add         5       6       5
        lw          0       4       zr
        sw          5       4       Stack
        add         5       6       5
        noop
        beq         0       2       base
        beq         1       2       base        base cases to return 1 in the recusive function
        noop
        lw          0       6       neg1        call to n-1,r
        add         6       1       1           n-1
        lw          0       6       Caddr
        jalr        6       7                   call function and save return addy for next function call
        lw          0       6       neg1
        add         6       2       2
        lw          0       6       Caddr
        jalr        6       7                   call to n-1,r-1

base    lw          0       3       one
        beq         0       0       rest
rest    lw          0       6       neg1
        add         6       5       5
        lw          5       4       Stack
        add         6       5       5
        lw          5       2       Stack
        add         6       5       5
        lw          5       2       Stack
        add         6       5       5
        lw          5       7       Stack
        jalr        7       6                   jump to where 7 left off (big cliff hanger ya feel)
n       .fill       7
r       .fill       3
Caddr   .fill       start
neg1    .fill       -1        
one     .fill       1
Stack   .fill       0
zr      .fill       0
        sw      0       1       five    load reg1 with 5 (symbolic address)
        sw      1       2       six       load reg2 with -1 (numeric address)
        sw      0       1       five
        sw      0       1       six
start   add     1       2       1       decrement reg1
        beq     0       1       -2       goto end of program when reg1==0
        beq     0       0       start   go back to the beginning of the loop
        noop
done    halt                            end of program
five    .fill   32769
six     .fill   -32770
neg1    .fill   -1
stAddr  .fill   five                   will contain the address of start (2)
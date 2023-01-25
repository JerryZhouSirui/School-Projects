        lw      0       1       32769    load reg1 with 5 (symbolic address)
        lw      1       2       -32770       load reg2 with -1 (numeric address)
start   add     1       2       1       decrement reg1
        beq     0       1       done       goto end of program when reg1==0
        beq     0       0       five   go back to the beginning of the loop
        beq     0       0       six
        noop
        jalr    0       0       stAddr
        jalr    0       1
done    halt                            end of program
five    .fill   32769
six     .fill   -32770
neg1    .fill   -1
stAddr  .fill   five                   will contain the address of start (2)
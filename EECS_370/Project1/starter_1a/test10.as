        lw      0       1       five   load reg1 with 5 (symbolic address)
        lw      1       2       six       load reg2 with -1 (numeric address)
start   add     1       2       1       decrement reg1
        beq     0       1       start       goto end of program when reg1==0
        beq     0       0       done   go back to the beginning of the loop
        jalr    3       3       start
        noop    0       0       1
        noop    0       0       start
done    halt                            end of program
five    .fill   1147483660
six     .fill   -1147483660
neg1    .fill   -1
stAddr  .fill   five                   will contain the address of start (2)
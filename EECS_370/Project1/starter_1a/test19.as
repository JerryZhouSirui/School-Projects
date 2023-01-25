        lw      0       1       five    load reg1 with 5 (symbolic address)
        jalr     1       2       six       load reg2 with -1 (numeric address)
start   add     1       2       1       decrement reg1
        jalr     0       1              goto end of program when reg1==0
        jalr     0       0       start   go back to the beginning of the loop
        noop
done    halt                            end of program
five    .fill   69
six     .fill   -69
neg1    .fill   -1
stAddr  .fill   five                   will contain the address of start (2)
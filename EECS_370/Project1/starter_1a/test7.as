        lw      0       1       five    load reg1 with 5 (symbolic address)
        lw      1       2       six       load reg2 with -1 (numeric address)
        lw      2       1       stop
start   add     1       2       1       decrement reg1
        beq     0       1       -2       goto end of program when reg1==0
        beq     0       0       start   go back to the beginning of the loop
once    beq     0       1       twice
        noop
        noop
        noop
twice   beq     0        0      once
        noop
        jalr    1       2       stop
done    halt                            end of program
five    .fill   32769
six     .fill   -32770
neg1    .fill   -1
stop    .fill   done
junk    .fill   57
stAddr  .fill   five                   will contain the address of start (2)
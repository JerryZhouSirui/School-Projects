        lw      0       1       count
        lw      0       2       one
        lw      0       3       neg1
while   beq     0       1       done
        add     2       2       4
        add     1       3       1
        beq     0       0       while
done    halt
count   .fill   10
one     .fill   1
neg1    .fill   -1
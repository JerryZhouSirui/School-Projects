        lw      0       1       data
        lw      1       2       thang
        lw      1       3       lbl
        nor     4       5       5
loop    beq     5       3       done
        lw      0       4       hell
        add     6       2       4
        sw      0       5       thang
        add     1       4       3
        beq     0       1       loop
done    halt
lbl     .fill   3
data    .fill   0
thang   .fill   5
smell   .fill   -10
hell    .fill   3
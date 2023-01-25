        lw      3       1       data
        lw      1       2       thang
        lw      0       3       lbl
        nor     5       5       5
loop    beq     5       6       done
        lw      0       4       hell
        add     4       2       4
        sw      5       4       thang
        add     1       3       3
        beq     2       0       loop
done    halt
lbl     .fill   3
data    .fill   0
thang   .fill   5
smell   .fill   -10
hell    .fill   3
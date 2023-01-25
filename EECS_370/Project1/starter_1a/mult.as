        lw      0       1       result
        lw      0       2       mcand
        lw      0       3       mplier
        lw      0       4       mask
        lw      0       5       mxbit
loop    nor     2       4       6       isolate 1 bit
        beq     0       6       adds   
        beq     0       0       skip    if nor result means bit is zero branch
adds    add     1       3       1
skip    lw      0       7       neg1    
        add     4       4       4
        add     5       7       5               dec 1 on the loop
        lw      0       7       one
        add     7       4       4
        beq     0       5       end
        add     3       3       3
        beq     0       0       loop
end     halt
mcand       .fill       5
mplier      .fill       10
result      .fill       0
neg1        .fill       -1 
mxbit      .fill       15
mask        .fill       -2
one         .fill       1
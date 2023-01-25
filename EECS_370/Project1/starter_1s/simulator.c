/*
 * Project 1
 * EECS 370 LC-2K Instruction-level simulator
 *
 * Make sure *not* to modify printState or any of the associated functions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Machine Definitions
#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8 /* number of machine registers */

// File
#define MAXLINELENGTH 1000 /* MAXLINELENGTH is the max number of characters we read */

typedef struct stateStruct {
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);

int convertNum(int);

int main(int argc, char *argv[])
{
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;

    if (argc != 2) {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }

    for(int i = 0; i < NUMMEMORY; i++) {
        state.mem[i] = 0;
    }
    for(int i = 0; i < NUMREGS; i++) {
        state.reg[i] = 0;
    }

    /* read the entire machine-code file into memory */
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; state.numMemory++) {
        if (sscanf(line, "%d", state.mem+state.numMemory) != 1) {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

    //Your code starts here
    int instruction = 0;

    while(1){
        
        printState(&state); //print out the current state of state before doing anything

        int opcode = state.mem[state.pc]; //separate elements of the machine code
        opcode = opcode & (0b00000001110000000000000000000000);
        opcode = opcode >> 22;
        int arg0 = state.mem[state.pc];
        arg0 = arg0 & (0b00000000001110000000000000000000);
        arg0 = arg0 >> 19;
        int arg1 = state.mem[state.pc];
        arg1 = arg1 & (0b00000000000001110000000000000000);
        arg1 = arg1 >> 16;
        int other = state.mem[state.pc];
        other = other & (0b00000000000000001111111111111111);
        other = convertNum(other);
        int arg2 = state.mem[state.pc];
        arg2 = arg2 & (0b00000000000000000000000000000111);

        
        
        if(opcode == 0b110){ //condition to exit the loop when needed
            state.pc++;
            instruction++;
            break;
        }
        else if(opcode == 0b111){ //noop 
            state.pc++;
        }
        else if(opcode == 0b000){ //add
            state.pc++;
            state.reg[arg2] = state.reg[arg0] + state.reg[arg1];
        }
        else if(opcode == 0b001){ //nor
            state.pc++;
            state.reg[arg2] = ~(state.reg[arg0]|state.reg[arg1]);
        }
        else if(opcode == 0b010){ //lw
            state.pc++;
            state.reg[arg1] = state.mem[state.reg[arg0] + other];
        }
        else if(opcode == 0b101){ //jalr
            state.reg[arg1] = state.pc + 1;
            state.pc = state.reg[arg0];
        }
        else if(opcode == 0b011){ //sw
            int calculatedAddress = state.reg[arg0] + other; 
            if(state.numMemory <= calculatedAddress) {//if we are trying to store something on the stack
	            state.numMemory = calculatedAddress + 1; 
            }//expand our 'memorysize' so that printstate shows the stack
            state.mem[state.reg[arg0] + other] = state.reg[arg1];
            state.pc++;
        }
        else if(opcode == 0b100){ //beq
            if(state.reg[arg0] == state.reg[arg1]){
                state.pc = state.pc + other + 1;
            }
            else {
                state.pc++;
            }
        }
        instruction++;
    }
    printf("machine halted\n");
    printf("total of %d instructions exectued\n", instruction);
    printf("final state of machine:\n");
    printState(&state);

    return(0);
}

void printState(stateType *statePtr)
{
    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");
    for (i=0; i<statePtr->numMemory; i++) {
              printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    }
    printf("\tregisters:\n");
    for (i=0; i<NUMREGS; i++) {
              printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    }
    printf("end state\n");
}

int convertNum(int num)
{
    /* convert a 16-bit number into a 32-bit Linux integer */
    if (num & (1<<15) ) {
        num -= (1<<16);
    }
    return(num);
}


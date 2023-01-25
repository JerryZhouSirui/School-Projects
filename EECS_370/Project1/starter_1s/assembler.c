/**
 * Project 1 
 * Assembler code fragment for LC-2K 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);

struct symb {
    char lbl[6];
    int addr;
};






int
main(int argc, char *argv[])
{
    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
            arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

    if (argc != 3) {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",
            argv[0]);
        exit(1);
    }

    inFileString = argv[1];
    outFileString = argv[2];

    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL) {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }
    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL) {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }

    struct symb symbls[MAXLINELENGTH];

    //Begin looping through for the first pass
    int addy = 0;
    int symbs = 0;
    while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
        if(strcmp(label, "")) {
            symbls[symbs].addr = addy;
            strcpy(symbls[symbs].lbl, label);
            symbs++;
        }
        addy++;
    }

    rewind(inFilePtr);
    addy = 0;
    for(int i = 0; i < symbs; i ++) {
        for(int j = i + 1; j < symbs; j++) {
            if(!strcmp(symbls[i].lbl, symbls[j].lbl)) {
                exit(1);
            }
        }
    }


    /* after doing a readAndParse, you may want to do the following to test the
        opcode */
    while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
        int mval = 0;
        if(!strcmp(opcode, "halt")){
            mval += (0b110 << 22);
        }
        else if(!strcmp(opcode, "noop")){
            mval += (0b111 << 22);
        }
        else if (!strcmp(opcode, "add")) {
            int a0 = atoi(arg0);
            int a1 = atoi(arg1);
            int a2 = atoi(arg2);
            mval += (a0 << 19);
            mval += (a1 << 16);
            mval += (a2 << 0);
        }
        else if (!strcmp(opcode, "nor")) {
            int a0 = atoi(arg0);
            int a1 = atoi(arg1);
            int a2 = atoi(arg2);
            mval += (0b1 << 22);
            mval += (a0 << 19);
            mval += (a1 << 16);
            mval += (a2 << 0);
        }
        else if (!strcmp(opcode, "lw")) {
            int a0 = atoi(arg0);
            int a1 = atoi(arg1);
            mval += (0b10 << 22);
            mval += (a0 << 19);
            mval += (a1 << 16);

            if(isNumber(arg2)) {
                int a2 = atoi(arg2);
                if(!(a2 < -32768 || a2 > 32767)) {
                    mval += a2 & (0b00000000000000001111111111111111);
                }
                else {
                    exit(1);
                }
            }
            else {
                int fadd = -69;
                for(int i = 0; i < symbs; i++) {
                    if(!strcmp(symbls[i].lbl, arg2)) {
                        fadd = symbls[i].addr;
                        break;
                    }
                }
                if(fadd == -69) {
                    exit(1);
                }
                if(fadd < 0){
                    fadd = fadd & (0b00000000000000001111111111111111);
                }
                mval += fadd;
            }
            
        }
        else if (!strcmp(opcode, "sw")) {
            int a0 = atoi(arg0);
            int a1 = atoi(arg1);
            mval += (0b11 << 22);
            mval += (a0 << 19);
            mval += (a1 << 16);

            if(isNumber(arg2)) {
                
                int a2 = atoi(arg2);
                if(!(a2 < -32768 || a2 > 32767)) {
                    mval += a2 & (0b00000000000000001111111111111111);
                }
                else {
                    exit(1);
                }
            }
            else {
                int fadd = -69;
                for(int i = 0; i < symbs; i++) {
                    if(!strcmp(symbls[i].lbl, arg2)) {
                        fadd = symbls[i].addr;
                        break;
                    }
                }
                if(fadd == -69) {
                    exit(1);
                }
                if(fadd < 0){
                    fadd = fadd & (0b00000000000000001111111111111111);
                }
                mval += fadd;
            }
            
        }
        else if (!strcmp(opcode, "beq")){
            int a0 = atoi(arg0);
            int a1 = atoi(arg1);
            mval += (0b100 << 22);
            mval += (a0 << 19);
            mval += (a1 << 16);

            if(isNumber(arg2)) {
                
                int a2 = atoi(arg2);
                if(!(a2 < -32768 || a2 > 32767)) {
                    mval += a2 & (0b00000000000000001111111111111111);
                }
                else {
                    exit(1);
                }
            }
            else {
                int fadd = -69;
                for(int i = 0; i < symbs; i++) {
                    if(!strcmp(symbls[i].lbl, arg2)) {
                        fadd = symbls[i].addr;
                        break;
                    }
                }
                if(fadd == -69) {
                    exit(1);
                }
                fadd = fadd - addy - 1;
                if(fadd < 0){
                    fadd = fadd & (0b00000000000000001111111111111111);
                }
                mval += fadd;
            }
            
        }
        else if (!strcmp(opcode, "jalr")) {
            int a0 = atoi(arg0);
            int a1 = atoi(arg1);
            mval += (0b101 << 22);
            mval += (a0 << 19);
            mval += (a1 << 16);
        }
        else if(!strcmp(opcode, ".fill")) {
            if(isNumber(arg0)) {
                int val = atoi(arg0);
                if(!(val < -2147483648 || val > 2147483647)) {
                    mval += val;
                }
                else {
                    exit(1);
                }
            }
            else{
                int fadd = -69;
                for(int i = 0; i < symbs; i++) {
                    if(!strcmp(symbls[i].lbl, arg0)) {
                        fadd = symbls[i].addr;
                        break;
                    }
                }
                if(fadd == -69) {
                    exit(1);
                }
                mval += fadd;
            }
        }
        else{
            exit(1);
        }
        addy++;
        fprintf(outFilePtr, "%d\n", mval);
    }
    

    return(0);
}

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int
readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
    char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];
    char *ptr = line;

    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
	/* reached end of file */
        return(0);
    }

    /* check for line too long */
    if (strlen(line) == MAXLINELENGTH-1) {
	printf("error: line too long\n");
	exit(1);
    }

    /* is there a label? */
    ptr = line;
    if (sscanf(ptr, "%[^\t\n ]", label)) {
	/* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }

    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
        opcode, arg0, arg1, arg2);
    return(1);
}

int
isNumber(char *string)
{
    /* return 1 if string is a number */
    int i;
    return( (sscanf(string, "%d", &i)) == 1);
}


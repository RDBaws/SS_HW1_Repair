#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Created by Robert Davis
COP 3402: Systems Software

This assignment creates a stack based P-machine*/

/*todo Fix Errors
 *Todo: Implementation of Fetch Cycle
 *  I think this was fixed with use of extra variable for address
 *Todo: Segfaults on input
 * */

typedef struct Instruction{
    int OP, L, M;
} Instruction;

#define MAX_PAS_LENGTH 500
//Create global variables for pointers
int pas[MAX_PAS_LENGTH];
int IC = 0;

//Pointers to be initialized later
int BP;
int GP;
int DP;
int FREE;
int PC;

int SP = MAX_PAS_LENGTH;
int pas[MAX_PAS_LENGTH];

//Define

//Function Stubs
int base(int L);
void print_execution(int line, char *opname, int *IR, int PC, int BP, int SP, int DP, int *pas, int GP);

Instruction instructionRegister;
int* programCounter;

int main(int argc, char* argv[]){
    //Is the VM Running
    int flag = 1;
    //Char array to hold call name
    char OP[4];

    FILE* inFile = fopen("test1.txt","r");
    if(!inFile){
        printf("Input Not Opened! Please try again!\n");
        exit(-1);
    }


    //Initialize pas to all zeros to avoid undefined behavior in while look check
    for(int i = 0; i < MAX_PAS_LENGTH; i++){
        pas[i] = 0;
    }

    //Load input file into text space
    while(!feof(inFile)){
        fscanf(inFile, "%d %d %d", &pas[IC], &pas[IC+1], &pas[IC+2]);
        //printf("%d %d %d\n", pas[IC], pas[IC+1], pas[IC+2]);
        IC += 3;
    }

    //Initialize variables after program load
    GP = IC;
    DP = IC-1;
    FREE = IC + 40;
    BP = IC;
    PC = 0;
    SP = MAX_PAS_LENGTH;

    //Track line number
    int lineNum = 0;

    printf("\t\t\t\t\tPC\tBP\tSP\tDP\tdata\n");
    //Print Initial Values
    printf("Initial values:\t\t%d\t%d\t%d\t%d\n", PC, BP, SP, DP);

    //Begin program running

    while(flag == 1 && PC <= IC){

        //printf("%d: PC=================================================================\n", PC);
        //Fetch Cycle


        programCounter = &pas[PC];

        //Set up structure with data
        instructionRegister.OP = *programCounter;
        instructionRegister.L = *(programCounter + 1);
        instructionRegister.M = *(programCounter + 2);
        PC += 3;



        //Execution Cycle
        switch(instructionRegister.OP) {
            case 1:
                if (BP == GP) {
                    DP++;
                    pas[DP] = instructionRegister.M;
                } else {
                    SP--;
                    pas[SP] = instructionRegister.M;
                }
                strcpy(OP, "LIT");
                break;

            case 2:
                switch (instructionRegister.M) {

                    case 0:
                        SP = BP + 1;
                        BP = pas[SP - 2];
                        PC = pas[SP - 3];
                        strcpy(OP, "RTN");
                        break;

                    case 1:
                        if (BP == GP)
                            pas[DP] = -1 * pas[DP];
                        else
                            pas[SP] = -1 * pas[SP];

                        strcpy(OP, "ADD");
                        break;

                    case 2:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] + pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] + pas[SP - 1];
                        }
                        strcpy(OP, "SUB");
                        break;

                    case 3:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] - pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] - pas[SP - 1];
                        }
                        break;

                    case 4:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] * pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] * pas[SP - 1];
                        }
                        strcpy(OP, "MUL");
                        break;

                    case 5:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] / pas[DP + 1];
                        } else {
                            SP--;
                            pas[SP] = pas[SP] / pas[SP - 1];
                        }
                        strcpy(OP, "DIV");
                        break;

                    case 6:
                        if (BP == GP) {
                            pas[DP] = pas[DP] % 2;
                        } else {
                            pas[SP] = pas[SP] % 2;
                        }
                        strcpy(OP, "ODD");
                        break;

                    case 7:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] % pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] % pas[SP - 1];
                        }
                        strcpy(OP, "MOD");
                        break;

                    case 8:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] == pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] != pas[SP - 1];
                        }
                        strcpy(OP, "EQL");
                        break;

                    case 9:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] != pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] != pas[SP - 1];
                        }
                        strcpy(OP, "NEQ");
                        break;

                    case 10:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] < pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] < pas[SP - 1];
                        }
                        strcpy(OP, "LSS");
                        break;

                    case 11:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] <= pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] <= pas[SP - 1];
                        }
                        strcpy(OP, "LEQ");
                        break;

                    case 12:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] > pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] > pas[SP - 1];
                        }
                        strcpy(OP, "GTR");
                        break;

                    case 13:
                        if (BP == GP) {
                            DP--;
                            pas[DP] = pas[DP] >= pas[DP + 1];
                        } else {
                            SP++;
                            pas[SP] = pas[SP] >= pas[SP - 1];
                        }
                        strcpy(OP, "GEQ");
                        break;
                }
                break;

            case 3:
                if(BP == GP){
                    DP ++;
                    pas[DP] = pas[GP + instructionRegister.M];
                }
                else{
                    if(base(instructionRegister.L) == GP){
                        SP--;
                        pas[SP] = pas[GP + instructionRegister.M];
                    }
                    else{
                        SP--;
                        pas[SP]=pas[base(instructionRegister.L) - instructionRegister.M];
                    }
                }

                strcpy(OP, "LOD");
                break;
            case 4:
                if(BP == GP){
                    pas[GP + instructionRegister.M] = pas[SP];
                    SP++;
                }
                else if(base(instructionRegister.L) == GP){
                    pas[GP + instructionRegister.M] = pas[SP];
                    SP++;
                }
                else{
                    pas[base(instructionRegister.L) - instructionRegister.M] = pas[SP];
                    SP++;
                }

                strcpy(OP, "STO");
                break;

            case 5:
                pas[SP - 1] = base(instructionRegister.L);
                pas[SP - 2] = BP;
                pas[SP - 3] = PC;
                BP = SP-1;
                PC = instructionRegister.M;
                strcpy(OP, "CAL");
                break;

            case 6:
                if(BP == GP)
                    DP += instructionRegister.M;
                else
                    SP -= instructionRegister.M;

                strcpy(OP, "INC");
                break;

            case 7:
                PC = instructionRegister.M;
                strcpy(OP, "JMP");
                break;

            case 8:
                if(BP == GP){
                    if(pas[DP] == 0) {
                        PC = instructionRegister.M;
                        DP--;
                    }else if(pas[SP] == 0){
                        PC = instructionRegister.M;
                        SP++;
                    }
                }

                strcpy(OP, "JPC");
                break;

            case 9:
                switch (instructionRegister.M) {
                    case 1:
                        if(BP == GP){
                            DP++;
                            printf("Top of Stack Value: %d\n", pas[DP]);
                            DP--;
                        }
                        else{
                            printf("Top of Stack Value: %d\n", pas[SP]);
                            SP++;
                        }

                        strcpy(OP, "SYS");
                        break;

                    case 2:
                        if(BP == GP){
                            DP++;
                            printf("Please enter an integer: ");
                            scanf("%d", &pas[DP]);
                        } else{
                            SP--;
                            printf("Please enter an integer: ");
                            scanf("%d", &pas[SP]);
                        }
                        strcpy(OP, "SYS");
                        break;
                    case 3:
                        flag = 0;
                        strcpy(OP, "SYS");
                }
        }

        //PC+=3;
        print_execution(lineNum, OP, &instructionRegister.OP, PC, BP, SP, DP, pas, GP);
        lineNum = (PC/3);
    }

    return 0;
}

//Given Base Function
int base(int L)
{
    int arb = BP;
// arb = activation record base
    while ( L > 0) //find base L levels down
    {
        arb = pas[arb];
        L--;
    }
    return arb;
}

//Given Print Function
void print_execution(int line, char *opname, int *IR, int PC, int BP, int SP, int DP, int *pas, int GP)
{
    int i;
// print out instruction and registers
    printf("%2d\t%s\t%d\t\t%d\t%d\t%d\t%d\t%d\t", line, opname, IR[1], IR[2], PC, BP,
           SP, DP);
// print data section
    for (i = GP; i <= DP; i++)printf("%d ", pas[i]);
    printf("\n");
// print stack
    printf("\tstack : ");
    for (i = MAX_PAS_LENGTH - 1; i >= SP; i--)
        printf("%d ", pas[i]);
    printf("\n");
}
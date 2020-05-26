/*
Marja Katrina Centina
Comp 222 - Fall 2019
Assignment 3: Pipelining
*/
#include <stdio.h>
#include <stdlib.h>

//global variables
int numOfInstr = 0;
int i, j, k; //loop variable

//structure for instructions
struct in
{
    char input[100];
   int dest, reg1, reg2;
   int delay;
};

struct in *ptr; //pointer for instruction

//function to get user input for instructions
void getInstruction()
{
printf("Enter number of instructions: ");
scanf("%d" , &numOfInstr);
printf("\n");
ptr = (struct in*)malloc(numOfInstr + 1 * sizeof(struct in)); //dynamic allocation for the number of instructions user inputs

for(i = 1; i <= numOfInstr; i++) //scans each instruction
 {
     printf("%d) ", i);
    scanf("%s", ptr[i].input);

    //gets each number value from the string and puts it to the proper struct properties
    ptr[i].dest=ptr[i].input[1]-'0';
    ptr[i].reg1=ptr[i].input[4]-'0';
    ptr[i].reg2=ptr[i].input[7]-'0';

    printf("%s", ptr[i].input);
   printf("\n");
 }//end for

printf("\n");
return;
}//end get instruction function

//does the calculations for the delays and total number of cycles
void calculate()
{
    for(i = 2; i <= numOfInstr; i++)
    {
        ptr[i].delay = 0; //initializes each delay through loop to 0
        if(ptr[i - 1].dest == ptr[i].reg1 || ptr[i - 1].dest == ptr[i].reg2) //if the next instruction relies on first one, delay is set to 2
        {
            ptr[i].delay = 2;
        }
        else if ((ptr[i - 2].dest == ptr[i].reg1 || ptr[i - 2].dest == ptr[i].reg2) && ptr[i-1].delay != 2) //if there's a delay between first and third register, delay is set to 1
        {
            ptr[i].delay = 1;
        }
    }//end for


    int count = 0; //variable keeps track of instructions with delays = 1 or delay = 2
    int totalCycles = 5;

    //calculates total number of cycles
    for(i = 1; i <= numOfInstr; i++)
   {
    if(i == 1) //adds no additional cycles to the first instruction but initializes it as 5
    {
        totalCycles = 5;
    }

    if(i > 1 && ptr[i].delay == 0) //adds a cycle for instructions without delays
    {
        totalCycles++;
    }

    if(i > 1 && ptr[i].delay == 1)
    {
        totalCycles++;
    }
    else if (i > 1 && ptr[i].delay == 2)
    {
        totalCycles += 2;
    }

    if(ptr[i].delay == 1 || ptr[i].delay == 2) //adds to count if there are instructions with delays
    {
        count++;
    }
   }//end for

    //calculates for the total number of cycles
   totalCycles = totalCycles + count;

    //prints total number of cycles
   printf("Total number of cycles: %d\n", totalCycles);
}//end calculate function

//prints out total number of cycles for the instruction sets
void print()
{
    //local variables to print statements
    int tab = 0;
    int start = 0;

    for(i = 1; i <= numOfInstr; i++)
    {
        //will add in extra tabs and cycles to the cycles if there are delays in the instructions
        if(ptr[i].delay == 2)
        {
            tab += 2;
            start += 2;
        }

        else if (ptr[i].delay == 1)
        {
            tab += 1;
            start += 1;
        }

        //print statements for the program
        printf("Instruction %d is Fetched at Cycle %d\n", i, i + start);
         printf("%d) ", i);

        for(j = 1; j <= tab; j++) //adds in tabs if there's delays
        {
            printf("\t");
        }

        //will create a pyramid like structure with the tabs
        for(k = 1; k < i; k++)
        {
            printf("\t");
        }
        printf("IF\tID\tEX\tMM\tWB\n");
    }

   printf("\n");
   return;
}//end print function



int main()
{
int selection;
do
{
    //heading lines and user input statements
    printf("Pipelined instruction performance\n");
    printf("1) Enter instructions\t2) Determine when instructions are fetched\t3) Exit\n");
    printf("Enter selection: ");
    scanf("%d", &selection);
    printf("\n");
    switch(selection)
    {
        case 1: getInstruction(); break;
        case 2: calculate(); print(); break;
        }
} while(selection != 3); //program terminates when user enters "3"


printf("\n");
printf("Program terminated normally");

return 0;
}

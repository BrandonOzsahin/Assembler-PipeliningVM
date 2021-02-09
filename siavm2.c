#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


unsigned char memory[1024]; 
// unsigned char currentIns[4];
unsigned char OP1; //hold register of trailing instructions
unsigned char OP2; //holds registers/offset of trailing instructions
unsigned char OPA; 
unsigned char OPB;
unsigned char DEST; //"result" register
unsigned char RESULT;
unsigned char opcode = 1; //compared to homework 3 opcode is non usable
unsigned char reg[15]; //14 registers minus stack which needs to be a pointer
unsigned char* point; //pointer to point to an address
char* register15 = &(memory[1023]);
int counter = 0; //for temp to read
// Create a loop to run everything most likely the main?
    int programCounter = 0; // for fetch and such   
    
//////////*************//////// new global variables
    bool fetchBuffer = false;
    bool dispatchBuffer = false;// created for pipelining this is a buffer check.
    bool executeBuffer = false;   // 
    bool storeBuffer = false;
    //buffers
    int Farray[4]; 
    int Darray[4];
    int Earray[4];
    int Sarray[4];
    unsigned char opcode2;// dispatch
    unsigned char opcode3; /// execute
    unsigned char opcode4; // store
    
    
int main(int argc, char** argv[]) 
{
    loadfile (argv[1]);
 

 for(int y = 0; y < 1024; y++)
 {
   if(fetchBuffer == false && dispatchBuffer == false && executeBuffer == false && storeBuffer == false)
    {
       
        fetch();
        fetchBuffer = true;


   }
                                                                                                                     
  
    if(fetchBuffer == true && dispatchBuffer == false && executeBuffer == false && storeBuffer == false)
   {

            Darray[0] = Farray[0];
            
            dispatch();
            dispatchBuffer = true;
            fetch();

   }
 
 if (fetchBuffer == true && dispatchBuffer == true && executeBuffer == false && storeBuffer == false)
 {
          
            Earray[0] = Darray[0];
            execute();
            executeBuffer = true;
            dispatch();
            fetch();       
            if(opcode == 0)
            {
             printf("\n\n HALT REACHED   "); 
             exit(0);
            } 
 }
 
  if (fetchBuffer == true && dispatchBuffer == true && executeBuffer == true && storeBuffer == false)
 {
            Sarray[0] = Earray[0];
            store();
            execute();
            dispatch();
            fetch();
            if(opcode == 0)
            {
             printf("\n\n  HALT REACHED  ");
             exit(0);
            }
  
 }
 }
    return 0;

    }

void loadfile()
{
    
    FILE *src = fopen("output.txt","rb");
     unsigned char line[2]; // keeps the [][] array positioning i.e 11 then 23 "TEMP"
     // counter is each iteration of memory array of text file
    while (fgets(line,sizeof(line),src)!= NULL) 
        {
            for(int i = 0; i < 1; i++) // for loop to run the read
            {
                memory[counter] = line[i]; // counter will always go forward till the end and line i will read the first two over and over and allocate into memory
                    counter++;
            }
        } 
   fclose(src);
    
   // return (EXIT_SUCCESS);
}
    
void fetch()
{
    opcode = memory[programCounter] >> 4; //"1"
   

    switch(opcode)
    {

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 14:
        case 15:
           
                Farray[0] = memory[programCounter] << 8 | memory[programCounter+1];
                programCounter= programCounter+2; 
                printf("\ninstruction fetched: %x",Farray[0]);

            break;
           
        case 10:
        case 11:
        case 12:
        case 13:
            
              Farray[0] = memory[programCounter] << 24 | memory[programCounter + 1] << 16 |memory[programCounter + 2] << 8 | memory[programCounter + 3];
                programCounter= programCounter+4;

            break;
            }
    
    }
 



void dispatch()
{
    opcode2 = opcode;
    switch(opcode2)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 14:
        case 15:
        Darray[0] = Farray[0];
        OP1 = (Darray[0] >> 8) & 0x0F; 
        OP2 = memory[programCounter+1];
        printf("\n%x(Being Decoded)",Darray[0]);
        
        break;
        case 10:
        case 11:
        Darray[0] = Farray[0]; //passes the fetched buffer into the decode buffer 
        OP1 = (Darray[0] >> 4) & 0x0F;
        DEST = (Darray[0] & 0x0F);
        OP2 = memory[programCounter+1]; 
          
        printf("\n%x(Being Decoded)",Darray[0]);
        break;
        
        case 12:
        case 13:
        OP1 = 0x00;
        OP2 = 0x00;
        DEST = Darray[0] & 0xFFFFFFF;
        printf("\n%x(Being Decoded)",Darray[0]);
        break;

    }
}
    /*******************this is where HALT should stop, in assembly halt should shouldn't mean anything until execute stage.*******************/
void execute() 
{
    OP1 = 3;
    OP2 = 5;
    OPA = OP1; // introduces the new pipeline OP's to hold the previous iterations.
    OPB = OP2;
    reg[OPA] = 3;
    reg[OPB] = 5;
    Earray[0] = Darray[0];
    
    opcode3 = opcode2;

        printf("\n%x Being Executed: ",Earray[0]); 
    switch(opcode3)
    { 
     case 1: // 3R (add,and,divide,multiply,subtract,or
         RESULT = reg[OPA] + reg[OPB];
         printf("\nResult: %d",RESULT);
         break;
     case 2:
         RESULT = reg[OPA] & reg[OPB];
         printf("\nResult: %d",RESULT);
         break;
    case 3:
         if(reg[OPB] == 0)
         {
             printf("\nDIVIDE BY ZERO ERROR!");
         }
         else
         {
         RESULT = reg[OPA] / reg[OPB];
         printf("\nResult: %d",RESULT);
         }
         break;
     case 4:
         RESULT = reg[OPA] * reg[OPB];
         printf("\nResult: %d",RESULT);
         break;
     case 5:
         RESULT = reg[OPA] - reg[OPB];
         printf("\nResult: %d",RESULT);
         break;
     case 6:
         RESULT = reg[OPA] | reg[OPB];
         printf("\nResult: %d",RESULT);
         break;
     case 7:
        if(OPB == 4)
         {
            RESULT = reg[OPA];
         } 
         break;
     case 8:
         if((DEST & 0x0F) == 0)
         {
         for(int i = 0; i < sizeof(reg); i++)
         {
             printf("\nreg[%d]: %d",i,reg[i]);
         }
         printf("\n");
         }
         else if ((DEST & 0x0F) == 1)
         {
         for(int k = 0; k <sizeof(memory); k++)
         {
             printf("%x",memory[k]); 
         }
         }
         break;
     case 9:
         RESULT = reg[OPA] + OPB;// this is just the number itself
      //   printf("\nResult: %d",RESULT);
         break;
     case 10:
         if(reg[OPA] == reg[OPB])
         {
          programCounter = programCounter + (2 * DEST);
         }
         break;
     case 11:
         if(reg[OPA] < reg[OPB])
         {
             programCounter = programCounter + (2*DEST);
         }
         break;
     case 12:
         programCounter = DEST * 2;
         printf("Jump to destination: %x",programCounter);

         break;
     case 13:
        programCounter = DEST * 2;
            int stack = 0;
           while(stack < 32)
            {
                *register15 = programCounter + 1 >> stack;
                register15 = register15 - 1;
                stack = stack + 8;
            }
            printf("Calljump to address: %x",*register15);

         break;
     case 14:
     case 15:
        point = &reg[OPA] + 2*DEST;
             break;
                 
    }
    
    
}

 void store()
 {
     opcode4 = opcode3;
    Sarray[0] = Earray[0];
    printf("\nCurrently being stored: %x",Sarray[0]);
     switch(opcode4)
     { // 3R + addi
         case 1:
         case 2:
         case 3:
         case 4:
         case 5:
         case 6:
         case 9:
            reg[DEST] = RESULT;
            break;
         case 14:
             reg[DEST] = *point;
             break;
         case 15:
             *point = reg[DEST];
             break;
           case 7:
             if(OP2 == 4)
             {
             int stack = 0;
             while(stack < 32)
            {
                *register15 = RESULT >> stack;
                register15 = register15 - 1;
                stack = stack + 8;
            }
            
             }
             /*
             else if (OP2 == 8)
             {
                 int stack = 24;
                 while(stack >= 0)
                 {
                     reg[OP1] = *register15 >> stack;                     *********CANT FIGURE OUT*************
                     *register15 = 0 >> stack;
                     stack = stack - 8;
                     
                 } 
                 
                 
             } 
             else if (OP2 == 0)
             {
                 int stack = 0;
                 
             }
             
      
             break;
      */
     }
     }

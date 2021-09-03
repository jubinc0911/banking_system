/*****************************************************************
//
//  NAME:        Ju-Bin Choi
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        Oct 26. 2020
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This file will give user interface of the banking system and
//   will show the menu with several options. Based on the user's choice
//   It will bring the user to the option, and also, it contains the
//   debug mode with it.
//
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

int debugMode;

void getAddress(char [], int);



/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main function will first show the banking
//                 menu with description of each option. Then, it  will
//                 get the user's choice and bring them to whatever
//                 they want. Also, once, they put invalid input, it
//                 will request for a valid, and it also contains
//                 the debug mode when there's a debug command in
//                 the execute command.
//                 
//
//
//  Parameters:    argc (int): it stores the number of
//                             command arguments
//                 argv (char *): it works as a pointer of
//                                array of the arguments
//
//  Return values:  0 : run successfully
//
****************************************************************/

int main (int argc, char *argv[])
{
    struct record * start = NULL;

    int quit = -1;
    int validChoice;

    char userInput[20];

    char accountNumber[30];
    int accountNum;
    int validNum;

    char name[30];
    int onlyWhiteSpace;
 
    char address[80];

    if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
         debugMode = 1;
        
         printf("\n             **************** DUBEG MODE ****************\n\n");
    }
    else if (argc == 1)
    {
        debugMode = 0;
    } 
    else
    {
        printf("Invalid execution\n");
        printf("Please execute with the valid command\n");
        
        quit = 0;
    }

    readfile(&start, "record.txt");

    if (quit != 0)
    {
        printf("               Welcome to the ICS 212 Banking System\n");
        printf("           Choose an option by entering the name of the option\n");
        printf("             You may enter a part of the name to access\n");
    }

    while (quit == -1)
    {
        printf("\n***********************  ICS 212 Banking System  ***********************\n");
        printf("               Please choose an option from the menu below\n");
        printf("=========================================================================\n\n");
        printf("Add: Add a new record in the databse\n");
        printf("Printall: Print all records in the databse\n");
        printf("Find: Find record(s) with a specific account number\n");
        printf("Delete: Delete existing record(s) from the database using account number\n");
        printf("Quit: Quit the banking system\n\n");
        printf("=========================================================================\n");

        validChoice = -1;
              
        
        fgets(userInput, 20, stdin);

        while (validChoice == -1)
        {
            if (strncmp(userInput, "add", strlen(userInput) - 1) == 0)
            {
                validChoice = 0;
                validNum = 1;

                printf("\nAdd a new record in the database.\n");
                printf("Please enter an account number: \n");
            
                fgets(accountNumber, 30, stdin);
                accountNum = atoi(accountNumber);
                if (accountNum > 0)
                {
                    validNum = 0;
                }
                else
                {
                    while (validNum == 1)
                    {
                        printf("The account number must be a positive integer.\n");
                        printf("Please enter a valid account number.\n");
                    
                        fgets(accountNumber, 30, stdin);
                        accountNum = atoi(accountNumber);
                        if (accountNum > 0)
                        {
                            validNum = 0;
                        }
                    }
                }
                       
                printf("Please enter a name.\n");
              
                
                onlyWhiteSpace = -1;
      
                while (onlyWhiteSpace == -1)
                { 
                    fgets(name, 30, stdin);
                    name[strlen(name) - 1] = '\0';
                
                    if (strstr(name, "\t") == NULL && strstr(name, "\n") == NULL)
                    {
                       onlyWhiteSpace = 0;
                    }
                    else
                    {
                        printf("We do not accept any tab or new line character.\n");
                        printf("Please enter a name again.\n");
                    }
                }
              
                 
                getAddress(address, 80);

                printf("--------------------- RESULT ---------------------\n");
                if (addRecord(&start, accountNum, name, address) != 0)
                {
                    printf("Failed to add Record\n");
                }
                else
                {
                    printf("Successfully added a new record on the database. \n\n");
                    printf("Account Number: %d\n", accountNum);
                    printf("Name: %s\n", name);
                    printf("Address: %s\n", address);
                }
            }
            else if (strncmp(userInput, "printall", strlen(userInput) - 1) == 0)
            {
                validChoice = 0;
                
                printf("--------------------- RESULT ---------------------\n");
                printAllRecords(start);


            }
            else if (strncmp(userInput, "find", strlen(userInput) - 1) == 0)
            {    
                validChoice = 0;
 
                printf("Please enter a account number that you want to find.\n");
              
                fgets(accountNumber, 30, stdin);
                accountNum = atoi(accountNumber);

                
                printf("--------------------- RESULT ---------------------\n");
                findRecord(start, accountNum);

            } 
            else if (strncmp(userInput, "delete", strlen(userInput) - 1) == 0)
            {
                validChoice = 0;
                
                printf("Please enter a account number that you want to delete.\n");
               
                fgets(accountNumber, 30, stdin);
                accountNum = atoi(accountNumber);

               
                printf("--------------------- RESULT ---------------------\n");
                if(deleteRecord(&start, accountNum) == 0)
                {
                    printf("Succesfully deleted record(s) with account #: %d\n", accountNum);
                }
                

            }
            else if (strncmp(userInput, "quit", strlen(userInput) - 1) == 0)
            {
                validChoice = 0;

                printf("\nQuit the system.\n");
                quit = 0;
            }
            else 
            {   
                printf("Eneterd a invalid input. Please enter a valid word, or alphabet.\n");
                printf("If you've enterd a captial letter, please enter a lower case letter.\n");
                printf("If you've entera a space, please remove the space\n"); 
                fgets(userInput, 20, stdin);
                
            }
        }
       

    }

    if (start != NULL)
    {
        writefile(start, "record.txt");
    }

    cleanup(&start);

    return 0;

    
}


/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:    Obtain address from the user and user can
//                  enter more than one line of address without any
//                  input about that.
//
//
//  Parameters:     address (char []) : address that will obtain from
//                                      the user
//                  size (int) : the maximum possible size of 
//                               the address field
//
//  Return values:  No return value (void function)
//
****************************************************************/

void getAddress (char address[], int size)
{
    
    char addr;
    char tempAddress[80];
    int done = -1;
    int count = 0;

    memset(tempAddress, 0, size);
    memset(address, 0, size);
    printf("Please enter your address (max 79 characters).\n");
    printf("When you are done, please enter $ at the end.\n");

    while (done == -1)
    {
        addr = fgetc(stdin);
        if (addr == '$')
        {
            done = 0;
            getchar();
            
        }
        else if (count == size)
        {
            done = 0;
        }
        else
        {
            tempAddress[count] = addr;
        }
        
        count++;
    }
    strcpy(address, tempAddress);
    address[strlen(address)] = '\0';
    if (count >= size)
    {
        while (getchar() != '\n');
    }
    if (debugMode == 1)
    {
        printf("\n********CURRENTLY ON DEBUGGING MODE********\n");
        printf("Function Called : getAddress\n");
        printf("Address: %s\n", address);        
        printf("Size: %d\n", size);
    }
       
}


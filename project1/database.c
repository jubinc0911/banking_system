/*****************************************************************
//
//  NAME:        Ju-Bin Choi
//
//  HOMEWORK:    project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        Oct 26, 2020
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   This file contains the functions that will be used to
//   run a project1, or banking system.
//
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

extern int debugMode;

/*****************************************************************
//
//  Function name:  addRecord
//
//  DESCRIPTION:    From the user, obtain account number, name, and address
//                  then add a record for the user
//                 
//
//  Parameters:     pstart (struct record **) : points the address
//                                               of the record's address
//                  accountNumber (int) : account number got from user
//                  name (char []) : name of the user
//                  address (char []) : address of the user
//
//  Return values:  0 : add successfully
//                 -1 : fail to add record
//                 
//
****************************************************************/

int addRecord(struct record ** pstart, int accountNumber, char name[], char address[])
{
    int returnVal = 0;
    struct record *position = NULL;
    struct record *prev = NULL; 

    struct record *temp = (struct record*) malloc(sizeof(struct record));
    memset(temp, 0, sizeof(struct record));

    temp->accountno = accountNumber;
    strcpy(temp->name, name);
    strcpy(temp->address, address);
    temp->next = NULL;

    if (*pstart == NULL)
    {
        *pstart = temp;
    }
    else
    {
        position = *pstart;
        while (position != NULL && position->accountno > accountNumber)
        {
            position = position->next;
        }
                
        prev = *pstart;

        while (position != *pstart && prev->next != position)
        {
            prev = prev->next;
        }
      
        if (position == *pstart)
        {
            temp->next = position;
            *pstart = temp;
        }
        else if (position == NULL)
        {
            prev->next = temp;
        }
        else
        {
            temp->next = position;
            prev->next = temp;
        }
    }

    position = NULL;
    prev = NULL;
    temp = NULL;    

    if (debugMode == 1)
    {
        printf("\n********CURRENTLY ON DEBUGGING MODE********\n");
        printf("Function Called : addRecord\n");
        printf("Account number: %d\n", accountNumber);
        printf("Name: %s\n", name);
        printf("Address: %s\n", address);
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name:  printAllRecords
//
//  DESCRIPTION:    Print all the records
//
//
//  Parameters:     start (struct *record) :  address of record
//
//  Return values:  No return value (void function)
//
//
****************************************************************/

void printAllRecords (struct record *start)
{
    int exist = -1; 
    struct record *temp = start;    
    
    while (temp != NULL)
    {
        printf("\nAccount Number: %d\n", temp->accountno);
        printf("Name: %s\n", temp->name);
        printf("Address: %s\n", temp->address);
        temp = temp->next;
        exist = 0;
    }

    temp = NULL;
 
    if (exist != 0)
    {
        printf("There's no record in the system\n");
    }

    if (debugMode == 1)
    {
        printf("\n********CURRENTLY ON DEBUGGING MODE********\n");
        printf("Function Called : printAllRecords\n");
        printf("No Parameter Passed\n");
        
    }


}

/*****************************************************************
//
//  Function name:  findRecord
//
//  DESCRIPTION:    Find the record based on the obtained account number
//
//
//  Parameters:     start (struct record*) : address of record
//                  accountNumber (int) : account number got from user
//
//  Return values:  0 : Succesffuly found record
//                 -1 : Fail to find record
//
****************************************************************/

int findRecord (struct record *start, int accountNumber)
{

    int returnVal = -1;
    struct record *temp = start;

    if (start == NULL)
    {
        returnVal = -1;
    }
    else
    {
        while (temp != NULL)
        {
            if (temp->accountno == accountNumber)
            {
                printf("\nAccount Number: %d\n", temp->accountno);
                printf("Name: %s\n", temp->name);
                printf("Address: %s\n", temp->address);
                returnVal = 0;
            }
            temp = temp->next;
        }
        
    }

    if (returnVal != 0)
    {
        printf("There's no record with account #: %d\n", accountNumber);
    }

    if (debugMode == 1)
    {
        printf("\n********CURRENTLY ON DEBUGGING MODE********\n");
        printf("Function Called : find\n");
        printf("Account number: %d\n", accountNumber);
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name:  deleteRecord
//
//  DESCRIPTION:    Get the user account number from user and delete
//                  corresponding record
//
//
//  Parameters:     pstart (struct record **): points address of the
//                                              record's location
//                  accountNumber (int) : account number got from user
//
//  Return values:  0 : Successfully deleted record
//                 -1 : Failed to delete record
//
//
****************************************************************/

int deleteRecord (struct record **pstart, int accountNumber)
{

    int returnVal;
    struct record *position = NULL;
    struct record *prev = NULL;
    struct record *temp = *pstart;

    if (*pstart == NULL)
    {
        returnVal = -1;
    }
    else
    {
        position = *pstart;
        while (position != NULL && position->accountno != accountNumber)
        {
            position = position->next;
        }
       
        if (position == NULL)
        {
            returnVal = -1;
        }
        else
        {
            if (position != *pstart)
            {
                prev = *pstart;
                while (prev->next != position)
                {
                    prev = prev->next;
                }
            }

            while (position != NULL && position->accountno == accountNumber)
            {
                temp = position;
                position = position->next;
                free(temp);
                returnVal = 0;
            }
            
            if (position == NULL && prev == NULL)
            {
                *pstart = NULL;
            }
            else if (position == NULL && prev != NULL)
            {
                prev->next = NULL;
            }
            else if (position != NULL && prev == NULL)
            {
                *pstart = position;
            }
            else
            {
                prev->next = position;
            }
           
            
        }
    }

    position = NULL;
    prev = NULL;
    temp = NULL;

    if (returnVal != 0)
    {
        printf("There's no record with account #: %d\n", accountNumber);
    }

    if (debugMode == 1)
    {
        printf("********CURRENTLY ON DEBUGGING MODE********\n");
        printf("Function Called : deleteRecord\n");
        printf("Account number: %d\n", accountNumber);
    }

    return returnVal;
}


/*****************************************************************
//
//  Function name:  readfile
//
//  DESCRIPTION:    When the program starts, read the text file and get the
//                  information from the file.
//
//
//  Parameters:     pstart (struct record **) : points the address
//                                               of the start address
//                  filename (char []) : the name of text file.
//
//  Return values:  0 : Succesfully read file
//                 -1 : Failed to read file
//
//
****************************************************************/

int readfile (struct record ** pstart, char filename[])
{

    int returnVal;
    FILE *fp;


    char name[25];
    int accountNum;

    char address[80];
    char tempAddr[80];
    char addr;    
    int addrCount;
    int done;

    returnVal = 0;
        
    
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        returnVal = -1;
    }
    else
    {
        if (ferror(fp) != 0)
        {
            returnVal = -1;
        }
    }

    
    if (returnVal != -1)
    {
        while (fscanf(fp, "%d\n", &accountNum) != EOF)
        {
            fscanf(fp, "%s\n", name);
            addrCount = 0;
            done = -1;
            memset(tempAddr, 0, sizeof(tempAddr));
            memset(address, 0, sizeof(address));
            while (done == -1)
            {
                addr = fgetc(fp);
                if (addr == '$')
                {
                    done = 0;
                }
                else if (addrCount == 80)
                {
                    done = 0;
                }
                else
                {
                    tempAddr[addrCount] = addr;
                }
                addrCount++;
            }
            strcpy(address, tempAddr);

            addRecord(pstart, accountNum, name, address);
            
        }
        
        fclose(fp);
    }




    if (debugMode == 1)
    {
        printf("\n********CURRENTLY ON DEBUGGING MODE********\n");
        printf("Function Called : readfile\n");
        printf("Filename: %s\n", filename);

    }

    return returnVal;

}

/*****************************************************************
//
//  Function name:  wrtiefile
//
//  DESCRIPTION:    When the program exits, read the list and copy to the text file
//                  and save it into text file.
//                  
//
//
//  Parameters:     start (struct record *) : points to the start of the heap list
//                  filename (char []) : the name of text file.
//
//  Return values:  0 : Successfully wrote file
//                 -1 : Failed to write file
//
//
****************************************************************/

int writefile (struct record *start, char filename[])
{
    
    int returnVal;
    struct record *temp;
    FILE *fp;
    
    temp = NULL;
    returnVal = 0;
    temp = start;
    fp = fopen(filename, "w");
    
    if (fp == NULL)
    {
        returnVal = -1;
    }
    else
    {
        if (ferror(fp) != 0)
        {
            returnVal = -1;
        }
    }
    
    if (returnVal != -1)
    {
        while (temp != NULL)
        {
            fprintf(fp, "%d\n", temp->accountno);
            fprintf(fp, "%s\n", temp->name);
            fprintf(fp, "%s", temp->address);
            fputs("$\n", fp);
            temp = temp->next;
        }
 

        fclose(fp);

    }

    if (debugMode == 1)
    {
        printf("\n********CURRENTLY ON DEBUGGING MODE********\n");
        printf("Function Called : writefile\n");
        printf("Filename: %s\n", filename);

    }


    return returnVal;
}

/*****************************************************************
//
//  Function name:  cleanup
//
//  DESCRIPTION:    From the user, obtain account number, name, and address
//                  then add a record for the user
//
//
//  Parameters:     pstart (struct record **) : points the address
//                                             of the record's address
//
//  Return values:  No return value (void function)
//
//
****************************************************************/

void cleanup (struct record **pstart)
{
    struct record *position = NULL;
    struct record *temp = NULL;

    temp = *pstart; 
    
    if (temp != NULL)
    {
        position = temp->next;    
        free(temp);
        temp = position;
    }

    temp = NULL;
    position = NULL;
    *pstart = NULL;
    
    if (debugMode == 1)
    {
        printf("\n********CURRENTLY ON DEBUGGING MODE********\n");
        printf("Function Called : cleanup\n");
        printf("No Parameter Passed\n");

    }
  
}

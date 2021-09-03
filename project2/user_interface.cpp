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

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

#include "llist.h"

void getAddress(char[], int);

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

    int quit = -1;
    int validChoice = -1;
    int validNum = -1;

    char userInput[20];
    
    int accountNum = -1;

    int onlyWhiteSpace;
    char name[25];

    char address[80];    
    


    llist mylist;

    
    #ifdef DEBUGMODE

        cout << "\n             **************** DUBEG MODE ****************\n\n";

    #endif


    while (quit == -1)
    {
        cout << "\n***********************  ICS 212 Banking System  ***********************\n";
        cout << "               Please choose an option from the menu below\n";
        cout << "=========================================================================\n\n";
        cout << "Add: Add a new record in the databse\n";
        cout << "Printall: Print all records in the databse\n";
        cout << "Find: Find record(s) with a specific account number\n";
        cout << "Delete: Delete existing record(s) from the database using account number\n";
        cout << "Quit: Quit the banking system\n\n";
        cout << "=========================================================================\n";
        
        validChoice = -1;
    
        cin.getline(userInput, 20, '\n');
        
        while (validChoice == -1)
        {


            if(strncmp(userInput, "add", strlen(userInput)) == 0)
            {
                validChoice = 0;
                validNum = -1;
 
                cout << "\nAdd a new record in the database.\n";
                cout << "Please enter an account number: \n";

                while (validNum == -1)
                {
                    cin >> accountNum;
  
                    if (!cin || accountNum <= 0)
                    {
                        cout << "The account number must be a positive integer.\n";
                        cout << "Please enter a valid account number\n";

                        cin.clear();
                        cin.ignore(100, '\n');
                    }
                    else
                    {
                        validNum = 0;
                    }
                }

                cin.clear();
                cin.ignore(100, '\n');

                cout << "Please enter a name.\n";

                onlyWhiteSpace = -1;
                while (onlyWhiteSpace == -1)
                {
                    cin.getline(name, 25, '\n');
                    name[strlen(name)] = '\0';

                    if (strstr(name, "\t") == NULL && strstr(name, "\n") == NULL)
                    {
                        onlyWhiteSpace = 0;
                    }
                    else
                    {
                        cout << "We do not accept any tab or new line character. \n";
                        cout << "Please enter a name\n";
                    }
                }


                cout << "Please enter an address.\n"; 
                memset(address, 0, 80);
                getAddress(address, 80);

                cout << "--------------------- RESULT ---------------------\n";
                if (mylist.addRecord(accountNum, name, address) != 0)
                {
                    cout << "Failed to add a new record.\n";
                }
                else
                {
                    cout << "Successfully added a new record on the database. \n\n";
                    cout << "Account Number: " << accountNum << "\n";
                    cout << "Name: " << name << "\n";
                    cout << "Address: " << address << "\n";
                }
                

            }
            else if(strncmp(userInput, "printall", strlen(userInput)) == 0)
            {
                validChoice = 0;
                cout << "Print all records in the database\n";
                cout << "--------------------- RESULT ---------------------\n";
                cout << mylist;

            }
            else if(strncmp(userInput, "find", strlen(userInput)) == 0)
            {
                validChoice = 0;
                validNum = -1;

                cout << "Please enter a account number that you want to find.\n";
                
                while (validNum == -1)
                {
                    cin >> accountNum;

                    if (!cin || accountNum <= 0)
                    {
                        cout << "The account number must be a positive integer.\n";
                        cout << "Please enter a valid account number\n";

                        cin.clear();
                        cin.ignore(100, '\n');
                    }
                    else
                    {
                        validNum = 0;
                    }
                }

                cin.clear();
                cin.ignore(100, '\n');                
              
                cout << "--------------------- RESULT ---------------------\n";
                mylist.findRecord(accountNum);
                
            }
            else if(strncmp(userInput, "delete", strlen(userInput)) == 0)
            {
                validChoice = 0;
                validNum = -1;

                cout << "Please enter a account number that you want to delete.\n";
 
                while (validNum == -1)
                {
                    cin >> accountNum;

                    if (!cin || accountNum <= 0)
                    {
                        cout << "The account number must be a positive integer.\n";
                        cout << "Please enter a valid account number\n";

                        cin.clear();
                        cin.ignore(100, '\n');
                    }
                    else
                    {
                        validNum = 0;
                    }
                }

                cin.clear();
                cin.ignore(100, '\n');

                cout << "--------------------- RESULT ---------------------\n";
                if (mylist.deleteRecord(accountNum) == 0)
                {
                    cout << "Successfully deleted record(s) with account #: " << accountNum << "\n";
                }

            }
            else if(strncmp(userInput, "quit", strlen(userInput)) == 0)
            {
                validChoice = 0;

                cout << "\nQuit the system.\n";
                quit = 0;
                
            }
            else
            {
                cout << "Eneterd a invalid input. Please enter a valid word, or alphabet.\n";
                cout << "If you've enterd a captial letter, please enter a lower case letter.\n";
                cout << "If you've entera a space, please remove the space\n";
               
                cin.getline(userInput, 20, '\n');

            }
        }
    }

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

void getAddress(char address[], int size)
{

    char addr;
    char tempAddress[80];
    int done = -1;
    int count = 0;
 
    memset(address, 0, 80);
    memset(tempAddress, 0, 80);

    cout << "Please enter your address (max 79 characters).\n";
    cout << "When you are done, please enter $ at the end.\n";
    
    while (done == -1)
    {
        addr = cin.get();
        if (addr == '$')
        {
            done = 0;
           
        }
        else if (count == size)
        {
            done = 0;
        }
        else
        {
            address[count] = addr;
        }
        count++;
    }   

    //strcpy(address, tempAddress);
    address[79] = '\0';

    cin.clear();
    cin.ignore(100, '\n');

    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: getAddress" << endl;
        cout << "Address: " << address << endl;
        cout << "Size: " << size <<endl;
        cout << "===========================================\n";

    #endif


}

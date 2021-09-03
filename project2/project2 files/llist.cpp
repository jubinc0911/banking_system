/*****************************************************************
//
//  NAME:        Ju-Bin Choi
//
//  HOMEWORK:    project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        Oct 26. 2020
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file contains various functions that is used in 
//   the banking system. 
//
//
****************************************************************/

#include "llist.h"

#include <string.h>
#include <stdlib.h>
#include <fstream>



/*****************************************************************
//
//  Function name:  llist
//
//  DESCRIPTION:    Constructor that construct a linked list with
//                  without a filename parameter.
//                  (the filename is decided in this function)
//
//
//  Parameters:     None
//
//  Return values:  None
//
****************************************************************/

llist::llist()
{

    start = NULL;

    strcpy(filename, "record.txt");

    readfile();

    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========\n";
        cout << "Function Called: llist (Constructor)\n";
        cout << "===========================================\n";

    #endif
}



/*****************************************************************
//
//  Function name:  llist
//
//  DESCRIPTION:    Constructor that construct a linked list with
//                  a filename parameter.
//                  The filename will be changed to the given filename
//
//
//  Parameters:     newFileName (char []) : new file name of the list
//
//  Return values:  None
//
//
****************************************************************/

llist::llist(char newFileName[])
{

    start = NULL;
    
    strcpy(filename, newFileName);
    readfile();

    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========\n";
        cout << "Function Called: llist (Constructor)\n";
        cout << "New filenmae: " << newFileName << endl;
        cout << "===========================================\n";

    #endif

}

/*****************************************************************
//
//  Function name:  ~llist
//
//  DESCRIPTION:    Destructor that will be called at the end of the
//                  main function. It will destory the linked list and
//                  write a file with a given filename
//
//
//  Parameters:     None
//
//  Return values:  None
//
//
****************************************************************/

llist::~llist()
{

    if (start != NULL)
    {
        #ifdef DEBUGMODE

            cout << "\n========CURRENTLY ON DEBUGGING MODE========\n";
            cout << "Function Called: ~llist (Destructor)\n";
            cout << "===========================================\n";

        #endif            
    
        writefile();

        cleanup();
    }
}



/*****************************************************************
//
//  Function name:  addRecord
//
//  DESCRIPTION:    From the user, obtain account number, name, and address
//                  then add a record for the user
//
//
//  Parameters:     accountNumber (int) : account number got from user
//                  name (char []) : name of the user
//                  address (char []) : address of the user
//
//  Return values:  0 : add successfully
//                 -1 : fail to add record
//
//
****************************************************************/

int llist::addRecord(int accountNumber, char name[], char address[])
{

    int returnVal = -1;
    struct record *position = NULL;
    struct record *prev = NULL;
    struct record *temp = NULL;

    temp = new struct record();

    temp->accountno = accountNumber;
    strcpy(temp->name, name);
    strcpy(temp->address, address);
    temp->next = NULL;

    if (start == NULL)
    {
        start = temp;

        returnVal = 0;
    }
    else
    {
        position = start;
        
        while (position != NULL && position->accountno > accountNumber)
        {
            position = position->next;
        }
     
        prev = start;
        while (position != start && prev->next != position)
        {
            prev = prev->next;
        }

        if (position == start)
        {
            temp->next = position;
            start = temp;
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
        
        returnVal = 0;
    }


    position = NULL;
    prev = NULL;
    temp = NULL;

    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: addRecord" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "============================================\n";

    #endif

    return returnVal;

}

/*****************************************************************
//
//  Function name:  findRecord
//
//  DESCRIPTION:    Find the record based on the obtained account number
//
//
//  Parameters:     accountNumber (int) : account number got from user
//
//  Return values:  0 : Succesffuly found record
//                 -1 : Fail to find record
//
****************************************************************/

int llist::findRecord(int accountNumber)
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
                cout << "\nAccount Number: " << temp->accountno << "\n";
                cout << "Name: " << temp->name << "\n";
                cout << "Address: " << temp->address << "\n";
                returnVal = 0;
            }
        
            temp = temp->next;
        }
    }

    if (returnVal != 0)
    {
        cout << "There's no record with account #: " << accountNumber << "\n";
    }

    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: findRecord" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "============================================\n";

    #endif


    return returnVal;

}

/*****************************************************************
//
//  Function name:  operator<<  (printall)
//
//  DESCRIPTION:    Print all the records
//
//
//  Parameters:     os (ostream&): pointer to ostream
//                  llist (const llist&): address of the llist
//
//  Return values:  No return value (void function)
//
//
****************************************************************/

ostream& operator<<(ostream& os, const llist& mylist)
{

    int exit;
    record *temp;
   
    temp = mylist.start;
    exit = -1;
    while (temp != NULL)
    {
        os << "\nAccount Number: " << temp->accountno << "\n";
        os << "Name: " << temp->name << "\n";
        os << "Address: " << temp->address << "\n";
        temp = temp->next;
        exit = 0;
    }

    temp = NULL;

    if (exit != 0)
    {
        os << "There's no record in the system.\n";
    }

    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========\n";
        cout << "Function Called: operator<< (printAll)\n";
        cout << "===========================================\n";

    #endif


    return os;

}
/*****************************************************************
//
//  Function name:  deleteRecord
//
//  DESCRIPTION:    Get the user account number from user and delete
//                  corresponding record(s)
//
//
//  Parameters:     accountNumber (int) : account number got from user
//
//  Return values:  0 : Successfully deleted record
//                 -1 : Failed to delete record
//
//
****************************************************************/

int llist::deleteRecord(int accountNumber)
{

    int returnVal;
    struct record *position = NULL;
    struct record *prev = NULL;
    struct record *temp = start;

    if (start == NULL)
    {
        returnVal = -1;
    }
    else
    {
        position = start;
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
            if (position != start)
            {
                prev = start;
                while (prev->next != position)
                {
                    prev = prev->next;
                }
            }

            while (position != NULL && position->accountno == accountNumber)
            {
                temp = position;
                position = position->next;
                delete(temp);
                returnVal = 0;
            }

            if (position == NULL && prev == NULL)
            {
                start = NULL;
            }
            else if (position == NULL && prev != NULL)
            {
                prev->next = NULL;
            }
            else if (position != NULL && prev == NULL)
            {
                start = position;
            }
            else
            {
                prev->next = position;
            }
        }
    }

    if (returnVal != 0)
    {
        cout << "There's no record with account #: " << accountNumber << "\n";
    }    


    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: deleteRecord" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "===========================================\n";

    #endif

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
//  Parameters:     None
//
//  Return values:  0 : Succesfully read file
//                 -1 : Failed to read file
//
//
****************************************************************/

int llist::readfile()
{

    int returnVal = -1;

    ifstream read;

    char name[25];
    string line;
  
    int accountNum;

    char address[80];
    char addr;
    int addrCount = 0;
    int done;

    read.open(filename);
    

    if (!read.is_open())
    {
        returnVal = -1;
        cout << "file not opened " << endl;
    }
    else
    {
        returnVal = 0;
    }

    if (returnVal != -1)
    {

        while (read >> accountNum)
        {

            getline(read, line);

            getline(read, line);
            strcpy(name, line.c_str());
                       
            memset(address, 0, 80);
       
            addrCount = 0;
            done = -1;
            while (done == -1)
            {
                addr = read.get();
           
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
                    address[addrCount] = addr;
                }
                addrCount++;
            }
            addRecord(accountNum, name, address);
                
        }
        if (!read)
        {
            read.clear();
            read.ignore(100, '\n');
        }
    
    }
    read.close();


    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: readfile" << endl;
        cout << "===========================================\n";

    #endif
    
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
//  Parameters:     None
//
//
//  Return values:  0 : Successfully wrote file
//                 -1 : Failed to write file
//
//
****************************************************************/

int llist::writefile()
{
    
    int returnVal = -1;
    
    struct record *temp;
    ofstream fout;

    temp = start;

    fout.open(filename);

    if (fout != NULL)
    {


        returnVal = 0;
        
        while (temp != NULL)
        {
            fout << temp->accountno << "\n";
            fout << temp->name << "\n";
            fout << temp->address;
            fout << "$\n";

            temp = temp->next;
        }
    
  
        fout.close();
    

    }

    fout.close();
    
    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: writefile" << endl;
        cout << "===========================================\n";

    #endif

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
//  Parameters:     None
//
//  Return values:  No return value (void function)
//
//
****************************************************************/

void llist::cleanup()
{

    struct record *position;
    struct record *temp;

    temp = start;

    while (temp != NULL)
    {
        position = temp->next;
        delete(temp);
        temp = position;
    }

    temp = NULL;
    position = NULL;
    start = NULL;


    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: cleanup" << endl;
        cout << "===========================================\n";

    #endif   

}

/*****************************************************************
//
//  Function name:  operator=  (overload assignment)
//
//  DESCRIPTION:    The overloading assignmnet operator copies the
//                  information from the linked list to a pre-existed
//                  linked list. (Not making a new list)
//
//
//  Parameters:     mylist (const llist&): reference of the initial list
//
//  Return values:  *this : pointer to the copied list
//
//
****************************************************************/

llist& llist::operator=(const llist& mylist)
{

    struct record *temp;



    strcpy(this->filename, mylist.filename);
   
    temp = mylist.start;

    this->cleanup();

    if (temp == NULL)
    {
        this->start = NULL;
    }
    else
    {
        this->start  = new struct record();

        this->start->accountno = temp->accountno;
        strcpy(this->start->name, temp->name);
        strcpy(this->start->address, temp->address);
        this->start->next = NULL;

        if (temp->next != NULL)
        {
            temp = temp->next;

            while (temp != NULL)
            {
                this->addRecord(temp->accountno, temp->name, temp->address);
                temp = temp->next;
            }


        }

    }
    

    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: operator=" << endl;
        cout << "===========================================\n";

    #endif

    return *this;

}


/*****************************************************************
//
//  Function name:  copy constructor
//
//  DESCRIPTION:    The copy constructor that copies the linked
//                  list by making a new list.
//
//
//  Parameters:     llist (const llist&): reference of the initial list
//
//  Return values:  No return value (void function)
//
//
****************************************************************/

llist::llist (const llist& oldlist)
{

    struct record *temp;
    
    this->start = NULL;
    strcpy(this->filename, oldlist.filename);


    temp = oldlist.start;
 
    if (temp == NULL)
    {
        this->start = NULL;
    }
    else
    {
        while (temp != NULL)
        {
            this->addRecord(temp->accountno, temp->name, temp->address);
            temp = temp->next;
        }
           
    }


    #ifdef DEBUGMODE

        cout << "\n========CURRENTLY ON DEBUGGING MODE========" << endl;
        cout << "Function Called: Copy Constructor" << endl;
        cout << "===========================================\n";

    #endif    

}

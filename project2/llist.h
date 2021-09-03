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
//  DATE:        November 24, 2020
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   A header file contains prototypes for functions and
//   and some elements.
//
****************************************************************/

#include "record.h"
#include <iostream>

using namespace std;

class llist
{
    private:
        record *    start;
        char        filename[16];
        int         readfile();
        int         writefile();
        void        cleanup();

    public:
        llist();
        llist(char[]);
        ~llist();
        int addRecord(int, char [ ],char [ ]);
        int findRecord(int);
        int deleteRecord(int);
        friend ostream& operator<<(ostream&, const llist&);
        llist& operator= (const llist&);
        llist(const llist&);
};


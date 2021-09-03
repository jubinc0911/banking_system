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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the variables that are used to operate
//   the banking system.  
//
//
****************************************************************/


struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};


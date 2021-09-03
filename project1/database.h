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
//  DATE:        Oct 26, 2020
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   This header file contains the functions that will be used to
//   complete the banking system. And, it will be implemented
//   in the future assignment.
//
//
****************************************************************/

#include "record.h"

int addRecord(struct record **, int, char [ ],char [ ]);
void printAllRecords(struct record *);
int findRecord (struct record *, int);
int deleteRecord(struct record **, int);
int readfile(struct record **, char[]);
int writefile(struct record *, char[]);
void cleanup(struct record **);

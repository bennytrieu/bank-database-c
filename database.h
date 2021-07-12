/****************************************************************
//
//  NAME:        Benny Trieu
//
//  HOMEWORK:    Project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 1st, 2020
//
//  FILE:        database.h
//
//  DESCRIPTION:
//  The header file for database.
//
****************************************************************/

#ifndef DATABASE_H
#define DATABASE_H
int addRecord(struct record **, int, char[], char[]);
void printAllRecords(struct record *);
int findRecord(struct record *, int);
int deleteRecord(struct record **, int);
int readfile(struct record **, char[]);
int writefile(struct record *, char[]);
void cleanup(struct record **);
#endif

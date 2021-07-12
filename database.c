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
//  FILE:        database.c
//
//  DESCRIPTION:
//  The database for the bank
//
****************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"record.h"
extern int debugmode;

/***************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record of an account, name, and address
//                 
//  Parameters:    addressofstart (struct record **) : Contains 
//                 the structure address of a record named 
//                 addressofstart
//                 uacc (int): Contains the account #
//                 uname (char[]): Contains the name
//                 uaddress (char[]): Contains the address
//
//  Return values:  0 : gives it the all clear
//
****************************************************************/

int addRecord(struct record ** addressofstart, int uacc, char uname[], char uaddress[])
{
    struct record * temp;
    struct record * prevrecord;
    struct record * input;
    int button = 1;
    int lone = 0;
    temp = NULL;
    prevrecord = NULL;
    input = (struct record*)malloc(sizeof(struct record));
    (*input).accountno = uacc;
    strcpy((*input).name, uname);
    strcpy((*input).address, uaddress);
    (*input).next = NULL;
    if (debugmode == 1)
    {
        printf("*****ADD: ADDRESSOFSTART IS PASSED*****\n");
        printf("*****ADD: %d IS PASSED*****\n", uacc);
        printf("*****ADD: %s IS PASSED*****\n", uname);
        printf("*****ADD: %s IS PASSED*****\n", uaddress);
    }
    if (*addressofstart == NULL)
    {
        (*addressofstart) = input;
    }
    else
    {
        temp = (*addressofstart);
        if (((*temp).next == NULL) && (uacc < (*temp).accountno))
        {
            (*temp).next = input;
            temp = NULL;
            lone++;
        }
        else if (((*temp).next == NULL) && (uacc >= (*temp).accountno))
        {
            (*input).next = temp;
            (*addressofstart) = input;
            temp = NULL;
            lone++;
        }
        else
        {
            while (temp != NULL)
            {
                if (uacc >= (*temp).accountno)
                {
                    if ((*addressofstart) == temp)
                    {
                        (*input).next = (*addressofstart);
                        (*addressofstart) = input;
                        temp = NULL;
                        button = 0;
                        lone++;
                    }
                    else if ((*addressofstart) != temp)
                    {
                        (*input).next = (*prevrecord).next;
                        (*prevrecord).next = input;
                        temp = NULL;
                        prevrecord = NULL;
                        button = 0;
                        lone++;
                    }
                }
                button++;
                if (prevrecord != NULL)
                {
                    prevrecord = (*prevrecord).next;
                    temp = (*temp).next;
                }
                if (button == 2)
                {
                    prevrecord = (*addressofstart);
                    temp = (*temp).next;
                }
                if ((temp == NULL) && (lone == 0))
                {
                    (*prevrecord).next = input;
                    lone++;
                }
            }
        }
    }
    return 0;
}

/****************************************************************
//
//  Function name: printAllRecords
// 
//  DESCRIPTION:   Prints all the records.
// 
//  Parameters:    start (struct record *) : Contains the structure
//                 of a record named start
//                  
//  Return values:  none
// 
****************************************************************/

void printAllRecords(struct record * start)
{
    if (debugmode == 1)
    {
        printf("*****PRINTALLRECORDS: START IS PASSED*****\n");
    }
    if (start == NULL)
    {
        printf("there are no records at the moment\n");
    }
    else
    {
        while (start != NULL)
        {
            printf("accountno:%d\n", (*start).accountno);
            printf("name:%s", (*start).name);
            printf("address:%s\n\n", (*start).address);
            start = (*start).next;
        }
    }
}

/****************************************************************
//
//  Function name: findRecord
//  
//  DESCRIPTION:   Finds the record using an account #
//  
//  Parameters:    start (struct record *) : Contains the structure
//                 of a record named start
//                 acc (int) : Contains the account #
//                  
//  Return values:  status : determines what return to give
//                  0 means all clear. -1 means it failed.
//  
****************************************************************/

int findRecord(struct record * start, int acc)
{
    int find;
    int status;
    status = 0;

    if (debugmode == 1)
    {
        printf("*****FINDRECORD: START IS PASSED*****\n");
        printf("*****FINDRECORD: %d IS PASSED*****\n", acc);
    }

    while (start != NULL)
    {
        if (acc == (*start).accountno)
        {
            printf("account #%d has been found\n", acc);
            printf("accountno:%d\n", (*start).accountno);
            printf("name:%s", (*start).name);
            printf("address:%s\n\n", (*start).address);
            find++;
        }
        start = (*start).next;
    }
    if (find == 0)
    {
        printf("account #%d has not been found\n", acc);
        status = -1;
    }
    return status;
}

/****************************************************************
//
//  Function name: deleteRecord
//  
//  DESCRIPTION:   Deletes the record using an account #
//  
//  Parameters:    addressofstart (struct record **) : Contains
//                 the structure address of a record named 
//                 addressofstart
//                 acc (int) : Contains the account #
//                  
//  Return values:  status: return value that determines how
//                  the program ran.
//                  0 means its all clear and -1 means it failed
//  
****************************************************************/

int deleteRecord(struct record ** addressofstart, int acc)
{
    struct record * temp;
    struct record * prevrecord;
    int status, button, find;

    prevrecord = NULL;
    button = 1;
    find = 0;
    status = 0;

    if (*addressofstart == NULL)
    {
        status = -1;
    }
    else
    {
        temp = (*addressofstart);
        while (temp != NULL)
        {
            if ((*temp).accountno == acc)
            {
                if ((temp == (*addressofstart)) && (button == 1))
                {
                    *addressofstart = (**addressofstart).next;
                    free(temp);
                    temp = (*addressofstart);
                    button = 0;
                    find++;
                }
                else if (*addressofstart != temp)
                {
                    while ((*temp).accountno == acc)
                    {
                        (*prevrecord).next = (*temp).next;
                        free(temp);
                        temp = (*prevrecord).next;
                        find++;
                        if (temp == NULL)
                        {
                            temp = prevrecord;
                        }
                    }
                }
            }
            button++;
            if ((temp == NULL) && (prevrecord != NULL))
            {
                prevrecord = NULL;
            }
            if (prevrecord != NULL)
            {
                prevrecord = (*prevrecord).next;
                if (temp != NULL)
                {
                    temp = (*temp).next;
                }
            }
            if (button == 2)
            {
                prevrecord = *addressofstart;
                temp = (*temp).next;
            }
        }
        if (find == 0)
        {
            status = -1;
            printf("Could not find account #%d\n", acc);
        }
        else if (find >= 0)
        {
            printf("account #%d has been deleted\n", acc);
        }
    }
    if (debugmode == 1)
    {
        printf("*****DELETERECORD: ADDRESSOFSTART IS PASSED*****\n");
        printf("*****DELETERECORD: %d IS PASSED*****\n", acc);
    }
    return status;
}

/****************************************************************
//
//  Function name: readfile
//  
//  DESCRIPTION:   Reads the file and loads in the bank's 
//                 database
//  
//  Parameters:    pbegin (struct record **) : Contains the structure
//                 address of a record named pbegin
//                 loadfile (char[]) : the file that will contain
//                 the database of the bank
// 
//  Return values:  status: determines the return value of the program
//                  0 means its all clear and -1 means it failed
//  
//  ****************************************************************/

int readfile(struct record ** pbegin, char loadfile[])
{
    struct record * load;
    struct record * temp;
    char input[100];
    int number;
    int status;
    FILE *fp;

    if (debugmode == 1)
    {
        printf("*****READFILE: PBEGIN IS PASSED*****\n");
        printf("*****READFILE: %s IS PASSED*****\n", loadfile);
    }
    temp = NULL;
    status = 0;

    fp = fopen(loadfile, "r");
    if (fp == NULL)
    {
        status = -1;
    }
    else
    {
        while (!feof(fp))
        {
            load = (struct record*)malloc(sizeof(struct record));
            fgets(input, 100, fp);
            number = atoi(input);
            (*load).accountno = number;
            fgets(input, 100, fp);
            strcpy((*load).name, input);
            fgets(input, 100, fp);
            strcpy((*load).address, input);
            (*load).next = NULL;
            if ((*pbegin) == NULL)
            {
                (*pbegin) = load;
                if ((*load).accountno <= 0)
                {
                    temp = (*pbegin);
                    (*pbegin) = NULL;
                    free(temp);
                    temp = NULL;
                }
            }
            else
            {
                if (temp == NULL)
                {
                    temp = (*pbegin);
                }
                (*temp).next = load;
                if ((*load).accountno <= 0)
                {
                    free((*temp).next);
                    (*temp).next = NULL;
                }
                temp = (*temp).next;
            }
        }
        fclose(fp);
    }
    return status;
}

/****************************************************************
//
//  Function name: writefile
// 
//  DESCRIPTION:   writes into the file and saves the bank's
//                 database
//  
//  Parameters:    begin (struct record *) : Contains the structure
//                 address of a record named begin
//                 loadfile (char[]) : the file that will store
//                 the data of the bank
//  
//  Return values:  0: it means all clear
//  
****************************************************************/

int writefile(struct record * begin, char loadfile[])
{
    FILE *fp;
    if (debugmode == 1)
    {
        printf("*****WRITEFILE: BEGIN IS PASSED*****\n");
        printf("*****WRITEFILE: %s IS PASSED*****\n", loadfile);
    }
    fp = fopen(loadfile, "w");
    while (begin != NULL)
    {
        fprintf(fp, "%d\n", (*begin).accountno);
        fprintf(fp, "%s", (*begin).name);
        fprintf(fp, "%s", (*begin).address);
        begin = (*begin).next;
    }
    fclose(fp);
    return 0;
}

/****************************************************************
//
//  Function name: cleanup
//  
//  DESCRIPTION:   cleans up the heap
//              
//  
//  Parameters:    begin (struct record **) : Contains the structure
//                 address of a record named begin
//  
//  Return values: none
//  
//  ****************************************************************/

void cleanup(struct record ** begin)
{
    struct record * temp;
    struct record * prev;
    int status = 1;
    if (debugmode == 1)
    {
        printf("*****CLEANUP: BEGIN IS PASSED*****\n");
    }
    while (status == 1)
    {
        if (*begin == NULL)
        {
            status = 0;
        }
        else
        {
            temp = (*begin);
            if ((*temp).next == NULL)
            {
                free(temp);
                (*begin) = NULL;
                status = 0;
            }
            else
            {
                while (temp != NULL)
                {
                    prev = temp;
                    temp = (*temp).next;
                    free(prev);
                }
                status = 0;
                (*begin) = NULL;
            }
        }
    }
}

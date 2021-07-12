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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//  A user interface that displays the menu options for the
//  bank at the user's convenience
//
****************************************************************/

#include<stdio.h>
#include<string.h>
#include"record.h"
#include"database.h"
void menu();
int userinterface();
void getaddress(char[], int);
int debugmode = 0;

/****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main hub of the code that helps run 
//                 the user interface for the bank.
//                 
//  Parameters:    argc (int) : contains the number of arguments
//                              inputted into the c file
//                 argv[] (char*): stores the arguments
//
//  Return values:  0 : tells the code its all good
//                 
//
****************************************************************/

int main(int argc, char *argv[])
{
    struct record * start = NULL;
    int transfer, lever, status, acc, condition, value, state, fin, position, num, numtrash, button;
    char letters[100];
    char name[100];
    char garbage[100];
    char address[80];
    char garb[100];
    char waste[100];
    char trash[100];
    lever = 0;
    transfer = 0;
    status = 1;
    condition = 1;
    state = 1;
    position = 1;
    button = 1;
    if (argc == 2)
    {
        if (strcmp(argv[1], "debug") != 0)
        {
            printf("*****NOT ALLOWED****\n");
            lever = 1;
        }
        else if (strcmp(argv[1], "debug") == 0)
        {
            debugmode = 1;
            printf("*****DEBUG MODE ON*****\n");
            printf("Hello welcome to the bank\n\n");
            readfile(&start, "loadfile.txt");
            menu();
        }
    }
    if (argc > 2)
    {
        printf("*****NOT ALLOWED****\n");
        lever = 1;
    }
    else if (argc == 1)
    {
        printf("Hello welcome to the bank\n\n");
        readfile(&start, "loadfile.txt");
        menu();
    }
    while (lever == 0)
    {
        status = 1;
        if (fgets(letters, 100, stdin))
        {
            value = strlen(letters);
            if (strncmp (letters, "add", value-1) == 0 || strncmp (letters, "Add", value-1) == 0)
            {
                printf("Add has been chosen\n");
                printf("account #:");
                do
                {
                    int scanner = scanf("%d", &acc);
                    if (scanner == 1)
                    {
                        if (acc <= 0)
                        {
                            printf("not a valid number, try again:");
                        }
                        else
                        {
                            condition = 0;
                        }
                    }
                    else if (scanner != 1)
                    {
                        if (fgets(garbage, 100, stdin))
                        {
                            printf("not a number. Try again:");
                        }
                    }
                }
                while (condition == 1);
                printf("name:");
                fgets(garb, 100, stdin);
                do
                {
                    int exam = scanf("%d", &numtrash);
                    if (exam !=1)
                    {
                        if (fgets(name, 100, stdin))
                        {
                            button = 0;
                        }
                    }
                    else if (exam == 1)
                    {
                        printf("not a valid name. Try again:");
                    }
                }
                while (button == 1);
                printf("address(80 characters max)(press 'enter' and then press '!' when done):");
                getaddress(address, transfer);
                printf("account #:%d\nname:%saddress:%s\n", acc, name, address);
                addRecord(&start, acc, name, address);
                printf("Welcome back to the menu\n\n");
                menu();
                fgets(letters, 100, stdin);
                status = 2;
            }
            if (strncmp (letters, "printall", value-1) == 0 ||
                strncmp(letters, "Printall", value-1) == 0)
            {
                printf("Here are all the records:\n\n");
                printAllRecords(start);
                printf("Welcome back\n\n");
                menu();
                status = 2;
            }
            if (strncmp (letters, "find", value-1) == 0 || strncmp (letters, "Find", value-1) == 0)
            {
                printf("Find has been chosen\n");
                printf("what account # would you like to find:");
                do
                {
                    int number = scanf("%d", &fin);
                    if (number == 1)
                    {
                        if (fin <=0)
                        {
                            printf("not a valid number, try again:");
                        }
                        else
                        {
                            printf("searching for account #%d\n\n", fin);
                            state = 0;
                        }
                    }
                    else if (number != 1)
                    {
                        if (fgets(waste, 100, stdin))
                        {
                            printf("not a number. Try again:");
                        }
                    }
                }
                while (state == 1);
                findRecord(start, fin);
                printf("Welcome back to the menu\n\n");
                menu();
                fgets(letters, 100, stdin);
                status = 2;
            }
            if (strncmp (letters, "delete", value-1) == 0 ||
                strncmp(letters, "Delete", value-1) == 0)
            {
                printf("Delete has been chosen\n");
                printf("what account # would you like to delete:");
                do
                {
                    int del = scanf("%d", &num);
                    if (del == 1)
                    {
                        if (num <= 0)
                        {
                            printf("not a valid number, try again:");
                        }
                        else
                        {
                            printf("attempting to delete account #%d\n\n", num);
                            position = 0;
                        }
                    }
                    else if (del != 1)
                    {
                        if (fgets(trash, 100, stdin))
                        {
                            printf("not a number. Try again:");
                        }
                    }
                }
                while (position == 1);
                deleteRecord(&start, num);
                printf("Welcome back to the menu\n\n");
                menu();
                fgets(letters, 100, stdin);
                status = 2;
            }
            if (strncmp (letters, "menu", value-1) == 0 || strncmp (letters, "Menu", value-1) == 0)
            {
                menu();
                status = 2;
            }
            if (strncmp (letters, "quit", value-1) == 0 || strncmp (letters, "Quit", value-1) == 0)
            {
                printf("Have a nice day :)\n");
                writefile(start, "loadfile.txt");
                cleanup(&start);
                lever = 1;
                status = 2;
            }
            else if (status == 1)
            {
                printf("INVALID. Please try again:");
            }
        }
    }
    return 0;
}

/****************************************************************
//  
//  Function name: menu
// 
//  DESCRIPTION:   Prints the options given and prompts the user
//                 to choose an option
//  
//  Parameters:    none
//                         
//  Return values: none
//    
****************************************************************/

void menu()
{
    if (debugmode == 1)
    {
        printf("*****MENU HAS BEEN CALLED*****\n");
    }
    printf("Here are your options\n\n");
    printf("add:             Add a new record in the database\n");
    printf("printall:        Print all records in the database\n");
    printf("find:            Find record(s) with a specified account #\n");
    printf("delete:          Delete existing record(s) from the database using the account #\n");
    printf("menu:            Brings up the options\n");
    printf("quit:            Quit the program\n\n");
    printf("Please choose an option:");
}

/****************************************************************
//
//  Function name: getaddress
// 
//  DESCRIPTION:   asks the user for their address
//                 press ! to be finished
//             
//  Parameters:    address (char[]): The array that holds the
//                 address for the user
//                 transfer (int): The integer that helps with
//                 fgetc
//  
//  Return values: none
//  
****************************************************************/

void getaddress(char address[], int transfer)
{
    int j = 0;
    memset(address, '\0', strlen(address));
    while ((transfer = fgetc(stdin)) != '!')
    {
        address[j] = transfer;
        j++;
    }
    if (debugmode == 1)
    {
        printf("*****GETADDRESS: %s IS PASSED*****\n", address);
        printf("*****GETADDRESS: %d IS PASSED*****\n", transfer);
    }
}

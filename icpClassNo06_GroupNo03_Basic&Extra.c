// --------------------
// include and define
// --------------------
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <windows.h>

#define PASSWORD "password"

// --------------------
// global variables
// --------------------
struct Book
{
    char title[100];
    char callNum[20];
    char subject[20];
    char author[100];
    char year[5];
    char status[20];
};

// --------------------
// function prototype
// --------------------
void addRecord();
void displayRecord();
void modifyRecord();
void deleteRecord();
void searchRecord();
int recordCount(FILE *);
void showBookData(struct Book);
void showTime();            // extra
void passwordAccess();      // extra
void borrowReturnBook();    // extra
void quitSystem();          // extra

// --------------------
// functions
// --------------------

// main
int main()
{
    // let user to enter the access code to use the system
    showTime();
    passwordAccess();
    
    while(1)    // infinite loop for menu
    {
        system("cls");  // clear screen
        fflush(stdin);
        showTime();
        printf("*** College Library Record System 201516 ***\n\n");
        printf("*** This system is developed by CCIT4020 Class No.CL-06 Group No.03 ***\n\n");
        printf("--(Basic function)--\n\n");
        printf("1. Add New Book Record(s)\n\n");
        printf("2. Display Book Record(s)\n\n");
        printf("3. Modify Book Record(s)\n\n");
        printf("4. Delete Book Record(s)\n\n");
        printf("5. Search Book Record(s)\n\n");
        printf("6. Borrow or Return Book(s)\n\n");
        printf("7. Close Application\n\n");
        printf("What is your option (1-7)? ");
        
        switch(getchar())
        {
            case '1':
                addRecord();
                break;
            case '2':
                displayRecord();
                break;
            case '3':
                modifyRecord();
                break;
            case '4':
                deleteRecord();
                break;
            case '5':
                searchRecord();
                break;
            case '6':
                borrowReturnBook();
                break;
            case '7':
                quitSystem();
                break;
            default: 
			    printf("\nWrong Entry!!Please re-entered correct option\n");
			    getchar();
        }
    }
    return 0;
}

// addRecord
void addRecord()
{
    // ----------------------------------------
    // declaring and initializing variables
    // ----------------------------------------
    FILE *fPtr = fopen("LibraryBook.txt", "a"); // open LibraryBook.txt
    struct Book newBook;
    int i, validCheck;
    char c;
    
    // ----------------------------------------
    // operating process
    // ----------------------------------------
    do
    {
        system("cls");   // clear sceen
        fflush(stdin);
        // getting the data of the new book
        printf("\nEnter the following information:\n");
        printf("Title: ");
        gets(newBook.title);
        newBook.title[99] = '\0';
        printf("Call number: ");
        gets(newBook.callNum);
        newBook.callNum[19] = '\0';
        printf("Subject: ");
        gets(newBook.subject);
        newBook.subject[19] = '\0';
        printf("Author: ");
        gets(newBook.author);
        newBook.author[99] = '\0';
        do
        {
            printf("Year of publishment: ");
            gets(newBook.year);
            newBook.year[4] = '\0';
            
            // validation process
            validCheck = 1;
            for(i = 0; i < 4; i++)
            {
                if(isdigit(newBook.year[i]) == 0)
                    validCheck = 0;
            }
            if(validCheck == 0)
                printf("Wrong year of publishment is entered!\nPlease enter again.\n");
        }while(validCheck == 0);
        do
        {
            printf("Status: ");
            gets(newBook.status);
            newBook.status[19] = '\0';
            // validation process
            validCheck = 0;
            if(strcmp(strlwr(newBook.status), "borrowed") == 0)
                validCheck = 1;
            if(strcmp(strlwr(newBook.status), "available") == 0)
                validCheck = 1;
            if(validCheck == 0)
                printf("Wrong Status is entered!\n"
                    "It can only be 'Borrowed' or 'Available'\n"
                    "Please enter again.\n");
        }while(validCheck == 0);
        newBook.status[0] = toupper(newBook.status[0]);
        
        // print it to the LibraryBook.txt
        fputs(newBook.title, fPtr);
		fputs("\n", fPtr);
		fputs(newBook.callNum, fPtr);
		fputs("\n", fPtr);
		fputs(newBook.subject, fPtr);
		fputs("\n", fPtr);
		fputs(newBook.author, fPtr);
		fputs("\n", fPtr);
		fputs(newBook.year, fPtr);
		fputs("\n", fPtr);
		fputs(newBook.status, fPtr);
		fputs("\n\n", fPtr);
		
		// asking the user to add another book or not
		printf("Do you want to add another book?(y/n) ");
		fflush(stdin);
		c = tolower(getchar());   // get the answer and turn it to lowercase
    }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
    
    fclose(fPtr);   // close LibraryBook.txt
}

// displayRecord
void displayRecord()
{
    // declaring and initializing variables
    FILE *fPtr = fopen("LibraryBook.txt", "r"); // open LibraryBook.txt
    int i, j, total, code;
    char c;
    
    // operating process
    system("cls");
	fflush(stdin);
	// check any data in LibraryBook.txt
	if(fPtr == NULL || fgetc(fPtr) == EOF)
	{
		printf("No data\nPress any key back to menu");
		getchar();
		return;
	}
	//getting book data from LibraryBook.txt
	total = recordCount(fPtr);
	struct Book records[total];
	fseek(fPtr, 0L, SEEK_SET);
    for(i = 0; i < total; i++)
	{
		fgets(records[i].title, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].title[j] == '\n')
                records[i].title[j] = '\0';
        }
		fgets(records[i].callNum, 21, fPtr);
		records[i].callNum[19] = '\0';
		for(j = 0; j < 19; j++)
		{
		    if(records[i].callNum[j] == '\n')
                records[i].callNum[j] = '\0';
        }
        fgets(records[i].subject, 21, fPtr);
		records[i].subject[19] = '\0';
		for(j = 0; j < 19; j++)
		{
		    if(records[i].subject[j] == '\n')
                records[i].subject[j] = '\0';
        }
		fgets(records[i].author, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].author[j] == '\n')
                records[i].author[j] = '\0';
        }
		fgets(records[i].year, 6, fPtr);
		records[i].year[4] = '\0';
		fgets(records[i].status, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].status[j] == '\n')
                records[i].status[j] = '\0';
        }
		fgetc(fPtr);
	}
	fclose(fPtr);   // close LibraryBook.txt
	
	do
	{
		system("cls");
		for(i = 0; i < total; i++)
		{
			printf("%d) %s\n", i+1, records[i].title);
		}
		// let user to select the book to show the details
		do
		{
		    fflush(stdin);
		    code = 0; // restore data in code
            printf("\nEnter the code of the book you want to display: ");
            scanf("%d", &code);
            if(code < 1 || code > total)    // for validation
                printf("Wrong range of code!\nPlease enter again.");
		}while(code < 1 || code > total);
		
		showBookData(records[code - 1]);  // display the data of the selected book
		
		// asking the user to display another book or not
		printf("Do you want to display another book?(y/n) ");
		fflush(stdin);
		c = tolower(getchar());   // get the answer and turn it to lowercase
    }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
}

// modifyRecord
void modifyRecord()
{
    // declaring and initializing variables
    FILE *fPtr = fopen("LibraryBook.txt", "r"); // open LibraryBook.txt
    int i, j, total, code, validCheck;
    char c;
    // operating process
    system("cls");
	fflush(stdin);
	// check any data in LibraryBook.txt
	if(fPtr == NULL || fgetc(fPtr) == EOF)
	{
		printf("No data\nPress any key back to menu");
		getchar();
		return;
	}
	//getting book data from LibraryBook.txt
	total = recordCount(fPtr);
	struct Book records[total];
	fseek(fPtr, 0L, SEEK_SET);
    for(i = 0; i < total; i++)
	{
		fgets(records[i].title, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].title[j] == '\n')
                records[i].title[j] = '\0';
        }
		fgets(records[i].callNum, 21, fPtr);
		records[i].callNum[19] = '\0';
		for(j = 0; j < 19; j++)
		{
		    if(records[i].callNum[j] == '\n')
                records[i].callNum[j] = '\0';
        }
        fgets(records[i].subject, 21, fPtr);
		records[i].subject[19] = '\0';
		for(j = 0; j < 19; j++)
		{
		    if(records[i].subject[j] == '\n')
                records[i].subject[j] = '\0';
        }
		fgets(records[i].author, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].author[j] == '\n')
                records[i].author[j] = '\0';
        }
        fgets(records[i].year, 6, fPtr);
        records[i].year[4] = '\0';
		fgets(records[i].status, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].status[j] == '\n')
                records[i].status[j] = '\0';
        }
		fgetc(fPtr);
	}
	fclose(fPtr);   // close LibraryBook.txt
	
	do
	{
		system("cls");
		for(i = 0; i < total; i++)
		{
			printf("%d) %s\n", i+1, records[i].title);
		}
		// let user to select the book to modify the details
		do
		{
		    fflush(stdin);
		    code = 0; // restore data in code
            printf("\nEnter the code of the book you want to modify: ");
            scanf("%d", &code);
            if(code < 1 || code > total)    // for validation
                printf("Wrong range of code!\nPlease enter again.");
		}while(code < 1 || code > total);
		
		fPtr = fopen("LibraryBook.txt", "w");
		// asking for input book data
		system("cls");
    	fflush(stdin);
    	printf("\nEnter the following information to modifly:\n");
    	printf("Title: ");
    	gets(records[code-1].title);
    	printf("Call number: ");
    	gets(records[code-1].callNum);
    	printf("Subject: ");
    	gets(records[code-1].subject);
    	printf("Author: ");
    	gets(records[code-1].author);
    	do
        {
            printf("Year of publishment: ");
            gets(records[code-1].year);
            records[code-1].year[4] = '\0';
            
            // validation process
            validCheck = 1;
            for(i = 0; i < 4; i++)
            {
                if(isdigit(records[code-1].year[i]) == 0)
                    validCheck = 0;
            }
            if(validCheck == 0)
                printf("Wrong year of publishment is entered!\nPlease enter again.\n");
        }while(validCheck == 0);
    	do
        {
            printf("Status: ");
            gets(records[code-1].status);
            records[code-1].status[19] = '\0';
            // validation process
            validCheck = 0;
            if(strcmp(strlwr(records[code-1].status), "borrowed") == 0)
                validCheck = 1;
            if(strcmp(strlwr(records[code-1].status), "available") == 0)
                validCheck = 1;
            if(validCheck == 0)
                printf("Wrong Status is entered!\n"
                    "It can only be 'Borrowed' or 'Available'\n"
                    "Please enter again.\n");
        }while(validCheck == 0);
        records[code-1].status[0] = toupper(records[code-1].status[0]);
        
		// print all data to LibraryBook.txt
		for(i = 0; i < total; i++)
    	{
    		fputs(records[i].title, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].callNum, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].subject, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].author, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].year, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].status, fPtr);
    		fputs("\n\n", fPtr);
    	}
    	fclose(fPtr);   // close LibraryBook.txt
		printf("\nDone! The record has been modified.\n");
		// asking the user to modify another book or not
		printf("Do you want to modify another book?(y/n) ");
		fflush(stdin);
		c = tolower(getchar());   // get the answer and turn it to lowercase
    }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
}

// deleteRecord
void deleteRecord()
{
    // declaring and initializing variables
    FILE *fPtr = fopen("LibraryBook.txt", "r"); // open LibraryBook.txt
    int i, j, total, code;
    char c;
    // operating process
    system("cls");
	fflush(stdin);
	// check any data in LibraryBook.txt
	if(fPtr == NULL || fgetc(fPtr) == EOF)
	{
		printf("No data\nPress any key back to menu");
		getchar();
		return;
	}
	
	do
	{
	    //getting book data from LibraryBook.txt
	    fPtr = fopen("LibraryBook.txt", "r");  // open LibraryBook.txt
    	total = recordCount(fPtr);
    	struct Book records[total];
    	fseek(fPtr, 0L, SEEK_SET);
        for(i = 0; i < total; i++)
    	{
    		fgets(records[i].title, 101, fPtr);
    		for(j = 0; j < 99; j++)
    		{
    		    if(records[i].title[j] == '\n')
                    records[i].title[j] = '\0';
            }
    		fgets(records[i].callNum, 21, fPtr);
    		records[i].callNum[19] = '\0';
    		for(j = 0; j < 19; j++)
    		{
    		    if(records[i].callNum[j] == '\n')
                    records[i].callNum[j] = '\0';
            }
    		fgets(records[i].subject, 21, fPtr);
    		records[i].subject[19] = '\0';
    		for(j = 0; j < 19; j++)
    		{
    		    if(records[i].subject[j] == '\n')
                    records[i].subject[j] = '\0';
            }
    		fgets(records[i].author, 101, fPtr);
    		for(j = 0; j < 99; j++)
    		{
    		    if(records[i].author[j] == '\n')
                    records[i].author[j] = '\0';
            }
    		fgets(records[i].year, 6, fPtr);
    		records[i].year[4] = '\0';
    		fgets(records[i].status, 101, fPtr);
    		for(j = 0; j < 99; j++)
    		{
    		    if(records[i].status[j] == '\n')
                    records[i].status[j] = '\0';
            }
    		fgetc(fPtr);
    	}
    	fclose(fPtr);   // close LibraryBook.txt
		system("cls");
		for(i = 0; i < total; i++)
		{
			printf("%d) %s\n", i+1, records[i].title);
		}
		// let user to select the book to modify the details
		do
		{
		    fflush(stdin);
		    code = 0; // restore data in code
            printf("\nEnter the code of the book you want to delete: ");
            scanf("%d", &code);
            if(code < 1 || code > total)    // for validation
                printf("Wrong range of code!\nPlease enter again.");
		}while(code < 1 || code > total);
		
		fPtr = fopen("LibraryBook.txt", "w");
		// print all data to LibraryBook.txt
		for(i = 0; i < total; i++)
    	{
    	    if(i == code - 1)
    	       continue;
    		fputs(records[i].title, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].callNum, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].subject, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].author, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].year, fPtr);
    		fputs("\n", fPtr);
    		fputs(records[i].status, fPtr);
    		fputs("\n\n", fPtr);
    	}
    	fclose(fPtr);   // close LibraryBook.txt
		printf("\nDone! The record has been deleted.\n");
		// asking the user to modify another book or not
		printf("Do you want to delete another book?(y/n) ");
		fflush(stdin);
		c = tolower(getchar());   // get the answer and turn it to lowercase
    }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
}

// searchRecord
void searchRecord()
{
    // declaring and initializing variables
    FILE *fPtr = fopen("LibraryBook.txt", "r"); // open LibraryBook.txt
    int i, j, total, code, hitCount, hitRecord;
    char c;
    char str1[100], str2[100], finding[100];
	char * strPtr;
	// operating process
	system("cls");
	fflush(stdin);
	// check any data in LibraryBook.txt
	if(fPtr == NULL || fgetc(fPtr) == EOF)
	{
		printf("No data\nPress any key back to menu");
		getchar();
		return;
	}
	//getting book data from LibraryBook.txt
	total = recordCount(fPtr);
	struct Book records[total];
	fseek(fPtr, 0L, SEEK_SET);
    for(i = 0; i < total; i++)
	{
		fgets(records[i].title, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].title[j] == '\n')
                records[i].title[j] = '\0';
        }
		fgets(records[i].callNum, 21, fPtr);
		records[i].callNum[19] = '\0';
		for(j = 0; j < 19; j++)
		{
		    if(records[i].callNum[j] == '\n')
                records[i].callNum[j] = '\0';
        }
		fgets(records[i].subject, 21, fPtr);
		records[i].subject[19] = '\0';
		for(j = 0; j < 19; j++)
		{
		    if(records[i].subject[j] == '\n')
                records[i].subject[j] = '\0';
        }
		fgets(records[i].author, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].author[j] == '\n')
                records[i].author[j] = '\0';
        }
		fgets(records[i].year, 6, fPtr);
		records[i].year[4] = '\0';
		fgets(records[i].status, 101, fPtr);
		for(j = 0; j < 99; j++)
		{
		    if(records[i].status[j] == '\n')
                records[i].status[j] = '\0';
        }
		fgetc(fPtr);
	}
	fclose(fPtr);   // close LibraryBook.txt
	
	while(1)
	{
		system("cls");
		fflush(stdin);
		printf("Search book information\n");
		printf("1. Search By Title of book\n");
	    printf("2. Search By Call number\n");
	    printf("3. Search By Subject\n");
	    printf("4. Search By Author\n");
	    printf("5. Search By Year of publishment\n");
	    printf("6. Back To Main Menu\n\n");
	    printf("Enter Your Choice: ");
	    
	    switch(getchar())
	    {
	        case '1':
	            do
				{
					system("cls");
					printf("Search Book By Title\n\n");
					printf("Enter the Title: ");
					scanf("%s", finding);
					hitCount = 0;
					for(i = 0; i < total; i++)
					{
						strcpy(str1, records[i].title);
						strcpy(str2, finding);
						strPtr = strstr(strlwr(str1), strlwr(str2));
						if(strPtr != NULL)
							hitCount += 1;
					}
					int order[hitCount];
					if(hitCount == 0)
					{
						printf("\nNo Record Found\n\n");
					
					}
					else
					{
					    int order[hitCount];
						printf("There are %d record(s)\n", hitCount);
						hitRecord = 0;
						for(i = 0; i < total; i++)
						{
							strcpy(str1, records[i].title);
							strcpy(str2, finding);
							strPtr = strstr(strlwr(str1), strlwr(str2));
							if(strPtr != NULL)
							{
								hitRecord++;
								printf("%d) %s\n", hitRecord, records[i].title);
								order[hitRecord-1] = i;
							}
						}
						do
    					{
    					    do
                    		{
                    		    fflush(stdin);
                    		    code = 0; // restore data in code
                                printf("\nEnter the code of the book you want to display: ");
                                scanf("%d", &code);
                                if(code < 1 || code > total)    // for validation
                                    printf("Wrong range of code!\nPlease enter again.");
                    		}while(code < 1 || code > total);
                    		
                    		showBookData(records[order[code - 1]]);  // display the data of the selected book
                    		
                    		// asking the user to display another book or not
                    		printf("Do you want to display another book?(y/n) ");
                    		fflush(stdin);
                    		c = tolower(getchar());   // get the answer and turn it to lowercase
    					}while(c == 'y');   // if user input 'y' or 'Y', it will repeat
					}
					// asking the user to search another book or not
            		printf("Do you want to search another book?(y/n) ");
            		fflush(stdin);
            		c = tolower(getchar());   // get the answer and turn it to lowercase
                }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
	            break;
	        case '2':
	            do
				{
					system("cls");
					printf("Search Book By Call number\n\n");
					printf("Enter the Call number: ");
					scanf("%s", finding);
					hitCount = 0;
					for(i = 0; i < total; i++)
					{
						strcpy(str1, records[i].callNum);
						strcpy(str2, finding);
						strPtr = strstr(strlwr(str1), strlwr(str2));
						if(strPtr != NULL)
							hitCount += 1;
					}
					int order[hitCount];
					if(hitCount == 0)
					{
						printf("\nNo Record Found\n\n");
					
					}
					else
					{
					    int order[hitCount];
						printf("There are %d record(s)\n", hitCount);
						hitRecord = 0;
						for(i = 0; i < total; i++)
						{
							strcpy(str1, records[i].callNum);
							strcpy(str2, finding);
							strPtr = strstr(strlwr(str1), strlwr(str2));
							if(strPtr != NULL)
							{
								hitRecord++;
								printf("%d) %s\n", hitRecord, records[i].title);
								order[hitRecord-1] = i;
							}
						}
						do
    					{
    					    do
                    		{
                    		    fflush(stdin);
                    		    code = 0; // restore data in code
                                printf("\n\nEnter the code of the book you want to display: ");
                                scanf("%d", &code);
                                if(code < 1 || code > total)    // for validation
                                    printf("Wrong range of code!\nPlease enter again.\n");
                    		}while(code < 1 || code > total);
                    		
                    		showBookData(records[order[code - 1]]);  // display the data of the selected book
                    		
                    		// asking the user to display another book or not
                    		printf("\nDo you want to display another book?(y/n) ");
                    		fflush(stdin);
                    		c = tolower(getchar());   // get the answer and turn it to lowercase
    					}while(c == 'y');   // if user input 'y' or 'Y', it will repeat
					}
					// asking the user to search another book or not
            		printf("Do you want to search another book?(y/n) ");
            		fflush(stdin);
            		c = tolower(getchar());   // get the answer and turn it to lowercase
                }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
	            break;
	        case '3':
	            do
				{
					system("cls");
					printf("Search Book By Subject\n\n");
					printf("Enter the Subject: ");
					scanf("%s", finding);
					hitCount = 0;
					for(i = 0; i < total; i++)
					{
						strcpy(str1, records[i].subject);
						strcpy(str2, finding);
						strPtr = strstr(strlwr(str1), strlwr(str2));
						if(strPtr != NULL)
							hitCount += 1;
					}
					int order[hitCount];
					if(hitCount == 0)
					{
						printf("\nNo Record Found\n\n");
					
					}
					else
					{
					    int order[hitCount];
						printf("There are %d record(s)\n", hitCount);
						hitRecord = 0;
						for(i = 0; i < total; i++)
						{
							strcpy(str1, records[i].subject);
							strcpy(str2, finding);
							strPtr = strstr(strlwr(str1), strlwr(str2));
							if(strPtr != NULL)
							{
								hitRecord++;
								printf("%d) %s\n", hitRecord, records[i].title);
								order[hitRecord-1] = i;
							}
						}
						do
    					{
    					    do
                    		{
                    		    fflush(stdin);
                    		    code = 0; // restore data in code
                                printf("\n\nEnter the code of the book you want to display: ");
                                scanf("%d", &code);
                                if(code < 1 || code > total)    // for validation
                                    printf("Wrong range of code!\nPlease enter again.\n");
                    		}while(code < 1 || code > total);
                    		
                    		showBookData(records[order[code - 1]]);  // display the data of the selected book
                    		
                    		// asking the user to display another book or not
                    		printf("\nDo you want to display another book?(y/n) ");
                    		fflush(stdin);
                    		c = tolower(getchar());   // get the answer and turn it to lowercase
    					}while(c == 'y');   // if user input 'y' or 'Y', it will repeat
					}
					// asking the user to search another book or not
            		printf("Do you want to search another book?(y/n) ");
            		fflush(stdin);
            		c = tolower(getchar());   // get the answer and turn it to lowercase
                }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
	            break;
	        case '4':
	            do
				{
					system("cls");
					printf("Search Book By Author\n\n");
					printf("Enter the Author: ");
					scanf("%s", finding);
					hitCount = 0;
					for(i = 0; i < total; i++)
					{
						strcpy(str1, records[i].author);
						strcpy(str2, finding);
						strPtr = strstr(strlwr(str1), strlwr(str2));
						if(strPtr != NULL)
							hitCount += 1;
					}
					int order[hitCount];
					if(hitCount == 0)
					{
						printf("\nNo Record Found\n\n");
					
					}
					else
					{
					    int order[hitCount];
						printf("There are %d record(s)\n", hitCount);
						hitRecord = 0;
						for(i = 0; i < total; i++)
						{
							strcpy(str1, records[i].author);
							strcpy(str2, finding);
							strPtr = strstr(strlwr(str1), strlwr(str2));
							if(strPtr != NULL)
							{
								hitRecord++;
								printf("%d) %s\n", hitRecord, records[i].title);
								order[hitRecord-1] = i;
							}
						}
						do
    					{
    					    do
                    		{
                    		    fflush(stdin);
                    		    code = 0; // restore data in code
                                printf("\n\nEnter the code of the book you want to display: ");
                                scanf("%d", &code);
                                if(code < 1 || code > total)    // for validation
                                    printf("Wrong range of code!\nPlease enter again.\n");
                    		}while(code < 1 || code > total);
                    		
                    		showBookData(records[order[code - 1]]);  // display the data of the selected book
                    		
                    		// asking the user to display another book or not
                    		printf("\nDo you want to display another book?(y/n) ");
                    		fflush(stdin);
                    		c = tolower(getchar());   // get the answer and turn it to lowercase
    					}while(c == 'y');   // if user input 'y' or 'Y', it will repeat
					}
					// asking the user to search another book or not
            		printf("Do you want to search another book?(y/n) ");
            		fflush(stdin);
            		c = tolower(getchar());   // get the answer and turn it to lowercase
                }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
	            break;
	        case '5':
	            do
				{
					system("cls");
					printf("Search Book By Year of publishment\n\n");
					printf("Enter the Year of publishment: ");
					scanf("%s", finding);
					hitCount = 0;
					for(i = 0; i < total; i++)
					{
						strcpy(str1, records[i].year);
						strcpy(str2, finding);
						strPtr = strstr(strlwr(str1), strlwr(str2));
						if(strPtr != NULL)
							hitCount += 1;
					}
					int order[hitCount];
					if(hitCount == 0)
					{
						printf("\nNo Record Found\n\n");
					
					}
					else
					{
					    int order[hitCount];
						printf("There are %d record(s)\n", hitCount);
						hitRecord = 0;
						for(i = 0; i < total; i++)
						{
							strcpy(str1, records[i].year);
							strcpy(str2, finding);
							strPtr = strstr(strlwr(str1), strlwr(str2));
							if(strPtr != NULL)
							{
								hitRecord++;
								printf("%d) %s\n", hitRecord, records[i].title);
								order[hitRecord-1] = i;
							}
						}
						do
    					{
    					    do
                    		{
                    		    fflush(stdin);
                    		    code = 0; // restore data in code
                                printf("\n\nEnter the code of the book you want to display: ");
                                scanf("%d", &code);
                                if(code < 1 || code > total)    // for validation
                                    printf("Wrong range of code!\nPlease enter again.\n");
                    		}while(code < 1 || code > total);
                    		
                    		showBookData(records[order[code - 1]]);  // display the data of the selected book
                    		
                    		// asking the user to display another book or not
                    		printf("\nDo you want to display another book?(y/n) ");
                    		fflush(stdin);
                    		c = tolower(getchar());   // get the answer and turn it to lowercase
    					}while(c == 'y');   // if user input 'y' or 'Y', it will repeat
					}
					// asking the user to search another book or not
            		printf("Do you want to search another book?(y/n) ");
            		fflush(stdin);
            		c = tolower(getchar());   // get the answer and turn it to lowercase
                }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
	            break;
	        case '6':
	            printf("Back To Main Menu in a second...");
	            Sleep(1000);
	            return;
	            break;
	        default:
				printf("\nWrong Entry!!Please re-entered correct option\n");
				getchar();
	    }
    }
}

// recordCount
int recordCount(FILE *fPtr)
{
    // declaring and initializing variables
    int count = 0;
    char c;
    
    // operating process
    fseek(fPtr, 0L, SEEK_SET);
    while((c=fgetc(fPtr))!=EOF)
	{
		if(c=='\n')
		{
			if(fgetc(fPtr)=='\n')
				count++;
		}
	}
	
	return count;
}

// showBookData
void showBookData(struct Book bk)
{
    // operation process
    printf("Title: %s\n", bk.title);
	printf("Call number: %s\n", bk.callNum);
	printf("Subject: %s\n", bk.subject);
	printf("Author: %s\n", bk.author);
	printf("Year of publishment: %s\n", bk.year);
	printf("Status: %s\n", bk.status);
}

// showTime
void showTime()             // extra
{
    time_t t = time(NULL);
    printf("Date and time: %s\n", ctime(&t));
}

// passwordAccess
void passwordAccess()       // extra
{
    // declaring and initializing variables
    char accessCode[9];
    // operating process
    do
    {
        fflush(stdin);
        printf("Please enter the access code: ");
        scanf("%s", accessCode);
        if(strcmp(accessCode,PASSWORD) != 0)
        printf("WRONG PASSWORD! PLEASE ENTER AGAIN.\n");
    }while(strcmp(accessCode,PASSWORD) != 0);
}

// borrowReturnBook
void borrowReturnBook()     // extra
{
    // declaring and initializing variables
    FILE *fPtr = fopen("LibraryBook.txt", "r");
    int i, j, books, count, code;
	int total = 0;
    char c;
    
    // operating process
    system("cls");
	fflush(stdin);
	// check any data in LibraryBook.txt
	if(fPtr == NULL || fgetc(fPtr) == EOF)
	{
		printf("No data\nPress any key back to menu");
		getchar();
		return;
	}
    total = recordCount(fPtr);
    struct Book records[total];
    
    while(1)
    {
        system("cls");
        fflush(stdin);
        printf("Borrow or Return book\n");
        printf("1. Borrow book\n");
        printf("2. Return book\n");
        printf("3. Back To Main Menu\n\n");
        printf("Enter Your Choice ");
        switch(getchar())
        {
            case '1':
                do
                {
                    system("cls");
                    fflush(stdin);
                    //getting book data from LibraryBook.txt
                	fseek(fPtr, 0L, SEEK_SET);
                    for(i = 0; i < total; i++)
                	{
                		fgets(records[i].title, 101, fPtr);
                		for(j = 0; j < 99; j++)
                		{
                		    if(records[i].title[j] == '\n')
                                records[i].title[j] = '\0';
                        }
                		fgets(records[i].callNum, 21, fPtr);
                		records[i].callNum[19] = '\0';
                		for(j = 0; j < 19; j++)
                		{
                		    if(records[i].callNum[j] == '\n')
                                records[i].callNum[j] = '\0';
                        }
                        fgets(records[i].subject, 21, fPtr);
                		records[i].subject[19] = '\0';
                		for(j = 0; j < 19; j++)
                		{
                		    if(records[i].subject[j] == '\n')
                                records[i].subject[j] = '\0';
                        }
                		fgets(records[i].author, 101, fPtr);
                		for(j = 0; j < 99; j++)
                		{
                		    if(records[i].author[j] == '\n')
                                records[i].author[j] = '\0';
                        }
                        fgets(records[i].year, 6, fPtr);
                        records[i].year[4] = '\0';
                		fgets(records[i].status, 101, fPtr);
                		for(j = 0; j < 99; j++)
                		{
                		    if(records[i].status[j] == '\n')
                                records[i].status[j] = '\0';
                        }
                		fgetc(fPtr);
                	}
                	fclose(fPtr);   // close LibraryBook.txt
                    books = 0;
                    count = 0;
                    for(i = 0; i < total; i++)
                    {
                        if(strcmp(records[i].status, "Available") == 0)
                            books++;
                    }
                    if(books == 0)
                    {
                        printf("No book is available for borrow.\n");
                        fflush(stdin);
                        getchar();
                        break;
                    }
                    int order[books];
                    for(i = 0; i < total; i++)
                    {
                        if(strcmp(records[i].status, "Available") == 0)
                        {
                            printf("%d) %s\n", count+1, records[i].title);
                            order[count] = i;
                            count++;
                        }
                    }
                    
                    do
                    {
                        fflush(stdin);
                        code = 0; // restore data in code
                        printf("\n\nEnter the code of the book needed to borrow: ");
                        scanf("%d", &code);
                        if(code < 1 || code > total)    // for validation
                            printf("Wrong range of code!\nPlease enter again.\n");
                    }while(code < 1 || code > total);
                    
                    strcpy(records[order[code-1]].status, "Borrowed");
                    
                    fPtr = fopen("LibraryBook.txt", "w");
                    // print all data to LibraryBook.txt
                    for(i = 0; i < total; i++)
                    {
                        fputs(records[i].title, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].callNum, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].subject, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].author, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].year, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].status, fPtr);
                        fputs("\n\n", fPtr);
                    }
                    fclose(fPtr);
                    
                    printf("\nDone! The status of the book changed to Borrowed.\n");
                    // asking the user to borrow another book or not
            		printf("Do you want to borrow another book?(y/n) ");
            		fflush(stdin);
            		c = tolower(getchar());   // get the answer and turn it to lowercase
                }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
                break;
            case '2':
                do
                {
                    system("cls");
                    fflush(stdin);
                    //getting book data from LibraryBook.txt
                	fseek(fPtr, 0L, SEEK_SET);
                    for(i = 0; i < total; i++)
                	{
                		fgets(records[i].title, 101, fPtr);
                		for(j = 0; j < 99; j++)
                		{
                		    if(records[i].title[j] == '\n')
                                records[i].title[j] = '\0';
                        }
                		fgets(records[i].callNum, 21, fPtr);
                		records[i].callNum[19] = '\0';
                		for(j = 0; j < 19; j++)
                		{
                		    if(records[i].callNum[j] == '\n')
                                records[i].callNum[j] = '\0';
                        }
                        fgets(records[i].subject, 21, fPtr);
                		records[i].subject[19] = '\0';
                		for(j = 0; j < 19; j++)
                		{
                		    if(records[i].subject[j] == '\n')
                                records[i].subject[j] = '\0';
                        }
                		fgets(records[i].author, 101, fPtr);
                		for(j = 0; j < 99; j++)
                		{
                		    if(records[i].author[j] == '\n')
                                records[i].author[j] = '\0';
                        }
                        fgets(records[i].year, 6, fPtr);
                        records[i].year[4] = '\0';
                		fgets(records[i].status, 101, fPtr);
                		for(j = 0; j < 99; j++)
                		{
                		    if(records[i].status[j] == '\n')
                                records[i].status[j] = '\0';
                        }
                		fgetc(fPtr);
                	}
                	fclose(fPtr);   // close LibraryBook.txt
                    books = 0;
                    count = 0;
                    for(i = 0; i < total; i++)
                    {
                        if(strcmp(records[i].status, "Borrowed") == 0)
                            books++;
                    }
                    if(books == 0)
                    {
                        printf("No book is available for return.\n");
                        fflush(stdin);
                        getchar();
                        break;
                    }
                    int order[books];
                    for(i = 0; i < total; i++)
                    {
                        if(strcmp(records[i].status, "Borrowed") == 0)
                        {
                            printf("%d) %s\n", count+1, records[i].title);
                            order[count] = i;
                            count++;
                        }
                    }
                    
                    do
                    {
                        fflush(stdin);
                        code = 0; // restore data in code
                        printf("\n\nEnter the code of the book needed to return: ");
                        scanf("%d", &code);
                        if(code < 1 || code > total)    // for validation
                            printf("Wrong range of code!\nPlease enter again.\n");
                    }while(code < 1 || code > total);
                    
                    strcpy(records[order[code-1]].status, "Available");
                    
                    fPtr = fopen("LibraryBook.txt", "w");
                    // print all data to LibraryBook.txt
                    for(i = 0; i < total; i++)
                    {
                        fputs(records[i].title, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].callNum, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].subject, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].author, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].year, fPtr);
                        fputs("\n", fPtr);
                        fputs(records[i].status, fPtr);
                        fputs("\n\n", fPtr);
                    }
                    fclose(fPtr);
                    
                    printf("\nDone! The status of the book changed to Available.\n");
                    // asking the user to return another book or not
            		printf("Do you want to return another book?(y/n) ");
            		fflush(stdin);
            		c = tolower(getchar());   // get the answer and turn it to lowercase
                }while(c == 'y');   // if user input 'y' or 'Y', it will repeat
                break;
            case '3':
                printf("Back To Main Menu in a second...");
                Sleep(1000);
                return;
                break;
            default:
                printf("\nWrong Entry!!Please re-entered correct option\n");
                getchar();
        }
    }
}


// quitSystem
void quitSystem()           // extra
{
    // operating process
    system("cls");
    printf("Library System\n");
    printf("is brought to you by\n");
	printf("CCIT4020 Class No.CL-06 Group No.03\n");
	printf("Amen, Alicia and Jerry\n\n");
    printf("Exiting in 3 second");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".");
    exit(1);
}

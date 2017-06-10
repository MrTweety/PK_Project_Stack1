
#include "stdafx.h"
#include "interface.h"
#include "Stack.h"
#include "student.h"
#include "faculty.h"
#include "messages.h"
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)

/**/static char FileName[] = "student.dat";
//static char FileName[] = "student_auto.dat";





 void MyMenu()
{
	Stack_Init(Student_Free);
	int op;
	

	while (1)

	
	{
		size_t it;
		for (it = 0; it<INTERF_TOT; ++it)
		{
			printf("%s\n", strtab[it]);
		}
		scanf_s("%d", &op);
		switch (op)
		{
		case INTERF_PUSH: push();
			break;
		case INTERF_POP: pop();
			break;
		case INTER_SEARCH: search();
			break;
		case INTER_PRINT_ALL: print_all();
			break;
		case INTER_SAVE: save();
			break;
		case INTER_OPEN: open();			
			break;
		case INTERF_CLEAR: clear();			
			break;
		case INTERF_STOP: clear();
			return ;		
		default:
			printf("nieuznawany kod operacji\n");
		};
	}
}



//*******************************************************************************************************
static void push()
{
	char name[512];
	int year;
	FACULTY faculty=FACULTY_TOT;
	printf("Podaj nazwisko:\n");
	scanf("%s", name);
	int t = strlen(name);
		
	printf("Podaj rok\n");
	scanf("%d", &year);
	
	void *pdat = NULL;

	
	do
	{
		printf("Podaj kierunek:\n");
		for (int it = 0; it < FACULTY_TOT; ++it)
		{
			printf("%s\n", ffaculty[it]);
		}

		scanf("%d", &faculty);

	} while ((faculty < MATH) || (faculty >= FACULTY_TOT));
	
		

	


	pdat = Student_Push(name, year, faculty);
		if (!Stack_Push(pdat))
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			{
				clear();
				pdat = NULL;
				system("pause");
				exit(1);
			}
		Student_Print(pdat);
		printf("\n\n");
		
		
		
}
//*******************************************************************************************************
static void pop()
{
	MY_STACK  tmp = Stack_Pop();
	Student_Print(tmp.pData);
	Student_Free(tmp.pData);
	printf("\n\n");
}
//*******************************************************************************************************
static void top()
{
	MY_STACK  tmp = Stack_Top();
	Student_Print(tmp.pData);
	printf("\n\n");
}
//*******************************************************************************************************
static void clear()
{
	Stack_Free();
	printf("\n\n");
}

//*******************************************************************************************************
static void print_all()
{
	Stack_Print_All(Student_Print);
	printf("\n\n");
}
//*******************************************************************************************************


static void save()
{
	Stack_save(Student_save_bin, FileName);
	printf("\n\n");
}
static void open()
{
	Stack_open(Student_open_bin, FileName);
	printf("\n\n");
}


static void search()
{
	void *ptrm = NULL;
	char name[512];
	int year;
	
	FACULTY faculty = FACULTY_TOT;
	SEARCH ssearch = SEARCH_TOTAL;

	for (int it = 0; it<SEARCH_TOTAL; ++it)
	{
		printf("%s\n", search_tab[it]);
	}


	scanf("%d", &ssearch);

	switch (ssearch)
	{
	case SEARCH_NAME: 
				printf("Podaj nazwisko:\n");
				scanf("%s", name);
				ptrm = &name;
				Stack_search_1(Student_search_name, ptrm);
				break;
	case SEARCH_YEAR: 
				printf("Podaj rok:\n");
				scanf("%d", &year);
				ptrm = &year;
				Stack_search_1(Student_search_year, ptrm);
				break;
		
	case SEARCH_FACULTY:
		
			do
			{
				printf("Podaj kierunek:\n");
				for (int it = 0; it < FACULTY_TOT; ++it)
				{
					printf("%s\n", ffaculty[it]);
				}

				scanf("%d", &faculty);

			} while ((faculty < MATH) || (faculty >= FACULTY_TOT));				
					ptrm = &faculty;
					Stack_search_1(Student_search_faculty, ptrm);
					break;
		default: search();
	};
		printf("\n\n");
}


//*******************************************************************************************************

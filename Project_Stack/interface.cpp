
#include "stdafx.h"
#include "interface.h"
#include "Stack.h"
#include "student.h"
#include "faculty.h"
#include "messages.h"
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)






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
		case INTERF_PUSH: 
			//auto_push();
			/**/push();

			break;
		case INTERF_POP: 
			//top(); 
			pop();
			break;
		case INTER_SEARCH: search();
			break;
		case INTER_PRINT_ALL:
			print_all();

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
void push()
{

	char *name=(char*)malloc(sizeof(char));
	if (!name)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
		{
			free(name);
			name = NULL;
			system("pause");
			exit(1);
		};
	int year;
	int faculty;
	printf("name\n");
	scanf("%s", name);
	printf("year\n");
	scanf("%d", &year);
	printf("Podaj Kierunek\n");
	size_t it;
	void *pdat=NULL;
	for (it = 0; it<FACULTY_TOT; ++it)
	{
		printf("%s\n", ffaculty[it]);
	}
	scanf("%d", &faculty);
	FACULTY fac = FACULTY_TOT;


	switch (faculty)
	{
	case MATH:  fac = MATH;
		break;
	case COMPUTER:  fac = COMPUTER;
		break;
	case INTERF_CLEAR:
		break;
	case INTERF_STOP:

	default:
		printf("NO FACULTY\n");
	};
	
//	void *pdat = Student_Push(name, year, fac);
	pdat = Student_Push(name, year, fac);
		if (!Stack_Push(pdat))
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			{
				clear();
				free(name);
				pdat = NULL;
				name = NULL;
				system("pause");
				exit(1);
			}
		Student_Print(pdat);
		
		free(name);
		name = NULL;
}
//*******************************************************************************************************
void pop()
{
	MY_STACK  tmp = Stack_Pop();
	Student_Print(tmp.pData);
	Student_Free(tmp.pData);
}
//*******************************************************************************************************
void top()
{
	MY_STACK  tmp = Stack_Top();
	Student_Print(tmp.pData);
}
//*******************************************************************************************************
void clear()
{
	Stack_Free();
}

//*******************************************************************************************************
void print_all()
{
	Stack_Print_All(Student_Print);
}
//*******************************************************************************************************


void save()
{
	Stack_save(Student_save_bin, "aaa.dat");
	//printf("funkcje jeszcze nie zosta³a dodana");
}
void open()
{
	//printf("funkcje jeszcze nie zosta³a dodana");
	Student_open_bin("aaa.dat");

}


void search()
{
	SEARCH ssearch = SEARCH_TOTAL;
	printf("wybierz sposób wyszukiwania\n");
	for (int it = 0; it<SEARCH_TOTAL; ++it)
	{
		printf("%s\n", search_tab[it]);
	}
	scanf("%d", &ssearch);
	printf("%s\n",search_tab[ssearch]);


	//printf("funkcje jeszcze nie zosta³a dodana");
	//Stack_search(Student_search_name,ssearch);
}










//*******************************************************************************************************

//*******************************************************************************************************
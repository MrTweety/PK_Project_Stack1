#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include <string.h>
#include "messages.h"
#pragma warning (disable : 4996)

static MY_STACK *top = NULL;  //wskaznik do pierwszego elementu w kolejce
static MY_STACK *search = NULL;

static char FileName[] = "student.txt";
static FILE *pf = NULL;

FreeData ptr_free_dat;           //Deklaracja wskaznika do funkcji typu FreeData
PrintObject ptr_fun_prnt;       //wskaznik do funkcji, ktora drukuje obiekt danych
SearchObject1 ptr_search1;
SaveObject ptr_save;
OpenObject ptr_open;



//*********************************************************************************************************************************
 void Stack_Init(FreeData pFreeDat)
{
	top = NULL;
	ptr_free_dat = pFreeDat;
}

//*********************************************************************************************************************************
MY_STACK * Stack_Push(void *pdat)
{
	
	
		//alokujemy pamiec dla nowego elementu stosu
		MY_STACK *current = (MY_STACK *)malloc(sizeof(MY_STACK));
		if (!current)
			return NULL;

		//Jest to element pierwszy - prev = NULL
		current->prev = top;
		top = current;

		

		//Ustawiamy pData
		current->pData = pdat;

		
		

		return current;
	}

//*********************************************************************************************************************************
MY_STACK Stack_Pop()
{
	//printf("POP poczatek \n");
	MY_STACK rv;
	if (!top)
	{
		if (my_mess_fun(MY_MESS_POP_ERROR) == MY_DECISION_POP_BREAK)
		{
			rv.pData = NULL;
			rv.prev = NULL;
			top = NULL;
			system("pause");
			return rv;

		}
		
		
	}
	else
	{
		//Pobieramy ostatni element
		//POPRZEDNI element powinien byc top. Pobieramy jego adres.
		MY_STACK *prev = top->prev;


		//Pobieramy dane dla elementu top.
		rv.pData = top->pData;
		rv.prev = NULL;
		
		//zwalniamy pamiec dla elementu top
		free(top);

		//przestawiamy top do poprzedniego elementu
		top = prev;
	}
	//printf("POP koniec \n");
	return rv;
}
//*********************************************************************************************************************************
MY_STACK Stack_Top()
{
	printf("TOP poczatek \n");
	MY_STACK rv;
	if (!top)
	{
		//kolejka jest pusta
		rv.pData = NULL;
		rv.prev = NULL;
		printf("POP kolejka jest pusta\n");
	}
	else
	{
		
	//Pobieramy dane dla elementu top.
		rv.pData = top->pData;


	
	}
	printf("TOP koniec \n");
	return rv;
}


//*********************************************************************************************************************************

void Stack_Free()
{
	//Zwalniamy cala stos
	//Ustaliamy wskaznik p do TOP
	MY_STACK *p = top, *ptmp = NULL;

	//pobieramy  obiekty ze stosu
	while (p)
	{
		//Zwalniamy dane dla biezacego elementu stosu, do ktorego wskazuje wskaznik p
		(*ptr_free_dat)(p->pData);

		//Przypisujemy adres biezacego elementu do pomocniczej zmiennej ptmp
		ptmp = p;

		//przestawiamy wskaznik p do poprzedniego elementu stosu
		p = p->prev;

		//zwalniamy biezacy element stosu
		free(ptmp);
	}

	top = NULL;
}

//*********************************************************************************************************************************
void Stack_Print_All(PrintObject pDat)
{
	MY_STACK *p = top;
	ptr_fun_prnt = pDat;

	if (p == NULL)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
		{

			system("pause");
			return;
		}
	//pobieramy po kolejce obiekty
	while (p)
	{
		//Wypisanie danych dla biezacego elementu stosu, do ktorego wskazuje wskaznik p
		(*ptr_fun_prnt)(p->pData);

		//przestawiamy wskaznik p do poprzedniego elementu stosu
		p = p->prev;

	}
}

//**********************************************************


void Stack_save(SaveObject pDat, char *file)
{

	ptr_save = pDat;
	MY_STACK *p = top;
	if (p == NULL)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
		{

			system("pause");
			return;
		}

	FILE *wfile = fopen(file, "wb+");

	
	if (wfile == NULL)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK)
		{
			wfile = NULL;
			system("pause");
			return;

		}


	while (p)
	{		
		(*ptr_save)(p->pData, file, wfile);
		p = p->prev;
		
	}	
	fclose(wfile);

}



//*******************************************************
void Stack_open(OpenObject pDat, char * file)
{
	ptr_open = pDat;

	{
		(*ptr_open)( file);
	}

}
//*******************************************************



	
void Stack_search_1(SearchObject1 pDat, void* ptrm)
{
	search = top;

	ptr_search1 = pDat;

	

	while (search)
	{
		// Wypisanie danych dla biezacego elementu stosu, do ktorego wskazuje wskaznik p
		(*ptr_search1)(search->pData, ptrm);

		//przestawiamy wskaznik p do poprzedniego elementu stosu
		search = search->prev;
	}
}
//********************************************************************************************************

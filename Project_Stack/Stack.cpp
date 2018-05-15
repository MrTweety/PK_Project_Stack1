
//Mateusz Gaczorek
//Student I roku Informatyki gr : 11 WFMiI

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include <string.h>
#include "messages.h"
#pragma warning (disable : 4996)



struct MY_STACK *top = NULL;  //wskaznik do pierwszego elementu w kolejce
unsigned int ilosc;
static char FileName[] = "student.txt";


FreeData ptr_free_dat;           //Deklaracja wskaznika do funkcji typu FreeData
PrintObject ptr_fun_prnt;       //wskaznik do funkcji, ktora drukuje obiekt danych
SearchObject1 ptr_search1;      //szukanie
SaveObject ptr_save;           //zapis
OpenObject ptr_open;          //odczyt





//*********************************************************************************************************************************
 void Stack_Init(FreeData pFreeDat)
{
	top = NULL;
	ptr_free_dat = pFreeDat;
	ilosc = 0;
}

//*********************************************************************************************************************************
MY_STACK * Stack_Push(void *pdat)
{
	
	
		//alokujemy pamiec dla nowego elementu stosu
		MY_STACK *current = (MY_STACK *)malloc(sizeof(MY_STACK));
		if (!current)
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			{
				free(current);
				current = NULL;
				Stack_Free();
				system("pause");
				exit(1);
			}

		//Jest to element pierwszy - prev = NULL
		current->prev = top;
		top = current;

		

		//Ustawiamy pData
		current->pData = pdat;
		ilosc++;

		
		

		return current;
	}

//*********************************************************************************************************************************
MY_STACK Stack_Pop()
{
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
	ilosc--;
	return rv;
}
//*********************************************************************************************************************************
/*
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
*/
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
	ilosc = 0;
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


	unsigned int no_items = ilosc;
	size_t it;
	unsigned int no_it = no_items;
	__int64 filepos = 0;
	__int64 *file_desc = (__int64 *)malloc((no_items + 1) * sizeof(__int64));
	if (!file_desc)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK) {
			free(file_desc);
			file_desc = NULL;
			system("pause");
			return;
		}

	FILE *wfile = fopen(file, "wb+");
	if (wfile == NULL)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK) {
			wfile = NULL;
			system("pause");
			return;
		}

	if (fwrite(&no_it, sizeof(unsigned int), 1, wfile) != 1)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK) {
			free(file_desc);
			file_desc = NULL;
			system("pause");
			return;
		}
	//rezerwacja pamieci
	_fseeki64(wfile, (no_items + 1) * sizeof(__int64), SEEK_CUR);


	for (it = 0; it < no_items; ++it)
	{
		file_desc[it] = ftell(wfile);

		(*ptr_save)(p->pData, file, wfile);
		p = p->prev;

	}


	file_desc[it] = ftell(wfile);   //!!!

	//zapisujemy wskazniki pozycji dla kazdego recordu
	_fseeki64(wfile, sizeof(unsigned int), SEEK_SET);
	if (fwrite(file_desc, sizeof(__int64), no_items + 1, wfile) != no_items + 1)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK) {
			free(file_desc);
			file_desc = NULL;
			system("pause");
			return;
		}

	fclose(wfile);

	if (wfile)
		fclose(wfile);
	wfile = NULL;

	if (file_desc)
		free(file_desc);
	file_desc = NULL;
}
//**********************************************************************************************************
void Stack_open(OpenObject pDat, char * file)
{
	ptr_open = pDat;
	unsigned int no_items = 0, it, rec;
	__int64 rec_len;
	__int64 *file_desc = NULL;

	FILE *r = fopen(file, "rb");
	if (r == NULL)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK)
		{
			r = NULL;
			system("pause");
			return;

		}

	if (fread(&no_items, sizeof(unsigned int), 1, r) != 1)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK) {
			r = NULL;
			system("pause");
			return;
		}

	file_desc = (__int64 *)malloc((no_items + 1) * sizeof(__int64));
	if (fread(file_desc, sizeof(file_desc[0]), no_items + 1, r) != no_items + 1)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK) {
			free(file_desc);
			file_desc = NULL;
			system("pause");
			return;
		}

	for (it = 0; it < no_items; ++it)
	{
		rec = no_items - it - 1; //czytanie od ty³u 
		_fseeki64(r, file_desc[rec], SEEK_SET);	
		(*ptr_open)( file,r);//wywo³anie funkcji odczyt student
	}

	if (file_desc)
		free(file_desc);
	file_desc = NULL;

	
	if (r)
		fclose(r);
	r = NULL;

}
//************************************************************************************	
void Stack_search_1(SearchObject1 pDat, void* ptrm)
{
	 MY_STACK *search = NULL;
	search = top;
	if (search==NULL)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
		{
			system("pause");
			return;
		}
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

MY_STACK * TOP()
{
	return top;
}
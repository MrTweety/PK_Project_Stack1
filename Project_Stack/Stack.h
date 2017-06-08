#pragma once


struct MY_STACK
{
	void *pData;    //wskaznik do danych typu void *
	MY_STACK *prev; //wskaznik do poprzedniego elementu stosu
	
};

enum SEARCH
{
	SEARCH_NAME,
	SEARCH_YEAR,
	SEARCH_FACULTY,
	SEARCH_ALL,
	SEARCH_TOTAL
};

static char *search_tab[] =
{
	"0 - search name",
	"1- search year",
	"2 - search faculty",
	"3 - search all"
};



typedef void(*PrintObject)(void * pdat);
typedef void(*FreeData)(void *pdat);  //Definicja typu: wskaznik do funkcji z prototypem void NazwaFunkcji(void *);
typedef void(*SearchObject)(void * pdat, char *sname);
typedef void(*SaveObject)(void * pdat, char *file, FILE *wfile);
typedef void(*OpenObject)(void * pdat, char *file);

//DOBRE

void Stack_Init(FreeData pFreeDat);
void Stack_Free();
MY_STACK * Stack_Push(void *pdat);
MY_STACK Stack_Pop();
MY_STACK Stack_Top();
void Stack_Print_All(PrintObject pDat);
//TESTOWANE


void Stack_save(SaveObject pDat, char *file);
void Stack_open(OpenObject pDat, char *file);


void Stack_search(SearchObject pDat, SEARCH ssearch);



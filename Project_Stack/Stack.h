
#ifndef STACK___H
#define STACK___H

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
	SEARCH_TOTAL
};

static char *search_tab[] =
{
	"0 - search name",
	"1- search year",
	"2 - search faculty",
};



typedef void(*PrintObject)(void * pdat); //Definicja typu: wskaznik do funkcji drukujacej na monitorze zawartosc stosu
typedef void(*FreeData)(void *pdat);  //Definicja typu: wskaznik do funkcji z prototypem void NazwaFunkcji(void *);
typedef void(*SearchObject1)(void * pdat, void *ptrm);  //Definicja typu: wskaznik do funkcji szukajacej
typedef void(*SaveObject)(void * pdat, char *file, FILE *wfile); //Definicja typu: wskaznik do funkcji zapisujacej do pliku
typedef void(*OpenObject)(char *file); //Definicja typu: wskaznik do funkcji czytajacej plik



void Stack_Init(FreeData pFreeDat);
void Stack_Free();
MY_STACK * Stack_Push(void *pdat);
MY_STACK Stack_Pop();
MY_STACK Stack_Top();
void Stack_Print_All(PrintObject pDat);
void Stack_save(SaveObject pDat, char *file);
void Stack_open(OpenObject pDat, char *file);
void Stack_search_1(SearchObject1 pDat, void *ptmr);





#endif
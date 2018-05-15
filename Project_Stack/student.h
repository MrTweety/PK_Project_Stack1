
//Mateusz Gaczorek
//Student I roku Informatyki gr : 11 WFMiI

#ifndef STUDENT___H
#define STUDENT___H

#include "faculty.h"

struct MY_STUDENT{	
	char *name;
	int year;
	FACULTY faculty;
};


static void *Student_Init(char *name, int year,enum FACULTY faculty);
void Student_Free(void *ptr);
void * Student_Push(char *name, int year, FACULTY faculty);
void Student_Print(void *ptr);
//zapis/odczyt
void Student_save_bin(void *ptr, char * file, FILE *wfile);
void Student_open_bin(char * file, FILE *r);
//szukanie
void Student_search_name(void *ptr, void * ptrm);
void Student_search_year(void *ptr, void * ptrm);
void Student_search_faculty(void *ptr, void * ptrm);



#endif

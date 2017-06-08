#pragma once



#pragma once
#include "faculty.h"

#define MAX_NAME 50

struct MY_STUDENT
{
	
	char *name;
	int year;
	FACULTY faculty;

};


void *Student_Init(char *name, int year,enum FACULTY faculty);
void Student_Free(void *ptr);
void * Student_Push(char *name, int year, FACULTY faculty);
void Student_Print(void *ptr);



void Student_save_bin(void *ptr, char * file, FILE *wfile);
void Student_open_bin( char * file);
void Student_open_bin_1(char * file);



void Student_search_name(void *ptr,char *sname);
void Student_search_year(void *ptr, int *year);
void Student_search_faculty(void *ptr, FACULTY faculty);
void Student_search(void *ptr, char *sname, int year, FACULTY faculty);


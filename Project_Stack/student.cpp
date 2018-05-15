
//Mateusz Gaczorek
//Student I roku Informatyki gr : 11 WFMiI

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include "string.h"
#include "faculty.h"
#include "messages.h"
#include "Stack.h"



#pragma warning (disable : 4996)

static void *Student_Init (char *name, int year, enum FACULTY faculty)
{
	int longg = strlen(name);
	struct MY_STUDENT *new_student = (struct MY_STUDENT*) malloc(sizeof(struct MY_STUDENT));
	if (!new_student)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
		{
			
			Student_Free(new_student);
			new_student = NULL;
			Stack_Free();
			system("pause");
			exit(1);			
		}
	new_student->name=(char*)malloc((longg +1)*sizeof(char));  //SF Tu Pan nadpisuje 1 bajt !!!
	if (!new_student->name)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
		{
			Student_Free(new_student->name);
			Student_Free(new_student);
			system("pause");
			Stack_Free();
			exit(1);
		}

	

	strcpy(new_student->name, name);
	new_student->year = year;
	new_student->faculty = faculty;

	printf("%d,%lf", sizeof(new_student->name));

	printf("dodanie studenta %s\n", new_student->name);
	return (void *)(new_student);
	

}


void Student_Free(void *ptr)
{

	MY_STUDENT *student = (MY_STUDENT*)ptr;
	if (student) {
		if (student->name) {
			free(student->name);//SF tu Pan gubi pamiec - name nie zwolnione
			student->name = NULL;
		}
		free(student);
		student = NULL;
	}
}


void * Student_Push(char *name, int year, FACULTY faculty)
{
	return Student_Init(name, year, faculty);
}




//***********************************************************************************************************

void Student_Print(void *ptr)
{
			MY_STUDENT *tmp = (MY_STUDENT *)ptr;
		if (tmp==NULL) 
			if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
			{
				tmp = NULL;
				system("pause");
				return;
			}
		
			printf("name    : %s\n", tmp->name);
			printf("year    : %d\n", tmp->year);
			printf("name    : %s\n", ffacultyy[tmp->faculty]);
			printf("\n\n");		
}
//*************************************************************

void Student_save_bin(void *ptr, char * file,FILE *wfile)
{
	
	MY_STUDENT *tmp = (MY_STUDENT *)ptr;
	if (tmp == NULL) 
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK)
		{
			tmp = NULL;
			system("pause");
			return;
		}

	__int8 longg = strlen(tmp->name);   //SF    '\0'  ???
	fwrite(&longg, sizeof(__int8), 1, wfile);
	fwrite((const void *)tmp, sizeof(MY_STUDENT), 1, wfile);
	fwrite((tmp->name), ((longg+1)*sizeof(char)), 1, wfile);
 }


//***********************************************************************************

 void Student_open_bin(char * file, FILE *r)
 {
	 size_t count_read = 1;
	 size_t count_rread = 1;
	 __int8 longg;
	 MY_STUDENT tmp;


	 count_rread = fread(&longg, sizeof(__int8), 1, r);
	 count_read = fread((MY_STUDENT *)&tmp, sizeof(MY_STUDENT), 1, r);
	 tmp.name = (char*)calloc((longg + 1), ((longg + 1) * sizeof(char)));
	 if (!tmp.name)
		 if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
		 {
			 free(tmp.name);
			 tmp.name = NULL;
			 Stack_Free();
			 system("pause");
			 exit(1);
		 }
	 fread(tmp.name, ((longg + 1)), 1, r);

	 //dodajemy obiekt do stosu
	 if (count_read && count_rread)
	 {
		 void *pdat = Student_Push(tmp.name, tmp.year, tmp.faculty);
		 if (!Stack_Push(pdat))
			 if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			 {
				 free(tmp.name);
				 tmp.name = NULL;
				 pdat = NULL;
				 Stack_Free();
				 system("pause");
				 exit(1);
			 }
		 Student_Print(pdat);
		 pdat = NULL;

	 }
	 free(tmp.name);
	 tmp.name = NULL;

 }
//****************************************************************************************************
void Student_search_name(void *ptr, void * ptrm) {


	MY_STUDENT *tmp = (MY_STUDENT *)ptr;
	if (tmp == NULL)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
		{
			tmp = NULL;
			system("pause");
			return;
		}
	char *ab = (char*)ptrm;
	if (strcmp((ab), tmp->name) == 0)	
		Student_Print(tmp);
}
//****************************************************************************************************
void Student_search_year(void * ptr, void * ptrm)
{
	MY_STUDENT *tmp = (MY_STUDENT *)ptr;
	if (tmp == NULL)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
		{
			tmp = NULL;
			system("pause");
			return;
		}

	int *syear = (int*)ptrm;
	if (*syear == tmp->year)
		Student_Print(tmp);	
}
//****************************************************************************************************
void Student_search_faculty(void * ptr, void * ptrm)
{

	MY_STUDENT *tmp = (MY_STUDENT *)ptr;
	if (tmp == NULL)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
		{
			tmp = NULL;
			system("pause");
			return;
		}

	FACULTY *sfa = (FACULTY*)ptrm;
	if (*sfa == tmp->faculty)	
		Student_Print(tmp);
}
//****************************************************************************************************




// Funkcja zosta³a napisana od nowa wstawaim stara wersje zawierajac¹  komentarze //SF

/*
//czytanie w odwrotnej kolejnosci
void Student_open_bin(  char * file)
{
size_t count_read = 1;
size_t count_rread = 1;
__int8 longg;



FILE *r = fopen(file, "rb");
if (r == NULL)
if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK)
{
r = NULL;
system("pause");
return;

}


MY_STUDENT tab[TAB_N];  //SF ???
int i = 0;


while (count_read && count_rread)
{

count_rread = fread(&longg, sizeof(__int8), 1, r);
count_read = fread((void *)&tab[i], sizeof(MY_STUDENT), 1, r);  //SF ???

//SF Tu Pan tworzy tablice tab, a pozniej - stos. Tak po co stos, jesli pamiec juz jest zajenta tablica?
//Prosze wykorzystac tu pojedynczy obiekt MY_STUDENT. Na zajeciach my rozwazali, jak to zrobic.

if (feof(r) == 0)
{


tab[i].name = (char*)calloc(100, ((longg+1) * sizeof(char)));  //SF tu gubimy '\0'
if (!tab[i].name)
if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK){
system("pause");
for (int j = 0; j <= i; ++j) {

free(tab[j].name);
tab[j].name = NULL;
}
return;
}
fread(tab[i].name, ((longg)), 1, r);
i++;
}


}

//SF ???
for (int j = (i-1); j >= 0; --j)
{

void *pdat = Student_Push(tab[j].name, tab[j].year, tab[j].faculty);
if (!Stack_Push(pdat))
if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
{
system("pause");
for (int n=j; j > 0; --n)
{
free(tab[j].name);
tab[j].name = NULL;
}
return;

}
Student_Print(pdat);
}
fclose(r);
}
*/
//****************************************************************************************************


#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include "string.h"
#include "faculty.h"
#include "messages.h"
#include "Stack.h"
#define TAB_N 10000


//struct MY_STUDENT *top = NULL;



#pragma warning (disable : 4996)

static void *Student_Init (char *name, int year, enum FACULTY faculty)
{
	int t = strlen(name);
	//printf("%d\n", t);
	struct MY_STUDENT *new_student = (struct MY_STUDENT*) malloc(sizeof(struct MY_STUDENT));
	if (!new_student)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
		{
			Student_Free(new_student);
			new_student = NULL;
			system("pause");
			exit(1);
		}
	new_student->name=(char*)malloc(t*sizeof(char));
	if (!new_student->name)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
		{
			Student_Free(new_student);
			system("pause");
			exit(1);
		}

	strcpy(new_student->name, name);
	new_student->year = year;
	new_student->faculty = faculty;

//	int d = _msize(new_student->name);
	// t = strlen(name);
	//printf("%d     %d\n", t,d);
	printf("dodanie studenta %s\n", new_student->name);
	return (void *)(new_student);
	

}


void Student_Free(void *ptr)
{

	MY_STUDENT *student = (MY_STUDENT*)ptr;
	if (student)
		free(student);
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


//zapisywanie 
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
	

	__int8 t = strlen(tmp->name);

	fwrite((const void *)tmp, sizeof(MY_STUDENT), 1, wfile);
	fwrite(&t, sizeof(__int8), 1, wfile);
	fwrite((tmp->name), (t*sizeof(char)), 1, wfile);
  // fputs((tmp->name), wfile);

}

//***********************************************************************************
//czytanie w odwrotnej kolejnosci 
void Student_open_bin(  char * file)
{
	size_t count_read = 1;
	size_t count_rread = 1;
	__int8 longg;
	char *count_readd[TAB_N];


	FILE *r = fopen(file, "rb");
	if (r == NULL)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
		{
			r = NULL;
			system("pause");
			return;

		}
	

	MY_STUDENT tab[TAB_N];
	MY_STUDENT tab_name[TAB_N];
	//MY_STUDENT tmp;
	int i = 0;
	
	
		while (count_read && count_rread)
		{
			if (feof(r) != 0)
			{
				break;
			}
			count_read = fread((void *)&tab[i], sizeof(MY_STUDENT), 1, r);
			count_rread = fread(&longg, sizeof(__int8), 1, r);
			count_readd[i] = (char*)calloc(100, (longg*sizeof(char)));
				if (!count_readd[i])
					if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
					{
						for ( int j=i ; j > 0; --j)
						{
							
						}
						
						system("pause");
						exit(1);
					}
				count_rread = fread(count_readd[i], ((longg)), 1, r);

				if (count_read)
				{
					i++;
				}
				if (feof(r) !=0)
				{
					break;
				}
	}
	
		for (int j = (i-1); j >= 0; --j)
		{
			
		void *pdat = Student_Push(count_readd[j], tab[j].year, tab[j].faculty);
			if (!Stack_Push(pdat))
				if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				{
					for (int j = i; j > 0; --j)
					{
						
}
					
					system("pause");
					
				}
			Student_Print(pdat);
			free(count_readd[i]);
			count_readd[i] = NULL;
		}

	fclose(r);
}
//****************************************************************************************************

//czytanie po koleii 
void Student_open_bin_1(char * file)
{
	FILE *r = fopen(file, "rb");
	if (r == NULL)
		if (my_mess_fun(MY_MESS_PRINT_ERROR) == MY_DECISION_PRINT_BREAK)
		{
			r = NULL;
			system("pause");
			return;

		}

	
	size_t count_read = 1;
	size_t count_rread = 1;
	__int8 longg;
	char *count_readd=NULL;
	MY_STUDENT tmp;

	while (count_read && count_rread)
	{
		
		count_read = fread((MY_STUDENT *)&tmp, sizeof(MY_STUDENT), 1, r);
		count_rread=fread(&longg, sizeof(__int8), 1, r);

		count_readd = (char*)calloc(100,(sizeof(char)));
		if (!count_readd)
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			{

				system("pause");
				free(count_readd);
				count_readd = NULL;
				exit(1);
			}
		
		fread(count_readd, ((longg)), 1, r);
		//fgets(count_readd, (longg+1), r);
		//dodajemy obiekt do stosu
	


		if (count_read && count_rread)
		{
			void *pdat = Student_Push(count_readd, tmp.year, tmp.faculty);
			if (!Stack_Push(pdat))
				if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				{
					Student_Free(pdat);
					pdat = NULL;
					system("pause");
					free(count_readd);
					count_readd = NULL;
					exit(1);
					
					
				}
			Student_Print(pdat);
			free(count_readd);
			count_readd = NULL;
		}



	}

}



//****************************************************************************************************
void Student_search_name(void *ptr, void * ptrm) {


	MY_STUDENT *tmp = (MY_STUDENT *)ptr;
	if (tmp == NULL)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK)
		{
			tmp = NULL;
			system("pause");
			return;
		}
	char *ab = (char*)ptrm;
		if (strcmp((ab), tmp->name) == 0)
			{

				printf("\n");
				printf("name    : %s\n", tmp->name);
				printf("year    : %d\n", tmp->year);
				printf("faculty: %s\n", ffacultyy[tmp->faculty]);
				printf("\n");

			};
}
//****************************************************************************************************
void Student_search_year(void * ptr, void * ptrm)
{
	MY_STUDENT *tmp = (MY_STUDENT *)ptr;
	if (tmp == NULL)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK)
		{
			tmp = NULL;
			system("pause");
			return;
		}

	int *syear = (int*)ptrm;
		if ( *syear == tmp->year)
			{

				printf("\n");
				printf("name    : %s\n", tmp->name);
				printf("year    : %d\n", tmp->year);
				printf("faculty: %s\n", ffacultyy[tmp->faculty]);
				printf("\n");

			};
}
//****************************************************************************************************
void Student_search_faculty(void * ptr, void * ptrm)
{

	MY_STUDENT *tmp = (MY_STUDENT *)ptr;
	if (tmp == NULL)
		if (my_mess_fun(MY_MESS_FILE_ERROR) == MY_DECISION_FILE_BREAK)
			{
				tmp = NULL;
				system("pause");
				return;
			}



	FACULTY *sfa = (FACULTY*)ptrm;	
		if (*sfa == tmp->faculty)
			{

				printf("\n");
				printf("name    : %s\n", tmp->name);
				printf("year    : %d\n", tmp->year);
				printf("faculty: %s\n", ffacultyy[tmp->faculty]);
				printf("\n");

			};
}
//****************************************************************************************************




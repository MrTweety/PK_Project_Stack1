


#include "stdafx.h"
#include "messages.h"
#include <stdlib.h>
#include <string.h>

static char *my_message_str_tab[] = {
	"E memory allocation error",	//MY_MESS_MEM_ALOC_ERROR
	"P No students,top=NULL",       //MY_DECISION_PRINT_BREAK
	"S POP:stack is empty",    //
	"O Error opening file"      //MY_DECISION_PRINT_BREAK
		        
};

MY_DECISION my_mess_fun(enum MY_MESSAGES mess)
/*===================================================================================
Przy podanym numerowaniu enum MY_MESSAGES komunikat mess jest poprostu
numierem wiersza w tablice my_message_str_tab.
RatVal:
MY_DECISION_BREAK    - Przerywamy wykonanie programu
MY_DECISION_CONTINUE - Kontynujemy wykonanie
====================================================================================*/
{
	MY_DECISION retval = MY_DECISION_CONTINUE;

	puts(my_message_str_tab[mess] + 1);

	//Analizujemy komunikat: b³¹d (przerywamy program) albo komunikat 
	//(drukujemy i kontynujemy dalej)
	if (my_message_str_tab[mess][0] == 'E')
	{
		//to jest b³¹d. Przerywamy wykonanie programu.
		retval = MY_DECISION_BREAK;
	}

	if (my_message_str_tab[mess][0] == 'P')
	{
		//to jest b³¹d. Przerywamy wykonanie funkcji
		retval = MY_DECISION_PRINT_BREAK;
	}

	if (my_message_str_tab[mess][0] == 'O')
	{
		//to jest b³¹d. Przerywamy wykonanie funkcji
		retval = MY_DECISION_FILE_BREAK;
	}

	if (my_message_str_tab[mess][0] == 'S')
	{
		//to jest b³¹d. Przerywamy wykonanie funkcji.
		retval = MY_DECISION_POP_BREAK;
	}

	return retval;
}
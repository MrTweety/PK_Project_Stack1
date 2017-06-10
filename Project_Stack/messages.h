#ifndef MESSAGES___H
#define  MESSAGES___H

enum MY_MESSAGES
{
	MY_MESS_MEM_ALOC_ERROR,    //0
	MY_MESS_PRINT_ERROR,	   //1	
	MY_MESS_POP_ERROR,
	MY_MESS_FILE_ERROR,
	MY_MESS_TOTAL              //ZAWSZE OSTATNI !!!
};

enum MY_DECISION
{
	MY_DECISION_BREAK,	           //Przerywamy wykonanie programu
	MY_DECISION_PRINT_BREAK,           //Przerywamy wykonanie programu
	MY_DECISION_POP_BREAK,
	MY_DECISION_FILE_BREAK,
	MY_DECISION_CONTINUE,        //Kontynujemy wykonanie
	
};


 enum MY_DECISION my_mess_fun(enum MY_MESSAGES mess);



#endif
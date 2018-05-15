#pragma once
#ifndef MY_INTERFACE___H
#define MY_INTERFACE___H


enum MY_INTERF_EN
{
	INTERF_PUSH,
	INTERF_POP,
	INTER_SEARCH,
	INTER_PRINT_ALL,
	INTER_SAVE,
	INTER_OPEN,
	INTERF_CLEAR,
	INTERF_STOP,
	INTERF_TOT
};

static char *strtab[] =
{
	"0 - push",			//INTERF_PUSH
	"1 - pop",          //INTERF_POP
	"2 - search",      //INTER_SEARCH
	"3 - print all",     //INTER_PRINT_ALL
	"4 - save" ,         //INTER_SAVE
	"5 - open",          //INTER_OPEN
	"6 - clear",		//INTERF_CLEAR
	"7 - finish" ,      //INTERF_STOP
	
};


static char *strtabPL[] =
{
	"0 - dodaj",			//INTERF_PUSH
	"1 - zdejmij ze stosu",          //INTERF_POP
	"2 - szukaj",      //INTER_SEARCH
	"3 - przegladaj",     //INTER_PRINT_ALL
	"4 - zapis na dysk" ,         //INTER_SAVE
	"5 - wczytaj z dysku ",          //INTER_OPEN
	"6 - wyczysc stos ",		//INTERF_CLEAR
	"7 - zakoncz prace" ,      //INTERF_STOP

};


//SF Prawdopodobnie, miejsce temu w interfejsie, a nie w stack'u
enum SEARCH
{
	SEARCH_NAME,
	SEARCH_YEAR,
	SEARCH_FACULTY,
	SEARCH_TOTAL
};

static char *search_tab[] =
{
	"0 - Szukaj wedlug nazwiska",
	"1- Szukaj wedlug roku",
	"2 - Szukaj wedlug kierunku",
};



void MyMenu();
static void push();
static void pop();
//static void topp();
static void search();
static void print_all();
static void save();
static void open();
static void clear();



#endif
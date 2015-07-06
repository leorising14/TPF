#include<stdio.h>
#include"fsm.h"

extern STATE ev1[];
extern STATE ev2[];


void (null) (void);
void (null) (void);
void reset_FSM (void);
void donothing (void);


STATE ev1[]=
{
	{"ev",ev2,donothing},
	{FIN_TABLA,ev1,reset_FSM}
};

STATE ev2[]=
{
	{"ev",ev1,donothing},
	{FIN_TABLA,ev1,reset_FSM}
};

void reset_FSM (void)
{
	printf("Reset");
}

STATE* FSM_GetInitState(void)
{
	return (ev1);
}
void donothing (void)
{
	return;
}


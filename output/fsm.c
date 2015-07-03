#include<stdio.h>
#include"fsm.h"

extern STATE hola[];
extern STATE nuevo[];


void (null) (void);
void reset_FSM (void);


STATE hola[]=
{
	{5,nuevo,(null)},
	{FIN_TABLA,hola,reset_FSM}
}

STATE nuevo[]=
{
	{FIN_TABLA,hola,reset_FSM}
}

void reset_FSM (void)
{
	printf("Reset");
}

STATE* FSM_GetInitState(void)
{
	return (hola);
}

#include<stdio.h>
#include"fsm.h"

extern STATE estado0[];
extern STATE estado1[];


void dummy (void);
void reset_FSM (void);


STATE estado0[]=
{
	{ev1,estado1,dummy},
	{FIN_TABLA,estado0,reset_FSM}
};

STATE estado1[]=
{
	{FIN_TABLA,estado0,reset_FSM}
};

void reset_FSM (void)
{
	printf("Reset");
}

STATE* FSM_GetInitState(void)
{
	return (estado0);
}

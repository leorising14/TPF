#include<stdio.h>
#include"fsm.h"

extern STATE estado1[];
extern STATE estado2[];


void donothing (void);
void reset_FSM (void);


STATE estado1[]=
{
	{"A",estado2,donothing},
	{FIN_TABLA,estado1,reset_FSM}
};

STATE estado2[]=
{
	{"B",estado1,donothing},
	{FIN_TABLA,estado1,reset_FSM}
};

void reset_FSM (void)
{
	printf("Reset");
}

STATE* FSM_GetInitState(void)
{
	return (estado1);
}

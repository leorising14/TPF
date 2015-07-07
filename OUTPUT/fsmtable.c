#include<stdio.h>
#include"fsm.h"

extern STATE estado0[];
extern STATE estado1[];
extern STATE estado2[];
extern STATE estado3[];
extern STATE estado4[];
extern STATE estado5[];


void match (void);
void reset_FSM (void);
void donothing (void);


STATE estado0[]=
{
	{'D',estado1,donothing},
	{FIN_TABLA,estado0,reset_FSM}
};

STATE estado1[]=
{
	{'a',estado2,donothing},
	{FIN_TABLA,estado0,reset_FSM}
};

STATE estado2[]=
{
	{'n',estado3,donothing},
	{FIN_TABLA,estado0,reset_FSM}
};

STATE estado3[]=
{
	{'i',estado4,donothing},
	{FIN_TABLA,estado0,reset_FSM}
};

STATE estado4[]=
{
	{'e',estado5,donothing},
	{FIN_TABLA,estado0,reset_FSM}
};

STATE estado5[]=
{
	{'l',estado0,match},
	{FIN_TABLA,estado0,reset_FSM}
};

void reset_FSM (void)
{
	printf("Reset\n");
}

STATE* FSM_GetInitState(void)
{
	return (estado0);
}

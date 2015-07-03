#include<stdio.h>
#include"fsm.h"

extern STATE 0[];
extern STATE 1[];
extern STATE 2[];
extern STATE 3[];


void hola (void);
void alñkdhf (void);
void 983fasoivy84 (void);
void chau (void);
void hola2 (void);
void reset_FSM (void);


STATE 0[]=
{
	{a,1,hola},
	{t,2,hola2},
	{FIN_TABLA,0,reset_FSM}
}

STATE 1[]=
{
	{s,2,alñkdhf},
	{FIN_TABLA,0,reset_FSM}
}

STATE 2[]=
{
	{d,3,983fasoivy84},
	{FIN_TABLA,0,reset_FSM}
}

STATE 3[]=
{
	{f,0,chau},
	{FIN_TABLA,0,reset_FSM}
}

void reset_FSM (void)
{
	printf("Reset");
}

STATE* FSM_GetInitState(void)
{
	return (0);
}

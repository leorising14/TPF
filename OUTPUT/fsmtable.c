#include<stdio.h>
#include"fsm.h"

extern STATE state0[];
extern STATE state1[];
extern STATE state2[];
extern STATE state3[];


void (null) (void);
void (null) (void);
void (null) (void);
void match (void);
void reset_FSM (void);
void donothing (void);


STATE state0[]=
{
	{"c",state1,donothing},
	{FIN_TABLA,state0,reset_FSM}
};

STATE state1[]=
{
	{"o",state2,donothing},
	{FIN_TABLA,state0,reset_FSM}
};

STATE state2[]=
{
	{"n",state3,donothing},
	{FIN_TABLA,state0,reset_FSM}
};

STATE state3[]=
{
	{"t",state0,match},
	{FIN_TABLA,state0,reset_FSM}
};

void reset_FSM (void)
{
	printf("Reset");
}

STATE* FSM_GetInitState(void)
{
	return (state0);
}
void donothing (void)
{
	return;
}


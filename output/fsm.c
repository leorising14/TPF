#include<stdio.h>
#include"fsm.h"

extern STATE D[];
extern STATE a[];
extern STATE n[];
extern STATE i[];


void f1 (void);
void f2 (void);
void f3 (void);
void (null) (void);
void (null) (void);
void (null) (void);
void reset_FSM (void);


STATE D[]=
{
	{pas1,a,f1},
	{FIN_TABLA,D,reset_FSM}
}

STATE a[]=
{
	{pas2,n,f2},
	{reset,D,(null)},
	{FIN_TABLA,D,reset_FSM}
}

STATE n[]=
{
	{pas3,i,f3},
	{reset,D,(null)},
	{FIN_TABLA,D,reset_FSM}
}

STATE i[]=
{
	{reset,D,(null)},
	{FIN_TABLA,D,reset_FSM}
}

void reset_FSM (void)
{
	printf("Reset");
}STATE* FSM_GetInitState(void)
{
	return (D);
}

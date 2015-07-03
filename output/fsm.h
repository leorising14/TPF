#ifndef FSM_H_
#define FSM_H_


#define FIN_TABLA 0xFF


typedef struct tabla_estado STATE;

struct tabla_estado

{
	char*  evento;
	STATE *prx_estado;
	void (*p_rut_accion)(void);
};

// Interfaz
STATE* fsm(STATE *p_tabla_estado,char* evento_actual);

STATE *FSM_GetInitState(void);

#endif /* FSM_H_ */

 

#include <allegro5/allegro.h>   
#include <allegro5/allegro_font.h>  
#include <stdio.h>

 #include "allegrogetchar.h"

char* getcharallegro(ALLEGRO_DISPLAY* d, ALLEGRO_FONT *fuente, char* str2)   
{   
    ALLEGRO_DISPLAY* displayauxiliar = NULL;
    displayauxiliar = al_create_display(SCREEN_W/2,SCREEN_H/2);
   
    ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();           //creo nuevo evento
    al_register_event_source(q, al_get_keyboard_event_source());  
    al_register_event_source(q, al_get_display_event_source(displayauxiliar));  
    ALLEGRO_USTR* str = al_ustr_new("");            //creo ustring para escribir en allegro
    int pos = (int)al_ustr_size(str);  
    char* mistring;
            
    int quit = 0;  
    while(quit==0)  
    {  
                al_clear_to_color(al_map_rgb_f(0, 0, 0));           //relleno la pantalla en negro asi me doy cuenta de que tengo que escribir
                al_draw_text(fuente,al_map_rgb(255,0,0),SCREEN_W/4,SCREEN_H/4-100,ALLEGRO_ALIGN_CENTER,str2);
                al_draw_ustr(fuente, al_map_rgb(255, 0, 0), SCREEN_W/4,SCREEN_H/4, ALLEGRO_ALIGN_LEFT, str);  //area donde escribo
                al_flip_display();  //muestro lo que escribo
                
                ALLEGRO_EVENT e;  
                al_wait_for_event(q, &e);  
                switch(e.type)  
                {  
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  
                        quit = true;  
                        break;  
                    case ALLEGRO_EVENT_KEY_CHAR:  
                        if(e.keyboard.unichar >= 32)  
                        {  
                            pos += al_ustr_append_chr(str, e.keyboard.unichar);  
                        }  
                        else if(e.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)  
                        {  
                            if(al_ustr_prev(str, &pos))  
                                al_ustr_truncate(str, pos);  
                        }
                        
                        if(e.keyboard.unichar == 13){
                            quit=1;
                        }
                        
                        break;  
                }  
    }  
    if(quit==1){
        mistring= (char *) al_cstr(str);      //TIRA WARNING POR QUE LA FUNCION TRABAJA CON CONST    
    }
    
    al_destroy_event_queue(q);                      //destruyo los displays y el evento que se consumieron en esta funcion
    al_destroy_display(displayauxiliar);
    al_set_target_bitmap(al_get_backbuffer(d));     //vuelvo a poner el buffer en el display original
    
    return(mistring);
            
}

void openinstructions(ALLEGRO_DISPLAY* d, ALLEGRO_FONT *fuente)   
{   
    ALLEGRO_DISPLAY* infodisplay = NULL;
    infodisplay = al_create_display(800,800);
   
    ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();           //creo nuevo evento
    al_register_event_source(q, al_get_keyboard_event_source());  
    al_register_event_source(q, al_get_display_event_source(infodisplay));  
    int quit = 0;              
/*
    FILE *fp;
    char str[1800];

    
    fp = fopen("README.txt","r");
    if( fp == NULL ){
        perror("Error al abrir el archivo README");
    }
*/
    

    while(quit==0)  
    {  
                al_clear_to_color(al_map_rgb(255, 255, 255));           //relleno la pantalla en negro asi me doy cuenta de que tengo que escribir
                al_draw_text(fuente,al_map_rgb(0,0,0),10,10,ALLEGRO_ALIGN_LEFT,"  Manual de Usuario");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,40,ALLEGRO_ALIGN_LEFT,"  Cada vez que se clickea en un botón, se debe ingresar el nombre o");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,70,ALLEGRO_ALIGN_LEFT,"  requisito que el programa necesita para terminar la acción. Por ejemplo,");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,100,ALLEGRO_ALIGN_LEFT,"  si se hace click en el botón ""Agregar Estado"", antes de que aparezca, ");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,130,ALLEGRO_ALIGN_LEFT,"  se pide ingresar el nombre, apreta enter y recién ahí aparece el estado.");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,190,ALLEGRO_ALIGN_LEFT,"  Para borrar un estado, se pedira el nombre del estado, y luego");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,220,ALLEGRO_ALIGN_LEFT,"  el programa procedera a borrarlo.");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,280,ALLEGRO_ALIGN_LEFT,"  ");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,310,ALLEGRO_ALIGN_LEFT,"  Para borrar una transición hay que apretar los estados vinculados");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,340,ALLEGRO_ALIGN_LEFT,"  a la misma e ingresar el evento asociado a ella.");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,400,ALLEGRO_ALIGN_LEFT,"  Para borrar una función, pide el estado de origen, el de destino y");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,430,ALLEGRO_ALIGN_LEFT,"  el evento relacionado a la misma. ");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,490,ALLEGRO_ALIGN_LEFT,"  Es EXTREMADAMENTE necesario que el usuario tenga las funciones que");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,520,ALLEGRO_ALIGN_LEFT,"  ingresa en archivos separados con el mismo nombre que asigna a las");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,550,ALLEGRO_ALIGN_LEFT,"  funciones en el programa.");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,610,ALLEGRO_ALIGN_LEFT,"  Una vez que el usuario esta conforme con la máquina de estado que");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,640,ALLEGRO_ALIGN_LEFT,"  crea, debe apretar el botón ""Generar Makefile"", los archivos que genera");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,670,ALLEGRO_ALIGN_LEFT,"  el programa se encuentran en la carpeta ""OUTPUT"". En caso de que haya");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,700,ALLEGRO_ALIGN_LEFT,"  generado el makefile y no esté conforme, puede editar de nuevo la máquina");
                al_draw_text(fuente,al_map_rgb(0,0,0),10,730,ALLEGRO_ALIGN_LEFT,"  y volver a apretar el botón sin ningun tipo de inconveniente.");
                /*
                if(fgets(str, 1800, fp) != NULL){
                    al_draw_multiline_text(fuente,al_map_rgb(255,0,0),5,5,50,15,ALLEGRO_ALIGN_LEFT,str);        
                }
*/
                al_flip_display();  //muestro lo que escribo
                
                ALLEGRO_EVENT e;  
                al_wait_for_event(q, &e);  
                switch(e.type)  
                {  
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:  
                        quit = true;  
                        break;  
                }  
    }  
    
/*
    fclose(fp);
*/
    
    al_destroy_event_queue(q);                      //destruyo los displays y el evento que se consumieron en esta funcion
    al_destroy_display(infodisplay);
    al_set_target_bitmap(al_get_backbuffer(d));     //vuelvo a poner el buffer en el display original
        
}
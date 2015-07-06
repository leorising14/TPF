 

#include <allegro5/allegro.h>   
 #include <allegro5/allegro_font.h>  

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

/* 
 * File:   main.c
 * Author: Gabriel
 *
 * Created on 6 de junio de 2015, 17:23
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
 
#include "arrdinamico.h"

const float FPS = 60;
const int SCREEN_W = 1000;
const int SCREEN_H = 700;
const int IMG_SIZE = 92;


void agregarestado(int tempestado_x,int tempestado_y, miestado* lista);
void borrarestado(int num_of_block_to_del,miestado *lista);
miestado* leerestado(int num_of_block_to_read, miestado *lista);

int main(int argc, char **argv){
 
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP  *estado1   = NULL;
   ALLEGRO_BITMAP *nuevoestado = NULL;
   ALLEGRO_BITMAP *nuevatransicion = NULL;
   ALLEGRO_BITMAP *nuevafuncion = NULL;
   ALLEGRO_BITMAP *makefile = NULL;
   ALLEGRO_BITMAP *blankspace = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   float estado1_x = SCREEN_W / 2.0 - IMG_SIZE / 2.0;
   float estado1_y = SCREEN_H / 2.0 - IMG_SIZE / 2.0;//lo hago aparecer en el medio
   float bouncer_dx = -4.0, bouncer_dy = 4.0; //velocidad de la pelotita
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   int mousestate = 0;
   int newstate = 0;
   int newtransicion = 0;
   int newfunction = 0;
   
   int var=0;
   int n=0;
   miestado* listadeestados;
   listadeestados = NULL;
   //miestado newestado1;
   //newestado1.estado_x = SCREEN_W / 2.0 - IMG_SIZE / 2.0;
   //newestado1.estado_y = SCREEN_H / 2.0 - IMG_SIZE / 2.0;

   //listadeestados = &newestado1;
   
   
   
   if(!al_init()) {
      al_show_native_message_box(display, "Error", "Error", "No se pudo inicializar allegro!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   
    if(!al_install_keyboard()) {
   fprintf(stderr, "No se pudo inicializar el teclado!\n");
    return -1;
 }
 
   if(!al_init_image_addon()) {       //IMPORTANTÍSIMO!!!!!!!!!!
        al_show_native_message_box(display, "Error", "Error", "No se pudo inicializar al_init_image_addon!", 
                              NULL, ALLEGRO_MESSAGEBOX_ERROR);
     return 0;
 }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "No se pudo crear el timer!\n");
      return -1;
   }
   
   if(!al_install_mouse()) {
      fprintf(stderr, "No se pudo inicializar el mouse!\n");
      return -1;
   }
   
   display = al_create_display(SCREEN_W,SCREEN_H);
   if(!display) {
      al_show_native_message_box(display, "Error", "Error", "No se pudo inicializar el display!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
 
  // newestado1.estadoimg = al_load_bitmap("estado1.png");
   nuevoestado = al_load_bitmap("nuevoestado.png");
   nuevafuncion = al_load_bitmap("nuevafuncion.png");
   nuevatransicion = al_load_bitmap("nuevatransicion.png");
   makefile = al_load_bitmap("makefile.png");
   blankspace = al_load_bitmap("blankspace.png");
   
   if(!nuevoestado || !nuevafuncion || !nuevatransicion || !makefile) {
      fprintf(stderr, "No se pudieron crear los bitmaps!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
  
   //if(!newestado1.estadoimg) {
    //  fprintf(stderr, "No se pudieron crear los bitmaps!\n");
    //  al_destroy_display(display);
    //  al_destroy_timer(timer);
    //  return -1;
  // }
   
   al_set_target_bitmap(al_get_backbuffer(display));
   
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(estado1);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source()); //meti los tres eventos en la misma cola

   al_register_event_source(event_queue, al_get_mouse_event_source());
    al_init_primitives_addon();

   al_clear_to_color(al_map_rgb(255,255,255));
 
   al_flip_display(); 
 
   al_start_timer(timer); //no olvidar!!!!!
 
    while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;//redibujo cuando toca el timer
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
       
          for(n=0;n<1;n++){
       if(((ev.mouse.x)<(leerestado(n,listadeestados)->estado_x+92)) && (((ev.mouse.y)<(leerestado(n,listadeestados)->estado_y+92))) 
               && ((leerestado(n,listadeestados)->estado_x)<ev.mouse.x) && ((leerestado(n,listadeestados)->estado_y)<ev.mouse.y)){
            mousestate = 1;
       }
       }
       if(((ev.mouse.x)<(725+250)) && (((ev.mouse.y)<(150+54))) && ((725)<ev.mouse.x) && ((150)<ev.mouse.y)){
            newstate = 1;
       }
       
       if(((ev.mouse.x)<(725+250)) && (((ev.mouse.y)<(250+54))) && ((725)<ev.mouse.x) && ((250)<ev.mouse.y)){
            newtransicion = 1;
       }
       
       if(((ev.mouse.x)<(725+250)) && (((ev.mouse.y)<(350+54))) && ((725)<ev.mouse.x) && ((350)<ev.mouse.y)){
            newfunction = 1;
       }
       
      }else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
          mousestate = 0;
      }else if((mousestate == 1)){
          //printf("El mouse esta en: %d\n",ev.mouse.x);        //Para pruebas
          for(n=0;n<1;n++){
          leerestado(n,listadeestados)->estado_x = (ev.mouse.x)-46;
          leerestado(n,listadeestados)->estado_y = (ev.mouse.y)-46;
          }
      }else if(ev.type == ALLEGRO_EVENT_KEY_UP){
          switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;              
          }
      }else if((newstate == 1)){
          printf("Agregue estado\n");
          var=1;
          agregarestado(SCREEN_W / 2.0 - IMG_SIZE / 2.0, SCREEN_H / 2.0 - IMG_SIZE / 2.0,listadeestados);
          for(n=0;n<1;n++){
             leerestado(n,listadeestados)->estadoimg = al_load_bitmap("estado1.png");      
          }

          al_draw_bitmap(blankspace, 725, 250, 0);
          newstate=0;
      }else if((newtransicion == 1)){
          printf("Aregue transicion\n");
      }else if((newfunction == 1)){
          printf("Agregue funcion\n");
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false; //cando ya dibuje, espero de nuevo al timer
 
         al_clear_to_color(al_map_rgb(255,255,255));
         if(var==1)
         {
             for(n=0;n<1;n++){
                al_draw_bitmap(leerestado(n,listadeestados)->estadoimg, leerestado(n,listadeestados)->estado_x, leerestado(n,listadeestados)->estado_y, 0);
             } 
         }
         al_draw_bitmap(nuevoestado, 725, 150, 0);
         al_draw_bitmap(nuevatransicion, 725, 250, 0);
         al_draw_bitmap(nuevafuncion, 725, 350, 0);
         al_draw_bitmap(makefile, 725, 500, 0);
         
         al_draw_line(estado1_x,estado1_y,40,50,al_map_rgb(0,255,0),2);
 
         al_flip_display();
      }
   }

   
   al_destroy_bitmap(estado1);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}

void agregarestado(int tempestado_x,int tempestado_y, miestado* lista) //lista es el  puntero al primer elemento, NO SE PUEDE TOCAR
{
    int i;
    miestado* temp=(miestado *) calloc(1,sizeof(miestado));
    miestado* recorrer = lista;
    if(!lista->next)
    {
    lista->cont=0;
    lista->next=temp;
    (temp->estado_x)=tempestado_x;
    (temp->estado_y)=tempestado_y;
    (temp->estadoimg)=al_load_bitmap("estado1.png");
    temp->next=NULL;
    }else {
    for(i=0;(recorrer->next)!=NULL;recorrer=(recorrer->next)) //el for solo recorre la lista
    {
        i++;
    }
    temp->cont=i;
    recorrer->next=temp;
    (temp->estado_x)=tempestado_x;
    (temp->estado_y)=tempestado_y;
    (temp->estadoimg)=al_load_bitmap("estado1.png");
    temp->next=NULL;
  }
}

void borrarestado(int num_of_block_to_del,miestado *lista){
miestado *recorrer=lista;
miestado *bup=lista;
for (;(recorrer->cont)<(num_of_block_to_del-1);recorrer=recorrer->next){
}
bup=recorrer;
recorrer=recorrer->next;
bup->next=recorrer->next;
free(recorrer);
}

miestado* leerestado(int num_of_block_to_read, miestado *list){
miestado *recorrer1=list;
for(;(recorrer1->cont)<(num_of_block_to_read);recorrer1=(recorrer1->next));
return recorrer1;
}


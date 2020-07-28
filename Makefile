################################################
CC = gcc
OPTIONS = -O2 -g -Wall   # -g for debug, -O2 for optimise and -Wall additional messages

################################################
LDLIBSOPTIONS =`pkg-config --libs allegro-5` `pkg-config --libs allegro_acodec-5` `pkg-config --libs allegro_audio-5` `pkg-config --libs allegro_color-5` `pkg-config --libs allegro_dialog-5` `pkg-config --libs allegro_font-5` `pkg-config --libs allegro_image-5` `pkg-config --libs allegro_main-5` `pkg-config --libs allegro_memfile-5` `pkg-config --libs allegro_physfs-5` `pkg-config --libs allegro_primitives-5` `pkg-config --libs allegro_ttf-5` `pkg-config --libs allegro_video-5`

################################################
EVENTQ_OBJECT = /Backend/event_queque/event_queque.o

################################################
HFRONT_ALL = /Frontend/Allegro/headall.h
HFRONT_RAS = /Frontend/Raspi/headras.h

################################################
OBJS = main.o PORTS.o

allegro: Backend\FSM_table.h Backend\main.c ingame_stats.o scoretable.o FSM_routines.o const.h
	${CC} ${OPTIONS} ${OBJS} main.c -o spg 

#space_invaders_debug: main.o 
#	${CC} ${OPTIONS} ${OBJS} -o main_d -D DEBUG

ingame_stats: Backend/ingame_stats.c Backend/ingame_stats.h const.h
	${CC} ${OPTIONS} ${OBJS} -c ingame_stats.c

scoretable: Backend/scoretable.c Backend/scoretable.h
	${CC} ${OPTIONS} ${OBJS} -c scoretable.c

FSM_routines: Backend/FSM_routines.h Backend/FSM_routines.c ${EVENTQ_OBJECT} const.h ${HFRONT_ALL}
	${CC} ${OPTIONS} ${OBJS} -c scoretable.c 

event_queue: Backend/event_queue/event_queue.c Backend/event_queue/event_queue.h 
	${CC} ${OPTIONS} ${OBJS} -c event_queue.c 

menu_front: menu_front.c headall.h ${EVENTQ_OBJECT}
	${CC} ${OPTIONS} ${LDLIBSOPTIONS} -c menu_front.c


#raspi: Backend\FSM_talbe.h main.c ingame_stats.o scoretable.o FSM_routines.o ${HFRONT_RAS}
#	${CC} ${OPTIONS} ${OBJS} main.c -o spg -D RASPI



clean: 
	rm *.o

#https://hernandis.me/2017/03/20/como-hacer-un-makefile.html#:~:text=GNU%20make%20es%20una%20utilidad,al%20final%20hace%20lo%20mismo.

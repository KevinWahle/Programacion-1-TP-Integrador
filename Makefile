################################################
CC = gcc
OPTIONS = -O2 -g -Wall -D DEBUG  # -g for debug, -O2 for optimise and -Wall additional messages

################################################
LDLIBSOPTIONS =`pkg-config --libs allegro-5` `pkg-config --libs allegro_acodec-5` `pkg-config --libs allegro_audio-5` `pkg-config --libs allegro_color-5` `pkg-config --libs allegro_dialog-5` `pkg-config --libs allegro_font-5` `pkg-config --libs allegro_image-5` `pkg-config --libs allegro_main-5` `pkg-config --libs allegro_memfile-5` `pkg-config --libs allegro_physfs-5` `pkg-config --libs allegro_primitives-5` `pkg-config --libs allegro_ttf-5` `pkg-config --libs allegro_video-5`

################################################
EVENTQ_OBJECT = Backend/event_queue/event_queue.o

################################################
HFRONT_ALL = Frontend/Allegro/headall.h
HFRONT_RAS = Frontend/Raspi/headras.h

################################################
OBJS = Backend/main.o Backend/ingame_stats.o Backend/scoretable.o Backend/FSM_routines.o Frontend/Allegro/menu_front.o ${EVENTQ_OBJECT}

allegro: ${OBJS} 
	${CC} ${OPTIONS} ${OBJS} ${LDLIBSOPTIONS} -o game

#space_invaders_debug: main.o 
#	${CC} ${OPTIONS} ${OBJS} -o main_d -D DEBUG

main.o: Backend/main.c Backend/FSM_table.h Backend/FSM_routines.h Backend/event_queue/event_queue.h const.h
	${CC} ${OPTIONS} -c Backend/main.c -D DEBUG
	
ingame_stats.o: Backend/ingame_stats.c Backend/ingame_stats.h const.h
	${CC} ${OPTIONS} -c Backend/ingame_stats.c 

scoretable.o: Backend/scoretable.c Backend/scoretable.h
	${CC} ${OPTIONS} -c Backend/scoretable.c

FSM_routines.o: Backend/FSM_routines.c Backend/FSM_routines.h const.h Backend/event_queue/event_queue.h ${HFRONT_ALL}
	${CC} ${OPTIONS} -c Backend/FSM_routines.c

event_queue.o: Backend/event_queue/event_queue.c Backend/event_queue/event_queue.h 
	${CC} ${OPTIONS} -c Backend/event_queue/event_queue.c 

menu_front.o: Frontend/Allegro/menu_front.c ${HFRONT_ALL} Backend/event_queue/event_queue.h
	${CC} ${OPTIONS} ${LDLIBSOPTIONS} -c Frontend/Allegro/menu_front.c


#raspi: Backend\FSM_talbe.h main.c ingame_stats.o scoretable.o FSM_routines.o ${HFRONT_RAS}
#	${CC} ${OPTIONS} ${OBJS} main.c -o spg -D RASPI


clean: 
	rm Backend/*.o
	rm Frontend/Allegro/*.o

clean_eq:
	rm Backend/event_queue/*.o
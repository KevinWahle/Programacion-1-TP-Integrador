################################################
CC = gcc -D PRUEBA
OPTIONS = -O2 -g -Wall # -g for debug, -O2 for optimise and -Wall additional messages

################################################
LDLIBSOPTIONS =`pkg-config --libs allegro-5` `pkg-config --libs allegro_acodec-5` `pkg-config --libs allegro_audio-5` `pkg-config --libs allegro_color-5` `pkg-config --libs allegro_dialog-5` `pkg-config --libs allegro_font-5` `pkg-config --libs allegro_image-5` `pkg-config --libs allegro_main-5` `pkg-config --libs allegro_memfile-5` `pkg-config --libs allegro_physfs-5` `pkg-config --libs allegro_primitives-5` `pkg-config --libs allegro_ttf-5` `pkg-config --libs allegro_video-5`

################################################
EVENTQ_OBJECT = Backend/event_queue/event_queue.o
EVENTQ_HEAD = Backend/event_queue/event_queue.h
################################################
HFRONT_ALL = Frontend/Allegro/headall.h 
HFRONT_RAS = Frontend/Raspi/headras.h

################################################
OBJS = Backend/main.o Backend/ingame_stats.o Backend/scoretable.o Backend/FSM_routines.o Frontend/Allegro/menu_front.o Frontend/Allegro/game_front.c ${EVENTQ_OBJECT}

game: ${OBJS} 
	${CC} ${OPTIONS} ${OBJS} ${LDLIBSOPTIONS} -o game

#space_invaders_debug: main.o 
#	${CC} ${OPTIONS} ${OBJS} -o main_d -D DEBUG

main.o: Backend/main.c Backend/FSM_table.h Backend/FSM_routines.h ${EVENTQ_OBJECT} const.h
	${CC} ${OPTIONS} -c Backend/main.c
	
ingame_stats.o: Backend/ingame_stats.c Backend/ingame_stats.h const.h
	${CC} ${OPTIONS} -c Backend/ingame_stats.c 

scoretable.o: Backend/scoretable.c Backend/scoretable.h
	${CC} ${OPTIONS} -c Backend/scoretable.c

FSM_routines.o: Backend/FSM_routines.c Backend/FSM_routines.h ${EVENTQ_HEAD} Backend/scoretable.h Backend/ingame_stats.h ${HFRONT_ALL} const.h
	${CC} ${OPTIONS} -c Backend/FSM_routines.c

menu_front.o: Frontend/Allegro/menu_front.c ${HFRONT_ALL} ${EVENTQ_HEAD} Frontend/Allegro/shared_res.h const.h
	${CC} ${OPTIONS} -c Frontend/Allegro/menu_front.c

game_front.o: Frontend/Allegro/menu_front.c ${HFRONT_ALL} ${EVENTQ_HEAD} Frontend/Allegro/shared_res.h const.h
	${CC} ${OPTIONS} -c Frontend/Allegro/game_front.c

################################################Terminar raspi
# raspi: Backend\FSM_talbe.h main.c ingame_stats.o scoretable.o FSM_routines.o ${HFRONT_RAS}
# 	${CC} ${OPTIONS} ${OBJS} main.c -o spg -D RASPI

# scoretable.o: Backend/scoretable.c Backend/scoretable.h
# 	${CC} ${OPTIONS} -c Backend/scoretable.c

# menu_front.o: Frontend/Raspi/menu_front.c ${HFRONT_RAS} Backend/event_queue/event_queue.h
# 	${CC} ${OPTIONS} -c Frontend/Raspi/menu_front.c

################################################

# allegro: Frontend/Allegro/game_front.o Frontend/Allegro/menu_front.o ${EVENTQ_OBJECT}
# 	gcc Frontend/Allegro/game_front.o  Frontend/Allegro/menu_front.o ${EVENTQ_OBJECT} ${LDLIBSOPTIONS} -Wall -o allegro

# game_front.o: Frontend/Allegro/menu_front.c ${HFRONT_ALL} ${EVENTQ_HEAD} Frontend/Allegro/shared_res.h const.h
# 	${CC} ${OPTIONS} ${LDLIBSOPTIONS} -c Frontend/Allegro/game_front.c

# menu_front.o: Frontend/Allegro/menu_front.c ${HFRONT_ALL} ${EVENTQ_HEAD} Frontend/Allegro/shared_res.h const.h
# 	${CC} ${OPTIONS} ${LDLIBSOPTIONS} -c Frontend/Allegro/menu_front.c

################################################
event_queue.o: Backend/event_queue/event_queue.c Backend/event_queue/event_queue.h 
	${CC} ${OPTIONS} -c Backend/event_queue/event_queue.c 

clean: 
	rm Backend/*.o
	rm Frontend/Allegro/*.o

clean_eq:
	rm Backend/event_queue/*.o
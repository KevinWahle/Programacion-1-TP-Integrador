################################################
CC = gcc
DEFINE_DEBUG = -D DEBUG
DEFINE_ALL = -D PLATFORM=ALLEGRO
DEFINE_RASPI = -D PLATFORM=RASPI
OPTIONS = -g -Wall	# -g for debug, -O2 for optimise and -Wall additional messages
################################################
ALLLINUXLIB =`pkg-config --libs allegro-5` `pkg-config --libs allegro_acodec-5` `pkg-config --libs allegro_audio-5` `pkg-config --libs allegro_color-5` `pkg-config --libs allegro_dialog-5` `pkg-config --libs allegro_font-5` `pkg-config --libs allegro_image-5` `pkg-config --libs allegro_main-5` `pkg-config --libs allegro_memfile-5` `pkg-config --libs allegro_physfs-5` `pkg-config --libs allegro_primitives-5` `pkg-config --libs allegro_ttf-5` `pkg-config --libs allegro_video-5`
ALLWINLIB = -l allegro -l allegro_audio -l allegro_acodec -l allegro_color -l allegro_font -l allegro_image -l allegro_primitives -l allegro_ttf
RPILINUXLIB = ../libs/joydisp/disdrv.h ../libs/joydisp/joydrv.h
RPILIBS = -I/usr/local/include -L/usr/local/lib -lSDL2 -lpthread
################################################
EVENTQ_OBJECT = Backend/event_queue/event_queue.o
EVENTQ_HEAD = Backend/event_queue/event_queue.h
################################################
TIMER_OBJECT = Frontend/Raspi/timer/timer.o
TIMER_HEAD	= Frontend/Raspi/timer/timer.h
###############################################
HFRONT_ALL = Frontend/Allegro/headall.h
HFRONT_RAS = Frontend/Raspi/headall.h
################################################
OBJS = Backend/main.o Backend/ingame_stats.o Backend/scoretable.o Backend/FSM_routines.o Frontend/Allegro/menu_front.o Frontend/Allegro/game_front.o ${EVENTQ_OBJECT}
OBJS2 = Backend/main.o Backend/ingame_stats.o Backend/scoretable.o Backend/FSM_routines.o Frontend/Raspi/menu_front.o Frontend/Raspi/game_front.o ${EVENTQ_OBJECT} ${TIMER_OBJECT} ../libs/joydisp/disdrv.o ../libs/joydisp/joydrv.o ../libs/audio/SDL2/libAudioSDL2.o
################################################


################# ALLEGRO ######################
gameall: OPTIONS += ${DEFINE_ALL}					# target variable: se define para todas las dependencias
gameall: ${OBJS}
	${CC} ${OPTIONS} ${OBJS} ${ALLLINUXLIB} -o gameall
################################################

################## RASPI #######################
gameraspi: OPTIONS += ${DEFINE_RASPI}				# target variable: se define para todas las dependencias
gameraspi: ${OBJS2}
	${CC} ${OPTIONS} ${OBJS2} ${RPILIBS} -o gameraspi
################################################

# Para Windows, se compila con las librerias de otra manera
win: OPTIONS += ${DEFINE_ALL}					# target variable: se define para todas las dependencias
win: ${OBJS}
	${CC} ${OPTIONS} ${OBJS} ${ALLWINLIB} -o game
#

################## MAIN BACK ########################
Backend/main.o: Backend/main.c Backend/FSM_table.h Backend/FSM_routines.h ${HFRONT_RAS} ${HFRONT_ALL} ${EVENTQ_HEAD} Backend/scoretable.h const.h
	${CC} ${OPTIONS} -c Backend/main.c -o Backend/main.o

Backend/ingame_stats.o: Backend/ingame_stats.c Backend/ingame_stats.h ${HFRONT_RAS} ${HFRONT_ALL} ${EVENTQ_HEAD} Backend/scoretable.h const.h
	${CC} ${OPTIONS} -c Backend/ingame_stats.c -o Backend/ingame_stats.o

Backend/scoretable.o: Backend/scoretable.c Backend/scoretable.h const.h
	${CC} ${OPTIONS} -c Backend/scoretable.c -o Backend/scoretable.o

Backend/FSM_routines.o: Backend/FSM_routines.c Backend/FSM_routines.h ${HFRONT_RAS} ${HFRONT_ALL} ${EVENTQ_HEAD} Backend/scoretable.h Backend/ingame_stats.h const.h
	${CC} ${OPTIONS} -c Backend/FSM_routines.c -o Backend/FSM_routines.o

Backend/event_queue/event_queue.o: Backend/event_queue/event_queue.c ${EVENTQ_HEAD}
	${CC} ${OPTIONS} -c Backend/event_queue/event_queue.c -o ${EVENTQ_OBJECT}

################## ALLEGRO FRONT ########################
Frontend/Allegro/menu_front.o: Frontend/Allegro/menu_front.c ${HFRONT_ALL} ${EVENTQ_HEAD} Frontend/Allegro/shared_res.h const.h
	${CC} ${OPTIONS} -c Frontend/Allegro/menu_front.c -o Frontend/Allegro/menu_front.o

Frontend/Allegro/game_front.o: Frontend/Allegro/game_front.c ${HFRONT_ALL} ${EVENTQ_HEAD} Frontend/Allegro/shared_res.h const.h
	${CC} ${OPTIONS} -c Frontend/Allegro/game_front.c -o Frontend/Allegro/game_front.o

################## RASPI FRONT ########################
Frontend/Raspi/game_front.o: Frontend/Raspi/game_front.c ${HFRONT_RAS} ${RPILINUXLIB} ${EVENTQ_HEAD} Frontend/Raspi/shared_res.h const.h
	${CC} ${OPTIONS} -c Frontend/Raspi/game_front.c -o Frontend/Raspi/game_front.o

Frontend/Raspi/menu_front.o: Frontend/Raspi/menu_front.c ${HFRONT_RAS} ${RPILINUXLIB} ${EVENTQ_HEAD} Frontend/Raspi/shared_res.h const.h
	${CC} ${OPTIONS} -c Frontend/Raspi/menu_front.c -o Frontend/Raspi/menu_front.o

Frontend/Raspi/timer/timer.o: Frontend/Raspi/timer/timer.c ${TIMER_HEAD}
	${CC} ${OPTIONS} -c Frontend/Raspi/timer/timer.c -o Frontend/Raspi/timer/timer.o
#################################################

cleanall:
	rm Backend/*.o
	rm Backend/event_queue/*.o
	rm Frontend/Allegro/*.o

cleanrpi:
	rm Backend/*.o
	rm Backend/event_queue/*.o
	rm Frontend/Raspi/*.o
	rm Frontend/Raspi/timer/*.o

cleanwin:
	del *.o /S
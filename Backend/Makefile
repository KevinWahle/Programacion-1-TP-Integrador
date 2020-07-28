CC = gcc 
LDLIBSOPTIONS =`pkg-config --libs allegro-5` `pkg-config --libs allegro_acodec-5` `pkg-config --libs allegro_audio-5` `pkg-config --libs allegro_color-5` `pkg-config --libs allegro_dialog-5` `pkg-config --libs allegro_font-5` `pkg-config --libs allegro_image-5` `pkg-config --libs allegro_main-5` `pkg-config --libs allegro_memfile-5` `pkg-config --libs allegro_physfs-5` `pkg-config --libs allegro_primitives-5` `pkg-config --libs allegro_ttf-5` `pkg-config --libs allegro_video-5`
OPTIONS = -O2 -g -Wall   # -g for debug, -O2 for optimise and -Wall additional messages
OBJS = main.o PORTS.o

space_invaders: 
	${CC} ${OPTIONS} ${OBJS} main.c -o space_invaders 

#space_invaders_debug: main.o 
#	${CC} ${OPTIONS} ${OBJS} -o main_d -D DEBUG



ingame_stats: Backend/ingame_stats.c Backend/ingame_stats.h const.h
${CC} ${OPTIONS} ${OBJS} -c ingame_stats

scoretable: Backend/scoretable.c Backend/scoretable.h
${CC} ${OPTIONS} ${OBJS} -c scoretable



menu_front: menu_front.c headall.h 
	${CC} ${OPTIONS} ${LDLIBSOPTIONS} -c menu_front.c

	
clean: 
	rm *.o

#https://hernandis.me/2017/03/20/como-hacer-un-makefile.html#:~:text=GNU%20make%20es%20una%20utilidad,al%20final%20hace%20lo%20mismo.
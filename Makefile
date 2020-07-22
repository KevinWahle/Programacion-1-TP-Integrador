CC = gcc 
LDLIBSOPTIONS =`pkg-config --libs allegro-5` `pkg-config --libs allegro_acodec-5` `pkg-config --libs allegro_audio-5` `pkg-config --libs allegro_color-5` `pkg-config --libs allegro_dialog-5` `pkg-config --libs allegro_font-5` `pkg-config --libs allegro_image-5` `pkg-config --libs allegro_main-5` `pkg-config --libs allegro_memfile-5` `pkg-config --libs allegro_physfs-5` `pkg-config --libs allegro_primitives-5` `pkg-config --libs allegro_ttf-5` `pkg-config --libs allegro_video-5`
OPTIONS = -O2 -g -Wall   # -g for debug, -O2 for optimise and -Wall additional messages
OBJS = main.o PORTS.o ${LDLIBSOPTIONS}

mainall: main.o PORTS.o
	${CC} ${OPTIONS} ${OBJS} -o main 

main.o: main.c PORTS.h
	${CC} ${OPTIONS} -c main.c 



mainraspi: main.o PORTS.o
	${CC} ${OPTIONS} ${OBJS} -o main


clean: 
	rm *.o

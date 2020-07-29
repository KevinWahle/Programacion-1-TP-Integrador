#ESTE MAKE ES SOLO PARA PROBAR EL JUEGO SOLO

LDLIBSOPTIONS =`pkg-config --libs allegro-5` `pkg-config --libs allegro_acodec-5` `pkg-config --libs allegro_audio-5` `pkg-config --libs allegro_color-5` `pkg-config --libs allegro_dialog-5` `pkg-config --libs allegro_font-5` `pkg-config --libs allegro_image-5` `pkg-config --libs allegro_main-5` `pkg-config --libs allegro_memfile-5` `pkg-config --libs allegro_physfs-5` `pkg-config --libs allegro_primitives-5` `pkg-config --libs allegro_ttf-5` `pkg-config --libs allegro_video-5`

HEAD_ALL = ../../const.h ../../Backend/scoretable.h ../../Backend/event_queue/event_queue.h

game: game_front.o menu_front.o ../../Backend/event_queue/event_queue.o
	gcc game_front.o  menu_front.o ../../Backend/event_queue/event_queue.o ${LDLIBSOPTIONS} -Wall -o game

game_front.o: game_front.o shared_res.h headall.h ${HEAD_ALL} 
	gcc -D PRUEBA -Wall -c game_front.c

menu_front.o: menu_front.c shared_res.h headall.h ${HEAD_ALL}
	gcc -Wall -c menu_front.c

clean: 
	rm *.o

echo Compilando...
@echo off
REM Uso: compile "source" "target". Ej: compile main.c main
gcc %1 -Wall -o %2 -l allegro -l allegro_audio -l allegro_acodec -l allegro_color -l allegro_font -l allegro_image -l allegro_primitives -l allegro_ttf
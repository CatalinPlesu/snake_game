programa:
	gcc -O0 -g main.c sdl_cat.c snake_logic.c `sdl2-config --cflags --libs` -lSDL2_gfx 
	./a.out

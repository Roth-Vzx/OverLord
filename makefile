all:
	g++ -Iinclude -Iinclude/sdl -Iheaders -Llib -o Main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
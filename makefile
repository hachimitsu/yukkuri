main.exe: game.o game_cleanup.o game_events.o game_init.o game_loop.o game_render.o vector3f.o Maths.o Camera.o
	g++ -w -g game.o game_cleanup.o game_events.o game_init.o game_loop.o game_render.o Camera.o vector3f.o Maths.o -o main.exe -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -static-libgcc -static-libstdc++

game.o: src/game.cpp src/game.h
	g++ -g -c src/game.cpp

game_cleanup.o: src/game_cleanup.cpp src/game.h
	g++ -g -c src/game_cleanup.cpp

game_events.o: src/game_events.cpp src/game.h
	g++ -g -c src/game_events.cpp

game_init.o: src/game_init.cpp src/game.h
	g++ -g -c src/game_init.cpp

game_loop.o: src/game_loop.cpp src/game.h
	g++ -g -c src/game_loop.cpp

game_render.o: src/game_render.cpp src/game.h
	g++ -g -c src/game_render.cpp

Camera.o: src/Camera.h src/Camera.cpp
	g++ -g -c src/Camera.cpp

vector3f.o: src/Math/vector3f.h src/Math/vector3f.cpp
	g++ -w -g -c src/Math/vector3f.cpp

Maths.o: src/Math/Maths.h src/Math/Maths.cpp
	g++ -w -g -c src/Math/Maths.cpp
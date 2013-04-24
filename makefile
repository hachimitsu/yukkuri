DIR=src
ODIR=obj
CC = g++
PFLAGS = -O3 -ffast-math -g -c -w
CFLAGS = -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -static-libgcc -static-libstdc++

_GAME_DEP = game.h
_GAME_OBJ = game.o game_cleanup.o game_events.o game_init.o game_loop.o game_render.o
GAME_DEP = $(patsubst %,$(DIR)/%,$(_GAME_DEP))
GAME_OBJ = $(patsubst %,$(ODIR)/%,$(_GAME_OBJ)) 
OBJ = $(ODIR)/Camera.o $(ODIR)/vector3f.o $(ODIR)/Maths.o $(ODIR)/quaternion.o

main.exe: $(GAME_OBJ) $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

$(ODIR)/%.o: $(DIR)/%.cpp $(GAME_DEP)
	$(CC) $(PFLAGS) $< -o $@

$(ODIR)/Camera.o: $(DIR)/Camera/Camera.h $(DIR)/Camera/Camera.cpp
	$(CC) $(PFLAGS) $(DIR)/Camera/Camera.cpp -o $(ODIR)/Camera.o

$(ODIR)/vector3f.o: $(DIR)/Math/vector3f.h $(DIR)/Math/vector3f.cpp
	$(CC) $(PFLAGS) $(DIR)/Math/vector3f.cpp -o $(ODIR)/vector3f.o

$(ODIR)/Maths.o: $(DIR)/Math/Maths.h $(DIR)/Math/Maths.cpp
	$(CC) $(PFLAGS) $(DIR)/Math/Maths.cpp -o $(ODIR)/Maths.o 

$(ODIR)/quaternion.o: $(DIR)/Math/quaternion.h $(DIR)/Math/quaternion.cpp
	$(CC) $(PFLAGS) $(DIR)/Math/quaternion.cpp -o $(ODIR)/quaternion.o 

clean:
	rm $(ODIR)/*.o

cleanall:
	rm $(ODIR)/*.o main.exe
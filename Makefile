VER = g++ -std=c++11
OBJ1 = main.o
OBJ2 = application.o
OBJ3 = bars.o
PROJECT = main

$(PROJECT): $(OBJ1) $(OBJ2) $(OBJ3)
		$(VER) $(OBJ1) $(OBJ2) $(OBJ3) -o $(PROJECT) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(OBJ1): globals.h
	 	$(VER) -c main.cpp -o $(OBJ1) -I.

$(OBJ2): globals.h application.h bars.h
		$(VER) -c application.cpp -o $(OBJ2)

$(OBJ3): globals.h bars.h
		$(VER) -c bars.cpp -o $(OBJ3)

clean:
		@rm -f $(OBJ1)
		@rm -f $(OBJ2)
		@rm -f $(OBJ3)
		@rm -f $(PROJECT)

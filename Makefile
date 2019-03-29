VER = g++ -std=c++11
OBJ1 = main.o
OBJ2 = application.o
PROJECT = main

$(PROJECT): $(OBJ1) $(OBJ2)
		$(VER) $(OBJ1) $(OBJ2) -o $(PROJECT) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(OBJ1): globals.h application.h
	 	$(VER) -c main.cpp -o $(OBJ1)

$(OBJ2): globals.h application.h
		$(VER) -c application.cpp -o $(OBJ2)

clean:
		@rm -f $(OBJ1)
		@rm -f $(OBJ2)
		@rm -f $(PROJECT)

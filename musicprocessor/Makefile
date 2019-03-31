VER = g++ -std=c++11
OBJ1 = test.o
OBJ2 = music.o
PROJECT = test

$(PROJECT): $(OBJ1) $(OBJ2)
		$(VER) $(OBJ1) $(OBJ2) -o $(PROJECT) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
$(OBJ1): globals.h musicprocessor.h
	 	$(VER) -c test.cpp -o $(OBJ1)
$(OBJ2): musicprocessor.h
	$(VER) -c musicprocessor.cpp -o $(OBJ2)

clean:
		@rm -f $(OBJ1)
		@rm -f $(OBJ2)
		@rm -f $(PROJECT)

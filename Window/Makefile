VER = g++ -std=c++11
OBJ = test.o
PROJECT = test

$(PROJECT): $(OBJ)
		$(VER) $(OBJ) -o $(PROJECT) -lsfml-window -lsfml-system -lsfml-graphics -lGL -lGLEW
$(OBJ):
	 	$(VER) -c basic_window.cpp -o $(OBJ)
clean:
		@rm -f $(OBJ)
		@rm -f $(PROJECT)

VER = g++ -std=c++11
OBJ = test.o
PROJECT = test

$(PROJECT): $(OBJ)
		$(VER) $(OBJ) -o $(PROJECT) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
$(OBJ):
	 	$(VER) -c main.cpp -o $(OBJ)
clean:
		@rm -f $(OBJ)
		@rm -f $(PROJECT)

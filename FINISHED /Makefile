# NAMES : CYRUS DIEGO and DANIEL ROJAS-CARDONA
# ID : 1528911 and 1531475
# CMPUT 275 WINTER 2019
#
# FINAL PROJECT : FFT VISUALIZER
# Makefile used to compile and build project
#-------------------------------------------------------------------------------
VER = g++ -std=c++11
OBJ1 = main.o
OBJ2 = app.o
OBJ3 = bar.o
OBJ4 = music.o
PROJECT = main
DEPEND = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pthread

$(PROJECT): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4)
		$(VER) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) -o $(PROJECT) $(DEPEND)

$(OBJ1): globals.h
	 	$(VER) -c main.cpp -o $(OBJ1) -I.

$(OBJ2): globals.h musicprocessor.h barSpectrum.h
		$(VER) -c application.cpp -o $(OBJ2) -I.

$(OBJ3): globals.h
		$(VER) -c barSpectrum.cpp -o $(OBJ3) -I.

$(OBJ4): globals.h
		$(VER) -c musicprocessor.cpp -o $(OBJ4) -I.

clean:
		@rm -f $(OBJ1)
		@rm -f $(OBJ2)
		@rm -f $(OBJ3)
		@rm -f $(OBJ4)
		@rm -f $(PROJECT)

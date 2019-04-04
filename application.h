/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.h : header file declaring application class
*/

#ifndef APPLICATION_H
#define APPLICATION_H
#include "globals.h"
#include "barSpectrum.h"
#include "musicprocessor.h"
/*
    application class that holds the window instantiating, keyboard input,
    and the application running
*/
class application {
public:
    application(const std::string title);
    ~application();
    void run();


private:
    void processEvents();
    void updateScreen();
    void renderScreen();
    void getNextSample();
    void setup();
    void printFFTStateText();
    void printCurrentSongText();
    void printInstructions();
    void boxes();

    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;
    sf::Time dt;
    std::string directory;
    int index = 0;
    std::string current_song;
    std::vector <std::string> songs;
    sf::Font Font;
    sf::Text currentSongText;
    sf::Text FFTStateText;
    sf::Text Instructions;
    sf::Text windowName;
    int FFTOnce = -1;
    std::string lastFFT;
    sf::RectangleShape taskbar;
    sf::RectangleShape FFT;
    sf::RectangleShape songBox;
    sf::RectangleShape instructionBox;
    barSpectrum *music_bars;
    musicProcessor *song;
    bool FFTDone = false;
    bool FFTRefresh = false;
<<<<<<< HEAD
    bool ready = false;
    bool PLAY = false;
    std::map<float,sf::RectangleShape>::iterator mapItr;
=======
    std::map<float,std::pair<sf::RectangleShape,std::pair<double,double>>>::iterator mapItr;
>>>>>>> c212912b58106fff61e50fa4ddf2ad978f96e025
    float duration = float(); // SFML Documentation (cite)
    std::vector<complex_vec>::iterator currentSample;
    std::vector<complex_vec>::iterator temp;
    bool flag = false, doneSong = false;
    int counter = 0;
};

#endif

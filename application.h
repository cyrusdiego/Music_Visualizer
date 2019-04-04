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

    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;
    sf::Time dt;
    sf::RectangleShape taskbar;
    barSpectrum *music_bars;
    musicProcessor *song;
    bool FFTDone = false;
    bool FFTRefresh = false;
    std::map<float,std::pair<sf::RectangleShape,std::pair<double,double>>>::iterator mapItr;
    float duration = float(); // SFML Documentation (cite)
    std::vector<complex_vec>::iterator currentSample;
    std::vector<complex_vec>::iterator temp;
    bool flag = false, doneSong = false;
    int counter = 0;
};

#endif

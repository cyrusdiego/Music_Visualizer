/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.h : header file declaring application class
*/

#ifndef APPLICATION_H
#define APPLICATION_H
#include "globals.h"
#include "bars.h"
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
    void processEvents();
    void updateScreen();
    void renderScreen();
    void windowSetup();

private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;
    barSpectrum music_bars;
    musicProcessor *song;
    std::map<float,sf::RectangleShape>::iterator mapItr;
    bool ready = false;
    sf::Time dt;
    float duration = float(); // SFML Documentation (cite)

};

#endif

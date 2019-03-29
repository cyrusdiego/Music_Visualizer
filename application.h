/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    window.h : header file containing content all files require
*/

#ifndef APPLICATION_H
#define APPLICATION_H
#include "globals.h"

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
    sf::Clock clock;
    sf::Time dt;
    sf::Event event;
    float duration = float();
    sf::RenderWindow window;


};

#endif

/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    bars.h : header file declaring bars class
*/

#ifndef BARS_H
#define BARS_H
#include "globals.h"

/*
    application class that holds the window instantiating, keyboard input,
    and the application running
*/
class bars {
public:
    bars();
    ~bars();

    sf::RectangleShape getBar(int i);
    std::vector<sf::RectangleShape>::const_iterator begin();
    std::vector<sf::RectangleShape>::const_iterator end();

private:
    std::vector<sf::RectangleShape> barGraph;
};

#endif

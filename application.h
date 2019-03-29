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
    void processEvents();
    void updateScreen();
    void renderScreen();

private:
    sf::Clock clock;
    sf::Time dt;
    sf::Event event;
    float duration = float();
    sf::RenderWindow window;
    sf::Vertex line[2] = {
        sf::Vertex(sf::Vector2f(300.0f, 600.0f)),
        sf::Vertex(sf::Vector2f(300.0f, 300.0f))
    };
    sf::Music music;
    float x = 300;
    int change = 0;
    sf::RectangleShape rectangle;


};

#endif

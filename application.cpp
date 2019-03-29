/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.cpp : implementation of the application class
*/
#include "globals.h"
#include "application.h"
#include <iostream>
/*
    constructor to launch the window and configures window properties
    @param : title of the window
*/
application::application(const std::string title) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode::getDesktopMode(), title,sf::Style::Default, settings);
    window.setKeyRepeatEnabled(false);
    music_bars = bars();
    windowSetup();
}

application::~application() {}

void application::windowSetup() {
    for(auto i = music_bars.begin(); i != music_bars.end(); i++){
        window.draw(*i);
        window.display();
    }
}

/*
    run is the main application loop that will check for events, update the buffer,
    then render on the screen
*/
void application::run() {
    while(window.isOpen()) {
        processEvents();
        // renderScreen();
        // updateScreen();

    }
}

/*
    processEvents will check for any events and act accordingly
*/
void application::processEvents() {
    if(window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:  // closes window
                window.close();
                break;

            case sf::Event::KeyPressed:  // checks for keyboard input
                if(event.key.code == sf::Keyboard::Q)  // closes window with "Q"
                    window.close();

                break;
        }
    }
}

/*

*/
void application::updateScreen() {
}

/*
    renders the new graphics on the screen by clearing, then drawing graphics,
    and displaying it
*/
void application::renderScreen() {
    window.clear(sf::Color::Black);
    window.display();
}

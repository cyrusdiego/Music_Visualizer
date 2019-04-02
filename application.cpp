/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.cpp : implementation of the application class
*/
#include "application.h"

/*
    constructor to launch the window and configures window properties
    @param : title of the window
*/
application::application(const std::string title) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode::getDesktopMode(), title,sf::Style::Default | sf::Style::Fullscreen, settings);
    window.setKeyRepeatEnabled(false);

    music_bars = barSpectrum((int)window.getSize().x,(int)window.getSize().y);


    windowSetup();

}

application::~application() {}

void application::windowSetup() {
    sf::Color taskbar_color(177, 186, 188);
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x , 50.f));
    rectangle.setFillColor(taskbar_color);
    taskbar = rectangle;
    window.draw(taskbar);

    for(mapItr = music_bars.start(); mapItr != music_bars.last(); mapItr++){
        window.draw(mapItr->second);
    }
    window.display();
}

/*
    run is the main application loop that will check for events, update the buffer,
    then render on the screen
*/
void application::run() {
    while(window.isOpen()) {
        processEvents();
        if(ready) {
            updateScreen();
            while(true){
                //std::cout << "stuck in while\n";
            }
            //renderScreen();
        }
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
                if(event.key.code == sf::Keyboard::P) {
                    if(ready){
                        song->play();
                    } else {
                        std::cout << "error: no song loaded\n";
                    }
                }
                if(event.key.code == sf::Keyboard::F) {
                    std::cout << "performing FFT now\n";
                    song = new musicProcessor("253011553368158.wav");
                    std::cout << "done FFT\n";
                    ready = true;
                }

            break;
        }
    }
}

void application::animationBarIncrease() {
    bool flag = true;
    while(flag){
        flag = music_bars.plotBars();
        duration = 0;
        window.clear(sf::Color::Black);
        for(mapItr = music_bars.start(); mapItr != music_bars.last(); mapItr++) {
            window.draw(mapItr->second);
        }
        window.display();
    }

}

/*

*/
void application::updateScreen() {
    dt = clock.restart();
    duration += dt.asSeconds();
    //music_bars.clearSampleMap();
    std::vector<complex_vec>::iterator currentSample = song->getIterator();
    music_bars.readFFT(currentSample);
    if(duration > 0.01f) {
        animationBarIncrease();
    }
}

/*
    renders the new graphics on the screen by clearing, then drawing graphics,
    and displaying it
*/
void application::renderScreen() {
    window.draw(taskbar);
    window.display();
}

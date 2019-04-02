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

    music_bars = new barSpectrum((int)window.getSize().x,(int)window.getSize().y);

    sf::Color taskbar_color(177, 186, 188);
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x , 50.f));
    rectangle.setFillColor(taskbar_color);
    taskbar = rectangle;
}

application::~application() {}

/*
    run is the main application loop that will check for events, update the buffer,
    then render on the screen
*/
void application::run() {
    while(window.isOpen()) {
        processEvents();
        if(FFTRefresh) {
            getNextSample();
        }
        updateScreen();
        renderScreen();

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
                    if(FFTDone){
                        song->play();
                    } else {
                        std::cout << "error: no song loaded\n";
                    }
                }
                if(event.key.code == sf::Keyboard::F) {
                    std::cout << "performing FFT now\n";
                    song = new musicProcessor("253011553368158.wav");
                    std::cout << "done FFT\n";
                    FFTDone = true;
                    FFTRefresh = true;
                }

            break;
        }
    }
}

void application::getNextSample() {
    currentSample = song->getIterator();
    music_bars->readFFT(currentSample);
}

void application::updateScreen() {
    dt = clock.restart();
    duration += dt.asSeconds();

    if(FFTDone && duration > 0.01f) {
        FFTRefresh = music_bars->plotBars();
        //FFTRefresh = false;
    }
}

/*
    renders the new graphics on the screen by clearing, then drawing graphics,
    and displaying it
*/
void application::renderScreen() {
    window.clear(sf::Color::Black);
    window.draw(taskbar);
    for(mapItr = music_bars->start(); mapItr != music_bars->last(); mapItr++){
        window.draw(mapItr->second);
        if(mapItr->second.getSize().y != 200){
            std::cout << "freq: " << mapItr->first << " mag: " << mapItr->second.getSize().y << "\n";
        }
    }
    window.display();
}

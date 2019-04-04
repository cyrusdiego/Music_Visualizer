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
    setup();
    boxes();
    printFFTStateText();
    printCurrentSongText();
    printInstructions();
}


void application::boxes () {
    sf::Color taskbar_color(177, 186, 188);
    sf::Color FFT_colour (255,255,255);
    sf::Color songBoxColor (255,255,255);
    sf::Color instructionColor (255,255,255);
    sf::RectangleShape rectangle(sf::Vector2f(window.getSize().x , 50.f));
    sf::RectangleShape FFTbox (sf::Vector2f(window.getSize().x/1.5 , window.getSize().x/20));
    sf::RectangleShape songShape (sf::Vector2f(window.getSize().x/1.4 , window.getSize().x/20));
    sf::RectangleShape instructionshape (sf::Vector2f(window.getSize().x , window.getSize().x/20));
    rectangle.setFillColor(taskbar_color);
    FFTbox.setFillColor(FFT_colour);
    songShape.setFillColor(songBoxColor);
    instructionshape.setFillColor(instructionColor);
    taskbar = rectangle;
    FFT = FFTbox;
    songBox = songShape;
    instructionBox = instructionshape;
    FFT.setPosition(window.getSize().x/6 , window.getSize().y/4);
    songBox.setPosition(window.getSize().x/7,window.getSize().y/2);
    instructionBox.setPosition(0,window.getSize().y-50.0f);

}
void application::printFFTStateText(){
    FFTStateText.setFont(Font);
    if (FFTOnce == 1){
        FFTStateText.setString(lastFFT + " IS LOADED");
    } else if (FFTOnce == 0){
        FFTStateText.setString("FFT IN PROGRESS");
    } else {
        FFTStateText.setString("NO SONG LOADED");
    }
    FFTStateText.setCharacterSize(100); // in pixels, not points!
    FFTStateText.setColor(sf::Color(0, 0, 0));
    FFTStateText.setPosition(window.getSize().x/4+200 , window.getSize().y/4);
}

void application::printCurrentSongText(){
    currentSongText.setFont(Font);
    currentSongText.setCharacterSize(100); // in pixels, not points!
    currentSongText.setColor(sf::Color(0, 0, 0));
    currentSongText.setPosition(window.getSize().x/4+200 , window.getSize().y/2);
}

void application:: printInstructions(){
    Instructions.setFont(Font);
    Instructions.setColor(sf::Color(0, 0, 0));
    Instructions.setCharacterSize(20);
    Instructions.setString("USE LEFT AND RIGHT ARROW KEYS TO CHOSE SONG || PRESS <F> TO BEGIN FOURIER TRANSFORM || PRESS <P> TO VISUALIZE || PRESS <Q> TO ESCAPE");
    Instructions.setPosition(window.getSize().x/11 ,window.getSize().y-43);
}


void application::setup(){
    std::ifstream file;
    std::string current_song;
    file.open("SONGS.txt"); // open file with song names
    std::string line; // stores the current line read in
    int count = 0;
    std::string font;
    while (std::getline(file,line)){
        if (count == 0) {
            directory = line;
        } else {
            songs.push_back(line);
        }
        count = 1;
    }
    file.close();
    if (!Font.loadFromFile("Roboto-BlackItalic.ttf")){
        std::cout <<"Error loading Font" << std::endl;
    }
    current_song = songs.at(0);
    currentSongText.setString(current_song);

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
            flag = false;
            getNextSample();
        }
        if(doneSong) {
            // std::cout << "got inside doneSong\n";
            window.close();
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
                    if(ready){
                        FFTRefresh = true;
                        FFTDone = true;
                        PLAY = true;
                        song->play();
                        // sf::sleep(sf::seconds(0.5));
                    } else {
                        std::cout << "error: no song loaded\n";
                    }
                }
                if(event.key.code == sf::Keyboard::F) {
                    std::cout << "FFT IN PROGRESS\n";
                    FFTOnce = 0;
                    lastFFT = current_song;
                    printFFTStateText();
                    renderScreen();
                    FFTOnce = 1;
                    song = new musicProcessor(directory+current_song);
                    printFFTStateText();
                    renderScreen();
                    music_bars = new barSpectrum((int)window.getSize().x,(int)window.getSize().y,song->getMaxMinFreq(),song->getMaxMinAmp());
                    ready = true;
                    flag = true;
                }
                if((event.key.code == sf::Keyboard::Left) && (index > 0)){
                    index--;
                    current_song = songs.at(index);
                    currentSongText.setString(current_song);
                }
                if((event.key.code == sf::Keyboard::Right) && (index < songs.size()-1)){
                    index++;
                    current_song = songs.at(index);
                    currentSongText.setString(current_song);
                }
            break;
        }
    }
}

void application::getNextSample() {
    currentSample = song->getIterator();
    if(currentSample == song->last()){
        std::cout << "currentSample = song->last()\n";
        doneSong = true;
    } else {
        // std::cout << "reading FFT\n";
        music_bars->readFFT(currentSample,song->getSampleRate(),currentSample->size());
        music_bars->restoreHeight();
        renderScreen();

    }
}

void application::updateScreen() {
    dt = clock.restart();
    duration += dt.asSeconds();


    if(FFTDone && duration > (1.0f/60.0f)) {
        // std::cout << "inside\n";
        duration = 0;
        FFTRefresh = music_bars->plotBars();
        if(!FFTRefresh) {
            flag = true;
        } else {
            flag = false;
        }
        // std::cout << "done\n";

    }
}

/*
    renders the new graphics on the screen by clearing, then drawing graphics,
    and displaying it
*/
void application::renderScreen() {
    window.clear(sf::Color::Black);
    window.draw(taskbar);
    window.draw(windowName);
    if (!PLAY) {
        window.draw(FFT);
        window.draw(songBox);
        window.draw(FFTStateText);
        window.draw(currentSongText);
        window.draw(instructionBox);
        window.draw(Instructions);
    }
    if(FFTDone) {
        for(mapItr = music_bars->start(); mapItr != music_bars->last(); mapItr++){
            window.draw(mapItr->second.first);
        }
    }
    window.display();

}

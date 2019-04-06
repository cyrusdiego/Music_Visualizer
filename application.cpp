/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and 1531475
    CMPUT 275 WINTER 2019 Final Project: FFT Visualizer

    application.cpp : implementation of the application class
        - Launches the window / GUI using SFML
        - Runs the driver loop to refresh the screen
        - Inits other classes for the application to run
*/
#include "application.h"

/*
    constructor to launch the window and configures window properties
    @param : title of the window
*/
application::application(const std::string title) {
    // graphics settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // inits wincow class (Fullscreen)
    window.create(sf::VideoMode::getDesktopMode(), title,sf::Style::Default | sf::Style::Fullscreen, settings);
    window.setKeyRepeatEnabled(false);

    // Draws the GUI upon initialization
    setup();
    boxes();
    printFFTStateText();
    printCurrentSongText();
    printInstructions();
}

/*
    Draws the GUI "Boxes" at the begining of the initialization
*/
void application::boxes () {
    // Sets colour for the boxes
    sf::Color box_color(255,255,255);

    // Creates rectangle objects
    sf::RectangleShape rectangle (sf::Vector2f(window.getSize().x , 50.f));
    sf::RectangleShape FFTbox (sf::Vector2f(window.getSize().x/1.5 , window.getSize().x / 20));
    sf::RectangleShape songShape (sf::Vector2f(window.getSize().x/1.4 , window.getSize().x / 20));
    sf::RectangleShape instructionshape (sf::Vector2f(window.getSize().x , window.getSize().x / 20));

    // Sets fill colours
    rectangle.setFillColor(box_color);
    FFTbox.setFillColor(box_color);
    songShape.setFillColor(box_color);
    instructionshape.setFillColor(box_color);

    // Assigns private data members to allow for the render method to draw them
    taskbar = rectangle;
    FFT = FFTbox;
    songBox = songShape;
    instructionBox = instructionshape;

    // sets positions for the boxes
    FFT.setPosition (window.getSize().x / 6 , window.getSize().y / 4);
    songBox.setPosition (window.getSize().x / 7, window.getSize().y / 2);
    instructionBox.setPosition (0, window.getSize().y - 50.0f);

}

/*
    Displays the state of application to screen
*/
void application::printFFTStateText(){
    FFTStateText.setFont(Font);

    // will display the appropriate string depending on the state
    if (FFTOnce == 1){
        FFTStateText.setString(lastFFT + " IS LOADED");
    } else if (FFTOnce == 0){
        FFTStateText.setString("FFT IN PROGRESS");
    } else {
        FFTStateText.setString("NO SONG LOADED");
    }

    // sets the text properties
    FFTStateText.setCharacterSize(100); // in pixels, not points!
    FFTStateText.setColor(sf::Color(0, 0, 0));
    FFTStateText.setPosition(window.getSize().x/4+200 , window.getSize().y/4);
}

/*
    prints the song title on the window
*/
void application::printCurrentSongText(){
    currentSongText.setFont (Font);
    currentSongText.setCharacterSize (100); // in pixels, not points!
    currentSongText.setColor (sf::Color(0, 0, 0));
    currentSongText.setPosition ((window.getSize().x / 4) + 200 , window.getSize().y / 2);
}

/*
    prints application instructions at the bottom of window
*/
void application:: printInstructions(){
    Instructions.setFont (Font);
    Instructions.setColor(sf::Color (0, 0, 0));
    Instructions.setCharacterSize (20);
    Instructions.setString ("USE LEFT AND RIGHT ARROW KEYS TO CHOSE SONG || PRESS <F> TO BEGIN FOURIER TRANSFORM || PRESS <P> TO VISUALIZE || PRESS <Q> TO ESCAPE");
    Instructions.setPosition (window.getSize().x / 11 ,window.getSize().y - 43);
}

/*
    initial setup for the GUI
    - font
    - reads file of song titles
*/
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

    // Loads font
    if (!Font.loadFromFile("Roboto-BlackItalic.ttf")){
        std::cout <<"Error loading Font" << std::endl;
    }

    current_song = songs.at(0);
    currentSongText.setString(current_song);

}

// Destructor
application::~application() {}

/*
    run is the main application loop that will check for events, update the buffer,
    then render on the screen.
*/
void application::run() {
    while(window.isOpen()) {
        processEvents();

        // if the fft buffer needs to be refreshed, get next sample
        if(FFTRefresh) {
            getNextSample();
        }

        // if the song is done, close screen
        if(doneSong) {
            window.close();
        }

        // draw on screen then refresh screen
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
                // closes window with "Q"
                if(event.key.code == sf::Keyboard::Q){
                    window.close();
                }
                // if P is pressed, play song (if song is loaded)
                if(event.key.code == sf::Keyboard::P) {
                    if(ready){
                        FFTRefresh = true;
                        FFTDone = true;
                        PLAY = true;
                        song->play();
                    } else {
                        std::cout << "error: no song loaded\n";
                    }
                }
                // Runs FFT on chosen song
                if(event.key.code == sf::Keyboard::F) {
                    std::cout << "FFT IN PROGRESS\n";
                    FFTOnce = 0;
                    lastFFT = current_song;
                    printFFTStateText();  // refreshes GUI
                    renderScreen();  // draws it on screen
                    FFTOnce = 1;
                    song = new musicProcessor(directory + current_song);  // inits musicProcessor class
                    printFFTStateText();  // refreshes GUI
                    renderScreen();  // draws it on screen
                    // inits barSpectrum class
                    music_bars = new barSpectrum((int)window.getSize().x,(int)window.getSize().y,song->getMaxMinFreq(),song->getMaxMinAmp());
                    ready = true;
                }
                // scrolls through song options
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

/*
    Gets iterator to the next FFT Buffer
*/
void application::getNextSample() {
    currentSample = song->getIterator();
    // if the iterator ran thru the whole buffer, song is done
    if(currentSample == song->last()){
        doneSong = true;
    } else {
        music_bars->readFFT(currentSample,song->getSampleRate(),currentSample->size());
        music_bars->restoreHeight();  // resets height of bars
        renderScreen(); // draws bar on screen
    }
}

/*
    draws the bars at 60fps
*/
void application::updateScreen() {
    dt = clock.restart();
    duration += dt.asSeconds();
    // if FFT process is done, and its less than 1/60th of a sec, change height of bars
    if(FFTDone && duration > (1.0f/60.0f)) {
        duration = 0;
        FFTRefresh = music_bars->plotBars();  // changes the heights of the bars

    }
}

/*
    renders the new graphics on the screen by clearing, then drawing graphics,
    and displaying it
*/
void application::renderScreen() {
    window.clear(sf::Color::Black);  // clear screen
    window.draw(taskbar);
    window.draw(windowName);

    // draws the initial gui objects
    if (!PLAY) {
        window.draw(FFT);
        window.draw(songBox);
        window.draw(FFTStateText);
        window.draw(currentSongText);
        window.draw(instructionBox);
        window.draw(Instructions);
    }

    if(FFTDone) {  // run through the barSpectrum class and draws all the bars with new height
        for(mapItr = music_bars->start(); mapItr != music_bars->last(); mapItr++){
            window.draw(mapItr->second.first);
        }
    }
    // display all the objects
    window.display();

}

/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.cpp : implementation of the application class
*/
#include "globals.h"
#include "bars.h"
#include <iostream>

// Define frequency ranges
#define SUBBASS 20
#define BASS 60
#define LOWMIDRANGE 250
#define MIDRANGE 500
#define UPMIDRANGE 2000
#define PRESENCE 4000
#define BRILLIANCE 6000
#define MAXFREQ 20000

barSpectrum::barSpectrum(){}

barSpectrum::barSpectrum(int xWindow, int yWindow){
    sf::RectangleShape temp;
    numBars = floor(xWindow / 5) + 1;

    // calcFreqRange();



    float x = 0,step = 0;
    int r = 255, g = 30, b = 0;
    for(int i = 0; i < numBars; i++){
        temp.setSize(sf::Vector2f(2.5f, 200.0f));
        temp.setPosition(x,yWindow - 200.0f);
        sf::Color temp_color(255,255,255);
        temp.setFillColor(temp_color);
        barGraph[i] = (temp);
        step += freqStep;
        x += 5.0;
    }
}

barSpectrum::~barSpectrum(){}

sf::RectangleShape barSpectrum::getBar(int i){
    return barGraph[i];
}

int barSpectrum::getnumBars(){
    return numBars;
}

int barSpectrum::getfreqStep(){
    return freqStep;
}

// pair(num of Bars in that range , freqency step in that range)
// void barSpectrum::calcFreqRange(){
//     subBass = make_pair(
//         ceil((BASS - SUBBASS) * numBars / MAXFREQ),
//         (BASS - SUBBASS) / ceil((BASS - SUBBASS) * numBars / MAXFREQ)
//     );
//     bass = make_pair(
//         ceil((BASS - SUBBASS) * numBars / MAXFREQ),
//         (BASS - SUBBASS) / ceil((BASS - SUBBASS) * numBars / MAXFREQ)
//     );
// }

// std::pair barSpectrum::getFreqRange(){
//
// }

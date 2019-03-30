/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    bars.h : header file declaring bars class
*/

#ifndef BARS_H
#define BARS_H
#include "globals.h"
#include <unordered_map>
#include <utility>

/*
    application class that holds the window instantiating, keyboard input,
    and the application running
*/
class barSpectrum {
public:
    barSpectrum();
    barSpectrum(int xWindow, int yWindow);
    ~barSpectrum();

    sf::RectangleShape getBar(int i);
    int getnumBars();
    int getfreqStep();
    // void calcFreqRange();
    // std::pair getFreqRange();
private:
    std::unordered_map<int,sf::RectangleShape> barGraph;
    int numBars;
    int freqStep;
    int startY;
    std::pair<int,float> subBass, bass, lowMidRange, midRange, upMidRange, presence, brilliance;

};

class bar {
public:

private:

};

#endif

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
class barSpectrum {
public:
    barSpectrum();
    barSpectrum(int xWindow, int yWindow);
    ~barSpectrum();

    sf::RectangleShape getBar(int i);
    int getnumBars();
    void calcFreqRange();
    void calcColor(sf::RectangleShape &bar, float counter);
    float mapFreq(float i);
    std::unordered_map<float,sf::RectangleShape>::iterator begin();
    std::unordered_map<float,sf::RectangleShape>::iterator end();
    int count(float key);

private:
    std::unordered_map<float,sf::RectangleShape> barGraph;
    float numBars;
    int startY;
    std::pair<int,std::pair<float,float>> subBass, bass, lowMidRange, midRange, upMidRange, presence, brilliance;
    // Define frequency ranges
    float SUBBASS = 20;
    float BASS = 60;
    float LOWMIDRANGE = 250;
    float MIDRANGE = 500;
    float UPMIDRANGE = 2000;
    float PRESENCE = 4000;
    float BRILLIANCE = 6000;
    float MAXFREQ = 20000;
};

class bar {
public:

private:

};

#endif

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
    void calcColor(sf::RectangleShape &bar, float counter);
    float mapFreq(float i);
    std::map<float,sf::RectangleShape>::iterator start();
    std::map<float,sf::RectangleShape>::iterator last();

    void plotBars(double phase, double magnitude);
    double findClosestFreq(double phase);
    void readFFT(std::vector<complex_vec>::iterator cmplxVector);


private:
    std::map<float,sf::RectangleShape> barGraph;
    std::map<float,sf::RectangleShape>::const_iterator lowBound,upBound;

    float numBars;
    float MAXFREQ = 20000;

};

#endif

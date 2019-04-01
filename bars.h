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

    bool plotBars();
    double findClosestFreq(double phase);
    void readFFT(std::vector<complex_vec>::iterator cmplxVector);
    double mapMagnitude(double magnitude);
    double increaseHeight(double magnitude);
    void clearSampleMap();
    bool restoreBars();
    double decreaseHeight(double magnitude);


private:
    std::map<float,sf::RectangleShape> barGraph;
    std::map<float,sf::RectangleShape>::const_iterator lowBound,upBound;
    float changeBar = 0.0f;
    float numBars;
    float MAXFREQ = 4000, MINFREQ = 20;
    int yWindowDim;
    std::map<double,float> sample;

};

#endif

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
    barSpectrum(int xWindow, int yWindow,std::pair<double,double> freqExtremes, std::pair<double,double> ampExtremes);
    ~barSpectrum();

    sf::RectangleShape getBar(int i);
    int getnumBars();
    void calcColor(sf::RectangleShape &bar, float counter);
    float mapFreq(float i);
    std::map<float,sf::RectangleShape>::iterator start();
    std::map<float,sf::RectangleShape>::iterator last();

    double findClosestFreq(double phase);
    void readFFT(std::vector<complex_vec>::iterator cmplxVector,sf::Uint64 sampleRate, sf::Uint64 length);
    double mapMagnitude(double magnitude);
    double increaseHeight(double magnitude, double prevHeight);
    void clearSampleMap();
    double decreaseHeight(double magnitude, double prevHeight);
    bool plotBars();
    void calcRanges();

private:
    std::map<float,sf::RectangleShape> barGraph;
    std::map<float,sf::RectangleShape>::const_iterator lowBound,upBound;
    float changeBar = 0.0f;
    float numBars;
    float MAXFREQ, MINFREQ;
    int yWindowDim;
    std::map <double,float> sample;
    double MAXHEIGHT, MINHEIGHT;
    std::vector<double> freqRanges;
    double mapFreqMultiplier = 1;
};

#endif

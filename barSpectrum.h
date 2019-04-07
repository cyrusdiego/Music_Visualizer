/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and 1531475
    CMPUT 275 WINTER 2019 Final Project: FFT Visualizer

    barSpectrum.h : header file declaring barSpectrum class
*/

#ifndef BARS_H
#define BARS_H
#include "globals.h"

/*
    barSpectrum is used to store all the bars in a map:
        - assigns each bar a frequency to represent
        - changes height of each bar in response to FFT data
*/
class barSpectrum {
public:
    barSpectrum();
    barSpectrum(int xWindow, int yWindow,std::pair<double,double> freqExtremes, std::pair<double,double> ampExtremes);
    ~barSpectrum();

    // Methods required inside application.cpp
    void readFFT(std::vector<complex_vec>::iterator cmplxVector,sf::Uint64 sampleRate, sf::Uint64 length);
    void restoreHeight();
    std::map<float,std::pair<sf::RectangleShape,double>>::iterator start();
    std::map<float,std::pair<sf::RectangleShape,double>>::iterator last();
    bool plotBars();



private:
    void calcColor(sf::RectangleShape &bar, float counter);
    float mapFreq(float i);
    double findClosestFreq(double phase);
    double mapMagnitude(double magnitude);
    double increaseHeight(double magnitude, std::pair<sf::RectangleShape,double> &bar);
    void clearSampleMap();
    double decreaseHeight(double magnitude, std::pair<sf::RectangleShape,double> &bar);
    void calcRanges();
    void resetRates();

    std::map<float,std::pair<sf::RectangleShape,double>> barGraph;
    std::map<float,std::pair<sf::RectangleShape,double>>::const_iterator lowBound,upBound;
    float numBars;
    float MAXFREQ, MINFREQ;
    int yWindowDim;
    std::map <double,float> sample;
    double MAXHEIGHT, MINHEIGHT;
    double mapFreqMultiplier = 1;
    std::vector<int> ranges;
    std::vector<int> freqRanges = {0, 60, 100, 300,700, 1500, 2500, 4000, 5000};
    float baseMagnitude;
    double xPosition = 50.0, defaultY = -200.0;
    float fps = 60.0f;
};

#endif

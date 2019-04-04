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

    int getnumBars();
    void calcColor(sf::RectangleShape &bar, float counter);
    float mapFreq(float i);
    std::map<float,std::pair<sf::RectangleShape,std::pair<double,double>>>::iterator start();
    std::map<float,std::pair<sf::RectangleShape,std::pair<double,double>>>::iterator last();

    double findClosestFreq(double phase);
    void readFFT(std::vector<complex_vec>::iterator cmplxVector,sf::Uint64 sampleRate, sf::Uint64 length);
    double mapMagnitude(double magnitude);
    double increaseHeight(double magnitude, std::pair<sf::RectangleShape,std::pair<double,double>> &bar);
    void clearSampleMap();
    double decreaseHeight(double magnitude, std::pair<sf::RectangleShape,std::pair<double,double>> &bar);
    bool plotBars();
    void calcRanges();
    void restoreHeight();
    void resetRates();

private:
    std::map<float,std::pair<sf::RectangleShape,std::pair<double,double>>> barGraph;
    std::map<float,std::pair<sf::RectangleShape,std::pair<double,double>>>::const_iterator lowBound,upBound;
    float numBars;
    float MAXFREQ, MINFREQ;
    int yWindowDim;
    std::map <double,float> sample;
    double MAXHEIGHT, MINHEIGHT;
    double mapFreqMultiplier = 1;
    std::vector<int> ranges;
    std::vector<int> freqRanges = { 0, 60, 100, 300,700, 1500, 2500, 4000, 5000};
    float baseMagnitude;
    double xPosition = 20, defaultY = -200.0f;
};

#endif

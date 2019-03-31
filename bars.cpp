/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.cpp : implementation of the application class
*/
#include "bars.h"

barSpectrum::barSpectrum(){}

barSpectrum::barSpectrum(int xWindow, int yWindow){
    // calc max number of bars in window and the freuency ranges per bar
    // this is window / pc dependent will need to be calc every launch of application
    numBars = floor(xWindow / 5) + 1;

    // temporary object used to store in barGraph
    sf::RectangleShape bar(sf::Vector2f(2.5f, 200.0f));
    int x = 0;
    for(float i = 1; i < numBars + 1; i++){
        // shifts position and sets color
        bar.setPosition(x, yWindow - 200.0f);
        calcColor(bar,i);

        // stores bar into unordered_map with respective freqency
        barGraph[mapFreq(i)] = bar;
        x += 5.0;
    }
}

barSpectrum::~barSpectrum(){}

sf::RectangleShape barSpectrum::getBar(int i) {
    return barGraph[i];
}

int barSpectrum::getnumBars(){
    return numBars;
}

float barSpectrum::mapFreq(float i) {
    return (i / numBars) * MAXFREQ;
}

std::map<float,sf::RectangleShape>::iterator barSpectrum::start(){
    return barGraph.begin();
}

std::map<float,sf::RectangleShape>::iterator barSpectrum::last(){
    return barGraph.end();
}


/*
    creates even gradient for the bars in the graph
*/
void barSpectrum::calcColor(sf::RectangleShape &bar, float counter) {
    float r,g,b;
    float oneFourth = numBars / 4;
    float twoFourth = numBars *  2 / 4;
    float threeFourth = numBars *  3 / 4;

    // https://stats.stackexchange.com/questions/281162/scale-a-number-between-a-range
    // used normalization to scale numbers to appropriate values
    if(counter < oneFourth) {
        r = 255; b = 0;
        g = (counter / oneFourth) * 255;

    } else if(oneFourth <= counter && counter <= twoFourth) {
        g = 255; b = 0;
        r = 255 - (((counter - oneFourth) / (twoFourth - oneFourth)) * 255);

    } else if(twoFourth < counter && counter <= threeFourth) {
        g = 255; r = 0;
        b = (((counter - twoFourth)/ (threeFourth - twoFourth)) * 255);

    } else {
        b = 255; r = 0;
        g = 255 - (((counter - threeFourth) / (numBars - threeFourth)) * 255);
    }

    sf::Color barColor(r,g,b);
    bar.setFillColor(barColor);
}
// O(logn)
double barSpectrum::findClosestFreq(double phase) {
    double newPhase;
    lowBound = barGraph.lower_bound(phase);
    if (lowBound != barGraph.end()) {
        upBound = barGraph.upper_bound(phase);

        if(lowBound->first - phase <= upBound->first - phase) {
            newPhase = lowBound->first;
        } else {
            newPhase = upBound->first;
        }

    } else {
        newPhase = barGraph.end()->first;
    }
    return newPhase;
}

void barSpectrum::plotBars(double phase, double magnitude) {
    if(barGraph[phase].getSize().y != magnitude) {
        sf::RectangleShape bar(sf::Vector2f(2.5f, 200.0f - 10.0f));
        barGraph[phase] = bar;
    }
}

void barSpectrum::readFFT(complex_vec cmplxVector) {
    double phase, magnitude;
    for(auto i : cmplxVector) {
        phase = findClosestFreq(std::arg(i) / (2 * pi));
        magnitude = std::abs(i);
        plotBars(phase,magnitude);
    }
}

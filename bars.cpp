/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.cpp : implementation of the application class
*/
#include "bars.h"

barSpectrum::barSpectrum(){}

barSpectrum::barSpectrum(int xWindow, int yWindow,std::pair<double,double> freqExtremes, std::pair<double,double> ampExtremes){
    // calc max number of bars in window and the freuency ranges per bar
    // this is window / pc dependent will need to be calc every launch of application
    numBars = floor(xWindow / 25) + 1;
    yWindowDim = yWindow;
    MAXHEIGHT = 10 * std::log10(ampExtremes.second);
    MINHEIGHT = (ampExtremes.first != 0 ? 10 * std::log10(ampExtremes.first) : 0) ;
    std::cout << "maxheight and min height: ";
    std::cout << MAXHEIGHT << " " << MINHEIGHT << "\n";
    std::cout << "numBars: " << numBars << "\n";
    // temporary object used to store in barGraph
    sf::RectangleShape bar(sf::Vector2f(25.0f, -200.0f));
    int x = 0;
    MAXFREQ = freqExtremes.second; MINFREQ = freqExtremes.first;
    std::cout << MAXFREQ << " " << MINFREQ << "\n";
    std::cout << "numBars: " << numBars << "\n";
    for(float i = 1; i < numBars + 1; i++){
        // shifts position and sets color
        bar.setPosition(x, yWindow);
        calcColor(bar,i);

        // stores bar into unordered_map with respective freqency
        barGraph[mapFreq(i)] = bar;
        // std::cout << "mapFreq(i): " << mapFreq(i) << "\n";
        x += 25.0;
    }
    calcRanges();

}

barSpectrum::~barSpectrum(){}

void barSpectrum::calcRanges() {
    double frequency, multiplier = 1;
    for(int i = 0; i < numBars; i++){
        frequency = (multiplier* i *(MAXFREQ - MINFREQ) / numBars);
        freqRanges.push_back(frequency);
        multiplier *= 1.2;
    }
}

sf::RectangleShape barSpectrum::getBar(int i) {
    return barGraph[i];
}

int barSpectrum::getnumBars(){
    return numBars;
}

float barSpectrum::mapFreq(float index) {
    std::vector<float> ranges;
    for(float i = 1; i < 8; i++) {
        fifths.push_back(i * numBars / 5);
    }
    // float oneFifth = numBars / 5;  // 0 to low bass
    // float twoFifth = numBars *  2 / 5; // low bass to low midrange
    // float threeFifth = numBars *  3 / 5; // low midrange to midrange
    // float fourFifth = numBars * 4 / 5;  // midrange to upper midrange
    float newFreq;

    float low = 20, subBass =
    if(index < oneFifth) {


    } else if(oneFifth <= index && index <= twoFifth) {


    } else if(twoFifth < index && index <= threeFifth) {


    } else if(threeFifth < index && index <= fourFifth){

    } else {

    }

     return newFreq;
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

void barSpectrum::clearSampleMap(){
    sample.clear();
}

// O(logn)
double barSpectrum::findClosestFreq(double phase) {
    double newPhase;
    if(phase < 0) {
        return barGraph.begin()->first;
    } else {
        lowBound = barGraph.lower_bound(phase);
        if (lowBound != barGraph.end()) {
            upBound = barGraph.upper_bound(phase);

            if(lowBound->first - phase <= upBound->first - phase) {
                newPhase = lowBound->first;
            } else {
                newPhase = upBound->first;
            }

        } else {
            newPhase = barGraph.rbegin()->first;
        }
        return newPhase;
    }


}

double barSpectrum::mapMagnitude(double magnitude) {
    return ((magnitude - MINHEIGHT)/ (MAXHEIGHT - MINHEIGHT)) * (50.0f - (yWindowDim - 200.0f)) + 50.0f;
}

double barSpectrum::increaseHeight(double magnitude, double prevHeight) {
    double x = /*yWindowDim -*/ (prevHeight - changeBar);
    double y =  magnitude;
    // std::cout << "yWindowDim - 200 - changeBar = " << x << " magnitude = " << y << "\n std::abs(y - x) <= 10.0f : " << (std::abs(y - x) <= 10.0f) << "\n";
    if(std::abs(std::abs(y) - std::abs(x)) <= 10.0f){
        return y;
    } else {
        return x;
    }
}
double barSpectrum::decreaseHeight(double magnitude, double prevHeight) {
    double x = /*yWindowDim -*/ (prevHeight + changeBar);
    double y =  magnitude;
    // std::cout << "yWindowDim - 200 - changeBar = " << x << " magnitude = " << y << "\n std::abs(y - x) <= 10.0f : " << (std::abs(y - x) <= 10.0f) << "\n";
    if(std::abs(std::abs(y) - std::abs(x)) <= 10.0f){
        return y;
    } else {
        return x;
    }
}
bool barSpectrum::plotBars() {
    bool haltGrowth = true;
    float newHeight;
    for(auto i : sample) {
        // if(i.second > 0) {
        //     std::cout << "i.second positive\n";
        // } else if(i.second == 0) {
        //     std::cout << "i.second zero \n";
        // } else {
        //     std:: cout << "i.second negative\n";
        // }
        // if(barGraph[i.first].getSize().y > 0) {
        //     std::cout << "barGraph[i.first] positive\n";
        // } else if(barGraph[i.first].getSize().y == 0) {
        //     std::cout << "barGraph[i.first] zero \n";
        // } else {
        //     std:: cout << "barGraph[i.first] negative\n";
        // }
        if(barGraph[i.first].getSize().y < i.second) {
            newHeight = decreaseHeight(i.second,barGraph[i.first].getSize().y);

        } else if(barGraph[i.first].getSize().y > i.second){
            newHeight = increaseHeight(i.second,barGraph[i.first].getSize().y);
        } else {
            newHeight = decreaseHeight(-200.0f,barGraph[i.first].getSize().y);

        }
         if(newHeight > (i.second)) { // dont change this im pre sure is correct lol
             haltGrowth = false;
         } else {
             haltGrowth = true;
         }
         // if(newHeight > 0) {
         //     std::cout << "newHeight positive\n";
         // } else if(newHeight == 0) {
         //     std::cout << "newHeight zero \n";
         // } else {
         //     std:: cout << "newHeight negative\n";
         // }
         // std::cout << newHeight << "\n";
         barGraph[i.first].setSize(sf::Vector2f(25.0f, newHeight));
         // std::cout << "i.first = " << i.first << " barGraph[i.first].getSize().y: " << barGraph[i.first].getSize().y << "\n";
         // std::cout << "i.first = " << i.first << " barGraph[i.first].getPosition().y: " << barGraph[i.first].getPosition().y << "\n";
         // std::cout << "origin: " << barGraph[i.first].getOrigin().x << ", " << barGraph[i.first].getOrigin().y << "\n";
    }
    changeBar += 5.0f;
    return haltGrowth;
}

void barSpectrum::readFFT(std::vector<complex_vec>::iterator cmplxVector,sf::Uint64 sampleRate, sf::Uint64 length) {
    double j = 0;
    double freq, magnitude, biggestMagnitude  = -1, biggestFrequency = 0, rangeIndex = 0;
    changeBar = 0.0f;
    this->clearSampleMap();
    // std::cout << "size of sample before loop: " << sample.size() << "\n";
    int counter = 0;
    for(std::vector<complex_num>::iterator i = cmplxVector->begin();
                                        i != cmplxVector->end(); i++) {
        freq = (j * (double)sampleRate) / (double)length;
        magnitude = 10 * std::log10(std::abs(*i));
        if(freqRanges.at(rangeIndex) <= freq && freq <= freqRanges.at(rangeIndex + 1)) {
            if(magnitude > biggestMagnitude) {
                biggestMagnitude = magnitude;
                biggestFrequency = freq;
            }
        } else {
            sample[findClosestFreq(biggestFrequency)] = (float)mapMagnitude(biggestMagnitude);
            rangeIndex++;
            biggestMagnitude = -1;
            if(rangeIndex == freqRanges.size() -1) {
                break;
            }

        }
        // std::cout << "freq: " << freq << " j: " << j << "\n";
        // std::cout << "freq: " << findClosestFreq(freq) << " mapMagnitude(magnitdue): " << (float)mapMagnitude(magnitude) << "\n";
        j++;
        if(j == ((length /2 ) - 1)) {
            break;
        }
    }
    // std::cout << "size of sample after loop: " << sample.size() << "\n";

}

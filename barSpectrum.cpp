/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.cpp : implementation of the application class
*/
#include "barSpectrum.h"

barSpectrum::barSpectrum(){}

barSpectrum::barSpectrum(int xWindow, int yWindow,std::pair<double,double> freqExtremes, std::pair<double,double> ampExtremes){
    // calc max number of bars in window and the freuency ranges per bar
    // this is window / pc dependent will need to be calc every launch of application

    numBars = floor(xWindow / xPosition) + 1;
    yWindowDim = yWindow;
    MAXHEIGHT = 10 * std::log10(ampExtremes.second);
    MINHEIGHT = (ampExtremes.first != 0 ? 10 * std::log10(ampExtremes.first) : 0);
    baseMagnitude = 0.3f * MAXHEIGHT;
    // std::cout << "maxheight and min height: ";
    // std::cout << MAXHEIGHT << " " << MINHEIGHT << "\n";
    // std::cout << "numBars: " << numBars << "\n";
    // temporary object used to store in barGraph
    sf::RectangleShape bar(sf::Vector2f(xPosition, defaultY));
    int x = 0;
    MAXFREQ = freqExtremes.second; MINFREQ = freqExtremes.first;
    // std::cout << MAXFREQ << " " << MINFREQ << "\n";
    // std::cout << "numBars: " << numBars << "\n";
    //******************* put in method?
    for(int i = 0; i < 8; i++) {
        // std::cout << "i: " << i << " i*numBars / 8: " << i * numBars / 8 << "\n";
        ranges.push_back(i * numBars / 8);
    }
    ranges.push_back(numBars);
    // ********************
    // std::cout << "size of ranges: " << ranges.size() << "\n";
    int counter = 0;
    for(float i = 1; i < numBars + 1; i++){
        // shifts position and sets color
        bar.setPosition(x, yWindow);
        calcColor(bar,i);

        // stores bar into unordered_map with respective freqency
        float index = mapFreq(i);
        // std::cout << "bar #: " << i << " mapFreq(i): " << index << "\n";
        barGraph[index] = std::make_pair(bar,std::make_pair(0,0));
        counter++;

        // std::cout << "mapFreq(i): " << mapFreq(i) << "\n";
        x += xPosition + 1;
    }

}

barSpectrum::~barSpectrum(){}

int barSpectrum::getnumBars(){
    return numBars;
}

float barSpectrum::mapFreq(float index) {
    double newFreq;
    newFreq = (((index -1 ) / (numBars - 1)) * (5000 - 20)) + 20;
    // int rangeIndex;
    // int i;
    // float min = 0, low = 50, subBass = 100, bass = 300,
    //  lowMidRange = 700, midRange = 1500, upMidRange = 2500,
    //  presence = 4000, max = 5000;
    // for( i = 0; i < ranges.size() - 1; i++) {
    //     if((ranges[i] < index) && (index <= ranges[i + 1])) {
    //         rangeIndex = i;
    //     }
    // }
    //
    //
    // switch(rangeIndex){
    //     case 0:
    //         newFreq = (((index - 1) / (ranges[rangeIndex] - 1)) * (low - min)) + min;
    //         break;
    //     case 1:
    //         newFreq = (((index - 1) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (subBass - low)) + low;
    //         break;
    //     case 2:
    //         newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (bass - subBass)) + subBass;
    //         break;
    //     case 3:
    //         newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (lowMidRange - bass)) + bass;
    //         break;
    //     case 4:
    //         newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (midRange - lowMidRange)) + lowMidRange;
    //         break;
    //     case 5:
    //         newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (upMidRange - midRange)) + midRange;
    //         break;
    //     case 6:
    //         newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (presence - upMidRange)) + upMidRange;
    //         break;
    //     case 7:
    //         newFreq = (((index - ranges[rangeIndex]) / (numBars - ranges[rangeIndex])) * (max - presence)) + presence;
    //         break;
    //
    // }

     return newFreq;
}

std::map<float,std::pair<sf::RectangleShape,std::pair<double,double>>>::iterator barSpectrum::start(){
    return barGraph.begin();
}

std::map<float,std::pair<sf::RectangleShape,std::pair<double,double>>>::iterator barSpectrum::last(){
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
    return (((magnitude - MINHEIGHT)/ (MAXHEIGHT - MINHEIGHT)) * ((-yWindowDim + 50.0f)- defaultY)) - 200.0f;
}

double barSpectrum::increaseHeight(double magnitude, std::pair<sf::RectangleShape,std::pair<double,double>> &bar) {
    double x = /*yWindowDim -*/ (bar.first.getSize().y - (-magnitude / 30.0f));
    bar.second.second++;
    //bar.second.first += 5.0f;
    double y =  magnitude;
    if((std::abs(y) - std::abs(x)) <= (magnitude / 30.0f)){
        return y;
    } else {
        return x;
    }
}
double barSpectrum::decreaseHeight(double magnitude, std::pair<sf::RectangleShape,std::pair<double,double>> &bar) {
    double x = /*yWindowDim -*/ (bar.first.getSize().y - (magnitude / (30.0f - bar.second.second)));
    //bar.second.second += 5.0f;
    double y =  magnitude;
    if((std::abs(y) - std::abs(x)) <= (magnitude / (30.0f - bar.second.second))) {
        return y;
    } else {
        return x;
    }
}

void barSpectrum::restoreHeight() {
    std::pair<double, double> reset = std::make_pair(0,0);
    for(auto i : barGraph) {
            i.second.first.setSize(sf::Vector2f(xPosition,defaultY));
            i.second.second = reset;

    }
}

bool barSpectrum::plotBars() {
    bool haltGrowth = true;
    float newHeight, decrHeight;
    for(auto i : sample) {

        if(barGraph[i.first].first.getSize().y <= i.second) {
            // if(barGraph[i.first].first.getSize().y != defaultY){
            decrHeight = decreaseHeight(defaultY,barGraph[i.first]);
            barGraph[i.first].first.setSize(sf::Vector2f(xPosition, decrHeight));

                // barGraph[i.first].first.setSize(sf::Vector2f(xPosition,defaultY));



        } else if(barGraph[i.first].first.getSize().y > i.second){
            // barGraph[i.first].first.setSize(sf::Vector2f(xPosition,i.second));

            newHeight = increaseHeight(i.second,barGraph[i.first]);
            barGraph[i.first].first.setSize(sf::Vector2f(xPosition, newHeight));

        }

         if(newHeight > (i.second)) { // dont change this im pre sure is correct lol
             haltGrowth = false;
         } else {
             haltGrowth = true;
         }


    }
    return haltGrowth;
}

void barSpectrum::resetRates() {
    std::pair<double, double> reset = std::make_pair(0,0);
    for(auto i : barGraph) {
        i.second.second = reset;
    }
}

void barSpectrum::readFFT(std::vector<complex_vec>::iterator cmplxVector,sf::Uint64 sampleRate, sf::Uint64 length) {
    double j = 0;
    double freq, magnitude, biggestMagnitude  = 0, biggestFrequency = 0, rangeIndex = 0;
    this->clearSampleMap();
    int counter = 0;
    for(std::vector<complex_num>::iterator i = cmplxVector->begin();
                                        i != cmplxVector->end(); i++) {
        freq = (j * (double)sampleRate) / (double)length;
        magnitude = 10 * std::log10(std::abs(*i));
        if(magnitude > baseMagnitude){
            sample[findClosestFreq(freq)] = (float)mapMagnitude(magnitude);
        }
        // if(magnitude > biggestMagnitude){
        //     biggestMagnitude = magnitude;
        //     biggestFrequency = freq;
        // }
        // if(freqRanges.at(rangeIndex) <= freq && freq <= freqRanges.at(rangeIndex + 1)) {
        //
        //     if(magnitude > biggestMagnitude && magnitude > baseMagnitude) {
        //         biggestMagnitude = magnitude;
        //         biggestFrequency = freq;
        //     }
        //
        // } else {
        //     sample[findClosestFreq(biggestFrequency)] = (float)mapMagnitude(biggestMagnitude);
        //     rangeIndex++;
        //     biggestMagnitude = 0;
        //     if(rangeIndex == freqRanges.size() -1) {
        //         break;
        //     }
        // }
        j++;
        if(j == ((length /2 ) - 1)) {
            break;
        }
    }
    // for(std::vector<complex_num>::iterator i = cmplxVector->begin();
    //                                     i != cmplxVector->end(); i++) {
    //     freq = (j * (double)sampleRate) / (double)length;
    //     magnitude = 10 * std::log10(std::abs(*i));
    //     sample[findClosestFreq(freq)] = (float)mapMagnitude(magnitude);
    //     if(freq = biggestFrequency){
    //         break;
    //     }
    // }

}

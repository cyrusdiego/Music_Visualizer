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
    MAXHEIGHT = 50 * std::log10(ampExtremes.second);
    MINHEIGHT = (ampExtremes.first != 0 ? 50 * std::log10(ampExtremes.first) : 0);
    baseMagnitude = 0.3f * MAXHEIGHT;
    // std::cout << "maxheight and min height: ";
    // std::cout << MAXHEIGHT << " " << MINHEIGHT << "\n";
    std::cout << "numBars: " << numBars << "\n";
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
    for(float i = 1; i < numBars + 1; i++){
        // shifts position and sets color
        bar.setPosition(x, yWindow);
        calcColor(bar,i);

        // stores bar into unordered_map with respective freqency
        float index = mapFreq(i);
        // std::cout << "bar #: " << i << " mapFreq(i): " << index << "\n";
        barGraph[index] = std::make_pair(bar,std::make_pair(40,40));
        // std::cout << "mapFreq(i): " << mapFreq(i) << "\n";
        x += xPosition;
    }

}

barSpectrum::~barSpectrum(){}

int barSpectrum::getnumBars(){
    return numBars;
}

float barSpectrum::mapFreq(float index) {
    double newFreq;
    int rangeIndex;
    int i;
    float min = 0, low = 20, subBass = 60, bass = 250,
     lowMidRange = 500, midRange = 2000, upMidRange = 4000,
     presence = 6000, max = 20000;
    for( i = 0; i < ranges.size() - 1; i++) {
        if((ranges[i] < index) && (index <= ranges[i + 1])) {
            // std::cout << "ranges[i]: " << ranges[i] << " ranges[i + 1]: " << ranges[i+1] << "\n";
            rangeIndex = i;
        }
    }
    // std::cout << ranges[7] << "\n";
    // std::cout << rangeIndex << "\n";

    switch(rangeIndex){
        case 0:
            newFreq = (((index - 1) / (ranges[rangeIndex] - 1)) * (low - min)) + min;
            break;
        case 1:
            newFreq = (((index - 1) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (subBass - low)) + low;
            break;
        case 2:
            newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (bass - subBass)) + subBass;
            break;
        case 3:
            newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (lowMidRange - bass)) + bass;
            break;
        case 4:
            newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (midRange - lowMidRange)) + lowMidRange;
            break;
        case 5:
            newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (upMidRange - midRange)) + midRange;
            break;
        case 6:
            newFreq = (((index - ranges[rangeIndex -1]) / (ranges[rangeIndex] - ranges[rangeIndex -1])) * (presence - upMidRange)) + upMidRange;
            break;
        case 7:
            newFreq = (((index - ranges[rangeIndex]) / (numBars - ranges[rangeIndex])) * (max - presence)) + presence;
            break;

    }

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
    double x = /*yWindowDim -*/ (bar.first.getSize().y - bar.second.first);
    //bar.second.first += 5.0f;
    double y =  magnitude;
    // std::cout << "yWindowDim - 200 - changeBar = " << x << " magnitude = " << y << "\n std::abs(y - x) <= 10.0f : " << (std::abs(y - x) <= 10.0f) << "\n";
    if((std::abs(y) - std::abs(x)) <= 40.0f){
        return y;
    } else {
        return x;
    }
}
double barSpectrum::decreaseHeight(double magnitude, std::pair<sf::RectangleShape,std::pair<double,double>> &bar) {
    double x = /*yWindowDim -*/ (bar.first.getSize().y + bar.second.second);
    //bar.second.second += 5.0f;
    double y =  magnitude;
    // std::cout << "yWindowDim - 200 - changeBar = " << x << " magnitude = " << y << "\n std::abs(y - x) <= 10.0f : " << (std::abs(y - x) <= 10.0f) << "\n";
    if((std::abs(y) - std::abs(x)) <= 40.0f){
        return y;
    } else {
        return x;
    }
}

void barSpectrum::restoreHeight() {
    for(auto i : barGraph) {
        if(i.second.first.getSize().y != defaultY){
            i.second.first.setSize(sf::Vector2f(xPosition,defaultY));
        }
    }
}

bool barSpectrum::plotBars() {
    bool haltGrowth = true;
    float newHeight;
    for(auto i : sample) {

        if(barGraph[i.first].first.getSize().y <= i.second) {
            if(barGraph[i.first].first.getSize().y != defaultY){
                barGraph[i.first].first.setSize(sf::Vector2f(xPosition,defaultY));

            }

        } else if(barGraph[i.first].first.getSize().y > i.second){
            newHeight = increaseHeight(i.second,barGraph[i.first]);
        }

         if(newHeight > (i.second)) { // dont change this im pre sure is correct lol
             haltGrowth = false;
         } else {
             haltGrowth = true;
         }

         barGraph[i.first].first.setSize(sf::Vector2f(xPosition, newHeight));
         // std::cout << "i.first = " << i.first << " barGraph[i.first].getSize().y: " << barGraph[i.first].getSize().y << "\n";
         // std::cout << "i.first = " << i.first << " barGraph[i.first].getPosition().y: " << barGraph[i.first].getPosition().y << "\n";
         // std::cout << "origin: " << barGraph[i.first].getOrigin().x << ", " << barGraph[i.first].getOrigin().y << "\n";
    }
    return haltGrowth;
}

void barSpectrum::resetRates() {
    std::pair<double, double> reset = std::make_pair(5,5);
    for(auto i : barGraph) {
        i.second.second = reset;
    }
}

void barSpectrum::readFFT(std::vector<complex_vec>::iterator cmplxVector,sf::Uint64 sampleRate, sf::Uint64 length) {
    double j = 0;
    double freq, magnitude, biggestMagnitude  = 0, biggestFrequency = 0, rangeIndex = 0;
    this->clearSampleMap();
    // std::cout << "size of sample before loop: " << sample.size() << "\n";
    int counter = 0;
    restoreHeight();
    for(std::vector<complex_num>::iterator i = cmplxVector->begin();
                                        i != cmplxVector->end(); i++) {
        freq = (j * (double)sampleRate) / (double)length;
        magnitude = 50 * std::log10(std::abs(*i));

        if(freqRanges.at(rangeIndex) <= freq && freq <= freqRanges.at(rangeIndex + 1)) {
            // std::cout << "freqRanges.at(rangeIndex): " << freqRanges.at(rangeIndex) << " freqRanges.at(rangeIndex + 1) "<< freqRanges.at(rangeIndex + 1) << " freq " << freq <<"\n";
            // std::cout << "baseMagnitude: " << baseMagnitude << "\n";

            // std::cout << "magnitude: " << magnitude << "\n";
            if(magnitude > biggestMagnitude && magnitude > baseMagnitude) {
                biggestMagnitude = magnitude;
                biggestFrequency = freq;
            }
            // std::cout << "biggestmagnitude: " << biggestMagnitude << "\n";

        } else {
            sample[findClosestFreq(biggestFrequency)] = (float)mapMagnitude(biggestMagnitude);
            // std::cout << "magnitide @ here sample[bigfreq]: " << sample[findClosestFreq(biggestFrequency)] << "\n";
            rangeIndex++;
            biggestMagnitude = 0;
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

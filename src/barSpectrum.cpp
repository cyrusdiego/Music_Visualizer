/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and 1531475
    CMPUT 275 WINTER 2019 Final Project: FFT Visualizer

    barSpectrum.cpp : implementation of barSpectrum class
        - Holds all bars in map with frequencies as keys
        - increases / decreases heights of bars
        - reads in FFT Buffer and changes heights of the bars
*/
#include "barSpectrum.h"

// constructor
barSpectrum::barSpectrum(){}

/*
    constructor to setup bar class
    @param : xWindow dimension
    @param : yWindow dimension
    @param : pair highest / lowest frequency
    @param : pair highest / lowest amplitude
*/
barSpectrum::barSpectrum(int xWindow, int yWindow,std::pair<double,double> freqExtremes, std::pair<double,double> ampExtremes){

    // Initial calculations of variables
    numBars = floor(xWindow / xPosition) + 1;
    yWindowDim = yWindow;
    MAXHEIGHT = 10 * std::log10(ampExtremes.second);  // converts to dB
    MINHEIGHT = (ampExtremes.first != 0 ? 10 * std::log10(ampExtremes.first) : 0);
    baseMagnitude = 0.4f * MAXHEIGHT;  // base magnitude is 40% of maximum height
    MAXFREQ = freqExtremes.second; MINFREQ = freqExtremes.first;

    // temporary object used to store in barGraph
    sf::RectangleShape bar(sf::Vector2f(xPosition, defaultY));
    int x = 0;

    // Establish cutoff ranges for the bars
    for(int i = 0; i < 8; i++) {
        ranges.push_back(i * numBars / 8);
    }
    ranges.push_back(numBars);

    // Inserts rectangle shapes into map
    for(float i = 1; i < numBars + 1; i++){
        // shifts position and sets color
        bar.setPosition(x, yWindow);
        calcColor(bar,i);

        // stores bar into unordered_map with respective freqency
        float index = mapFreq(i);

        barGraph[index] = std::make_pair(bar,0);

        x += xPosition + 1;
    }

}

// destructor
barSpectrum::~barSpectrum(){}

// Maps the bar index to a freuency range of 0Hz to 5000Hz (chosen values)
float barSpectrum::mapFreq(float index) {
    double newFreq;
    newFreq = (((index - 1) / (numBars - 1)) * (5000));
    return newFreq;
}

// Returns begining Iterator through the map
std::map<float,std::pair<sf::RectangleShape,double>>::iterator barSpectrum::start(){
    return barGraph.begin();
}

// Returns end Iterator through the map
std::map<float,std::pair<sf::RectangleShape,double>>::iterator barSpectrum::last(){
    return barGraph.end();
}


// Creates even gradient (rainbow) across the bars
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

// resets the sample map to ensure its empty before refilling
void barSpectrum::clearSampleMap(){
    sample.clear();
}

/*
    O(logn) -> uses fact that std::map is a binary tree
    Finds closest freqency in the range of 0Hz to 5000Hz
    @param : phase, the phase we want to snap to in the map
*/
double barSpectrum::findClosestFreq(double phase) {
    double newPhase;

    // if phase is less than 0, then snap to lowest frequency
    if(phase < 0) {
        return barGraph.begin()->first;
    } else {  // find where the phase would be inserted in the binary tree
        lowBound = barGraph.lower_bound(phase);  // gets lower key
        if (lowBound != barGraph.end()) {
            upBound = barGraph.upper_bound(phase);  // gets upper key

            // returns which ever phase is closest to the input phase
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

/*
    Takes magnitude of the audio sample and normalizes it to y dimensions on the screen
    @param : magnitude, the magnitude we want to map to window application
    @return : the new magnitude
*/
double barSpectrum::mapMagnitude(double magnitude) {
    return (((magnitude - MINHEIGHT)/ (MAXHEIGHT - MINHEIGHT)) * ((-yWindowDim + 50.0f)- defaultY)) - 200.0f;
}

/*
    gradually increases the height of the bars based on fps
    @param : magnitude (target height)
    @param : pair, the bar we want to change
    @return : the new height
*/
double barSpectrum::increaseHeight(double magnitude, std::pair<sf::RectangleShape,double> &bar) {
    double x = (bar.first.getSize().y - (-magnitude / fps));  // gets the new height
    bar.second++;  // increments frame count
    double y =  magnitude;  // original height of bar

    if((std::abs(y) - std::abs(x)) <= (magnitude / fps)){
        return y;  // if the difference is close, return original
    } else {
        return x;  // if height is not close enough, increase height
    }
}

/*
    gradually decreases the height of the bars barsed on fps and remaining frames
    @param : magnitude (target height)
    @param : pair, the bar we want to change
    @return : the new height
*/
double barSpectrum::decreaseHeight(double magnitude, std::pair<sf::RectangleShape,double> &bar) {
    double x = (bar.first.getSize().y - (magnitude / (fps- bar.second)));  // gets the new height
    double y =  magnitude;  // original height of bar


    if((std::abs(y) - std::abs(x)) <= (magnitude / (fps - bar.second))) {
        return y;  // if the difference is close, return original
    } else {
        return x;  // if height is not close enough, increase height
    }
}

/*
    resets the height of the bars to 200px and the frame counter to 0
*/
void barSpectrum::restoreHeight() {
    double reset = 0;
    for(auto i : barGraph) {
            i.second.first.setSize(sf::Vector2f(xPosition,defaultY));
            i.second.second = reset;

    }
}

/*
    Determines whether to increase height of decrease based on target magnitude
    @return : bool if all the bars have reached their target height
    If all bars reached target, will refresh FFT Buffer
*/
bool barSpectrum::plotBars() {
    bool haltGrowth = true;
    float newHeight, decrHeight;

    for(auto i : sample) {  // iterates thru collected samples

        // if the current height is at the target OR greater than, decrease
        if(barGraph[i.first].first.getSize().y <= i.second) {
            decrHeight = decreaseHeight(defaultY,barGraph[i.first]);  // decrease height
            barGraph[i.first].first.setSize(sf::Vector2f(xPosition, decrHeight));  // sets the size

        // if the current height is less than target, increase
        } else if(barGraph[i.first].first.getSize().y > i.second){
            newHeight = increaseHeight(i.second,barGraph[i.first]);  // increase height
            barGraph[i.first].first.setSize(sf::Vector2f(xPosition, newHeight));  // sets the size

        }

        // If ALL Bars are at their target height, then refresh the buffer
         if(newHeight > (i.second)) {
             haltGrowth = false;
         } else {
             haltGrowth = true;
         }

    }
    return haltGrowth;
}


/*
    Reads the FFT Buffer (complex vector) and stores the target magnitudes for the
    frequencies to a map to be used later to change the bar heights
    @param : complex vector iterator that points to a vector of complex numbers
    @param : sample rate used to calculate the frequency at each iteration
    @param : length of the sample vector
*/
void barSpectrum::readFFT(std::vector<complex_vec>::iterator cmplxVector,sf::Uint64 sampleRate, sf::Uint64 length) {
    double j = 0;
    double freq, magnitude, biggestMagnitude  = 0, biggestFrequency = 0, rangeIndex = 0;
    int counter = 0;

    this->clearSampleMap();  // resets the sample map

    // iterate thru the iterator to get sample information
    for(std::vector<complex_num>::iterator i = cmplxVector->begin();
                                        i != cmplxVector->end(); i++) {

        // calculate frequency and magnitude
        freq = (j * (double)sampleRate) / (double)length;
        magnitude = 10 * std::log10(std::abs(*i));

        // Will only plot the bars with a certain amplitude
        if(magnitude > baseMagnitude){
            sample[findClosestFreq(freq)] = (float)mapMagnitude(magnitude);
        }
        // increment counter
        j++;
        if(j == ((length / 2 ) - 1)) {  // break loop at half of the samples
            break;
        }
    }


}

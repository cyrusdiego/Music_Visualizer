/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    bars.h : header file declaring bars class
*/

#ifndef MUSICPROCESSOR_H
#define MUSICPROCESSOR_H
#include "globals.h"

/* Music Processor class will run the fouring transform on the samples of them
song
*/
class musicProcessor {
public:
    musicProcessor();
    musicProcessor(std::string songName);
    ~musicProcessor();
    void FFT(complex_vec &vec);
    sf::Uint64 getLength();
    std::vector<complex_vec>::iterator getIterator();
    std::vector<complex_vec>::iterator last();
    void play();
    void firstHalf(std::vector<complex_vec> &vec);
    void secondHalf(std::vector<complex_vec> &vec);
    std::pair <double,double> getMaxMinFreq();
    sf::Uint64 getSampleRate();
    std::pair<double,double> getMaxMinAmp();

private:
    sf::InputSoundFile file;
    sf::InputSoundFile file2;
    sf::Music music;
    sf::Uint64 sampleRate;
    sf::Uint64 sampleLength = 32768;
    std::vector<complex_vec> freqDomain;
    std::vector<complex_vec>::iterator freqDomainItr;
    double max;
    double min;
    double maxAmplitude;
    double minAmplitude;
    sf::Uint64 halfSample;
};


#endif

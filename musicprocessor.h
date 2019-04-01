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
    void getLength();
    std::vector<complex_vec>::iterator getIterator();
    void play();
    void firstHalf(std::vector<complex_vec> &vec);
    void secondHalf(std::vector<complex_vec> &vec);

private:
    sf::InputSoundFile file;
    sf::InputSoundFile file2;
    sf::Music music;
    sf::Uint64 samplerate;
    sf::Uint64 sampleLength;
    std::vector<complex_vec> freqDomain;
    std::vector<complex_vec>::iterator freqDomainItr;

    sf::Uint64 halfSample;
};


#endif

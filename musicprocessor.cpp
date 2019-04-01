/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    bars.h : header file declaring bars class
*/
// threads: https://stackoverflow.com/questions/17472827/create-thread-inside-class-with-function-from-same-class
#include "musicprocessor.h"
#include <thread>
complex_num makeComp(sf::Int16 i) {
    complex_num temp (0,0);
    return temp+=(double)i;
}

musicProcessor::musicProcessor(){}

musicProcessor::musicProcessor(std::string songName) {
    // load the song into the sound object
    std::vector<complex_vec> freqOne;
    std::vector<complex_vec> freqTwo;
    if (!music.openFromFile(songName));
    if (!file.openFromFile(songName));
    if (!file2.openFromFile(songName));
    samplerate = file.getSampleRate();
    sf::Uint64 numSamples = file.getSampleCount();
    halfSample = (numSamples/(samplerate*2));
    // will make sure that the array has a a power of 2 number of elements
    getLength();
    std::thread first (&musicProcessor::firstHalf,this,std::ref(freqOne));
    secondHalf (freqTwo);
    first.join();
    freqDomain.insert (freqDomain.begin(),freqOne.begin(),freqOne.end());
    freqDomain.insert(freqDomain.end(),freqTwo.begin(),freqTwo.end());
    freqDomainItr = freqDomain.begin();



}
void musicProcessor::firstHalf(std::vector<complex_vec> &vec){
    int counter = 0;
    sf::Uint64 count;
    while (counter < halfSample){
        sf::Int16 sample[sampleLength] = {0};
        count = file.read(sample,samplerate);
        std::vector <sf::Int16> temp(sample,sample + sampleLength);
        complex_vec compSample(sampleLength);
        std::transform(temp.begin(),temp.end(),compSample.begin(),makeComp);
        FFT(compSample);
        vec.push_back(compSample);
        counter++;
    }
}

void musicProcessor::secondHalf(std::vector<complex_vec> &vec){
    file2.seek(file.getSampleCount()/2);
    int counter = 0;
    sf::Uint64 count;
    while (count > 0){
        sf::Int16 sample[sampleLength] = {0};
        count = file2.read(sample,samplerate);
        std::vector <sf::Int16> thing(sample,sample+sampleLength);
        complex_vec compSample(sampleLength);
        std::transform(thing.begin(),thing.end(),compSample.begin(),makeComp);
        FFT(compSample);
        vec.push_back(compSample);
    }
}

musicProcessor::~musicProcessor(){}

void musicProcessor::play() {
    music.play();
}

std::vector<complex_vec>::iterator musicProcessor::getIterator(){
    freqDomainItr++;
    return --freqDomainItr;
}


void musicProcessor::getLength(){
    double power = log2(samplerate);
    sampleLength = ((fmod(power,2.0) == 0.0) ? samplerate : pow(2,(int)power+1));
}

void musicProcessor::FFT(complex_vec& vec){
    assert(log2(vec.size()) >= 0); // ensures that the size is 2^m m >= 0

    sf::Uint64 N = vec.size();
    if(N == 1){
        return;  // figure out what to actually return
    }
    else{
        //https://stackoverflow.com/questions/33787939/sort-vector-by-even-and-odd-indices-c
        stable_partition(begin(vec),end(vec),
                        [&vec](complex_num const& a){return 0==((&a-&vec[0])%2);});

        //rearrange(samples);  // rearrange order for easier odd / even
        complex_num W_N = std::polar(1.0,(-2*pi)/N);;  // root of Unity
        complex_num W(1,0);

        // Divide
        complex_vec sample_even;
        complex_vec sample_odd;

        sample_even.insert(sample_even.begin(),vec.begin(), vec.begin() + N/2);
        sample_odd.insert(sample_odd.begin(),vec.begin() + N/2, vec.end());

        // conquer
        FFT(sample_even);
        FFT(sample_odd);

        for(sf::Uint64 j = 0; j < (N / 2); ++j){
            vec.at(j) = sample_even.at(j) + (W * sample_odd.at(j));
            vec.at(j + N/2) = sample_even.at(j) - (W* sample_odd.at(j));
            W *= W_N;
        }
    }
}

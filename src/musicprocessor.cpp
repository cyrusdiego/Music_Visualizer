/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and 1531475
    CMPUT 275 WINTER 2019 Final Project: FFT Visualizer

    musicprocessor.cpp : runs FFT for the song loaded and also plays the song
*/
// threads: https://stackoverflow.com/questions/17472827/create-thread-inside-class-with-function-from-same-class
#include "musicprocessor.h"
#include <thread>
#include <typeinfo>

/*
    This function will convert real input into an imaginary number
    @param : i is the real number to convert to complex
    @return : the complex number converted of form i + 0j
*/
complex_num makeComp(sf::Int16 i) {
    complex_num temp (0,0);
    return temp+=(double)i;
}

musicProcessor::musicProcessor(){}

/*
    Contructor
    @param : the name of the song to load
*/
musicProcessor::musicProcessor(std::string songName) {
    // load the song into the sound object
    std::vector<complex_vec> freqOne; // will store the first half of the samples
    std::vector<complex_vec> freqTwo; // will store the second half of the sampes
    if (!music.openFromFile(songName)); // will load the song into music object for playing
    if (!file.openFromFile(songName)); // load the song information into the variable
    if (!file2.openFromFile(songName));
    sampleRate = getSampleRate();
    sf::Uint64 numSamples = file.getSampleCount();
    double max = 0, min = 0; // maximum and minimum frequency
    maxAmplitude = 0;
    minAmplitude = 10000000;

    // divide and conquer approach to split the workload of calculating fft
    // of whole song
    std::thread first (&musicProcessor::firstHalf,this,std::ref(freqOne));
    secondHalf (freqTwo);
    first.join();
    
    // will join all the transformed samples into a single vector
    freqDomain.insert (freqDomain.begin(),freqOne.begin(),freqOne.end());
    freqDomain.insert(freqDomain.end(),freqTwo.begin(),freqTwo.end());
    freqDomainItr = freqDomain.begin();

}

/*
    will return a pair that contains the minimum and maximum amplitudes
*/
std::pair<double,double> musicProcessor::getMaxMinAmp(){
    return std::make_pair(minAmplitude,maxAmplitude);
}

/*
    will return the sample rate of the song
*/
sf::Uint64 musicProcessor::getSampleRate() {
    return file.getSampleRate();
}

/*
    Returns the minimum and maximum frequencies
*/
std::pair <double,double> musicProcessor::getMaxMinFreq(){
    max = (((sampleLength / 2) - 1) * sampleRate) / sampleLength;
    std::pair <double,double> extremes = std::make_pair(min,max);
    return extremes;
}

// https://stackoverflow.com/questions/3555318/implement-hann-window (hanning window refrence)
/*
    Will perform the FFT transform on the first half of the samples
    @param: the complex vector of samples to run FFT thru
*/
void musicProcessor::firstHalf(std::vector<complex_vec> &vec){
    int counter = 0; // flag variable used when reading and applying fourier
                        // transform to the samples
    sf::Uint64 count;
    while (counter < file.getSampleCount()/2){
        sf::Int16 sample[sampleLength] = {0}; // zero padding
        // loads the next sampleLength amount of samples into the sample array
        count = file.read(sample,sampleLength);
        // applies hanning window function
        for (int i = 0; i < sampleLength; i++) {
            double multiplier = 0.5 * (1 - cos(2*pi*i/(sampleLength - 1)));
            sample[i] = multiplier * sample[i];
        }
        // will store the samples in the array in a vector instead
        std::vector <sf::Int16> sampleVec(sample,sample+sampleLength);
        complex_vec compSample(sampleLength);
        // converts all the samples to complex numbers
        std::transform(sampleVec.begin(),sampleVec.end(),compSample.begin(),makeComp);
        FFT(compSample); // perform FFT on the samples
        vec.push_back(compSample); // add the vector of samples to the table
        counter+=count;
    }
}

/*
    Will perform the FFT transform on the second half of the samples
    @param: the complex vector of samples to run FFT thru
*/
void musicProcessor::secondHalf(std::vector<complex_vec> &vec){
    file2.seek(file.getSampleCount()/2);  // starts at 2nd half of music file
    sf::Uint64 count;
    while (count > 0){
        sf::Int16 sample[sampleLength] = {0};  // zero padding
        // loads the next sampleLength amount of samples into the sample array
        count = file2.read(sample,sampleLength);
        // apply hanning window
        for (int i = 0; i < sampleLength; i++) {
            double multiplier = 0.5 * (1 - cos(2*pi*i/(sampleLength - 1)));
            sample[i] = multiplier * sample[i];
        }
        // will store the samples in the array in a vector instead
        std::vector <sf::Int16> sampleVec(sample,sample+sampleLength);
        complex_vec compSample(sampleLength);
        // converts all the samples to complex numbers
        std::transform(sampleVec.begin(),sampleVec.end(),compSample.begin(),makeComp);
        FFT(compSample); // perform the FFT on the samples
        vec.push_back(compSample); // add the vector of samples to the table
    }
}

/*
    Destructor
*/
musicProcessor::~musicProcessor(){}

/*
    Will play the music object that was load previously
*/
void musicProcessor::play() {
    music.play();
}

/*
    returns the pointer to freqDomain vector
*/
std::vector<complex_vec>::iterator musicProcessor::getIterator(){
    auto temp = freqDomainItr;
    freqDomainItr++;
    return temp;
}
/*
    Will return the end iterator of the table containing all of the samples
*/
std::vector<complex_vec>::iterator musicProcessor::last(){
    return freqDomain.end();
}


/*
    Returns the length of samples that are read in at a time
*/
sf::Uint64 musicProcessor::getLength(){
    return sampleLength;
}

/*
    will perform the fast fourier transform on the samples
    @param : complex vector to run FFT thru
*/
void musicProcessor::FFT(complex_vec& vec){
    assert(log2(vec.size()) >= 0); // ensures that the size is 2^m m >= 0

    sf::Uint64 N = vec.size();
    if(N == 1){
        return;  // figure out what to actually return
    }
    else{
        //https://stackoverflow.com/questions/33787939/sort-vector-by-even-and-odd-indices-c
        // puts even index elements at start and odd index at end
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

        // will multiply the sample by the ith root of unity
        for(sf::Uint64 j = 0; j < (N / 2); ++j){
            vec.at(j) = sample_even.at(j) + (W * sample_odd.at(j));
            vec.at(j + N/2) = sample_even.at(j) - (W* sample_odd.at(j));
            W *= W_N;

            // will obtain the maximum and minimum amplitudes
            if (std::abs(vec.at(j)) > maxAmplitude){
                maxAmplitude = abs(vec.at(j));
            } else if (std::abs(vec.at(j)) < minAmplitude) {
                minAmplitude = std::abs(vec.at(j));
            }
            if (std::abs(vec.at(j + (N/2))) > maxAmplitude){
                maxAmplitude = std::abs(vec.at(j + (N/2)));
            } else if (std::abs(vec.at(j+(N/2))) < minAmplitude) {
                minAmplitude = std::abs(vec.at(j+(N/2)));

            }


        }
    }
}

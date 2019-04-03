#include <cassert>
#include <cmath>  // for log2
#include <math.h>
#include <iostream>  // for cout
#include <vector>
#include <complex>
#include <algorithm>
#include <SFML/Audio.hpp>
const double pi = 3.141592653589793238460;
using namespace std;

typedef complex<double> complex_num;
typedef vector<complex_num> complex_vec;

// main fft function
// double check type of the samples, how big of an int
void FFT(complex_vec& samples){
    assert(log2(samples.size()) >= 0); // ensures that the size is 2^m m >= 0

    sf::Uint64 N = samples.size();
    if(N == 1){
        return;  // figure out what to actually return
    }
    else{
        //https://stackoverflow.com/questions/33787939/sort-vector-by-even-and-odd-indices-c
        stable_partition(begin(samples),end(samples),
                        [&samples](complex_num const& a){return 0==((&a-&samples[0])%2);});

        //rearrange(samples);  // rearrange order for easier odd / even
        complex_num W_N = polar(1.0,(-2*pi)/N);;  // root of Unity
        complex_num W(1,0);

        // Divide
        complex_vec sample_even;
        complex_vec sample_odd;

        sample_even.insert(sample_even.begin(),samples.begin(), samples.begin() + N/2);
        sample_odd.insert(sample_odd.begin(),samples.begin() + N/2, samples.end());

        // conquer
        FFT(sample_even);
        FFT(sample_odd);

        for(sf::Uint64 j = 0; j < (N / 2); ++j){
            samples.at(j) = sample_even.at(j) + (W * sample_odd.at(j));
            samples.at(j + N/2) = sample_even.at(j) - (W* sample_odd.at(j));
            W *= W_N;
        }

    }

}

int main() {
    sf::InputSoundFile file;

    if (!file.openFromFile("253011553368158.wav"));

    sf::Uint64 samplerate = file.getSampleRate();
    double power = log2(samplerate);
    sf::Uint64 rate = ((fmod(power,2.0) == 0.0) ? samplerate : pow(2,(int)power+1));
    sf::Int16 sample[rate] = {0};
    sf::Uint64 count;

    do {
        count = file.read(sample,samplerate);
        sf::Sound sound;
        sound.setBuffer(sample);
        sound.play();
        complex_vec input;
        for(sf::Uint64 i = 0; i < rate; i++){
            complex<double> temp((double)sample[i],0);
            input.push_back(temp);
        }
        FFT(input);

        for(auto i = input.begin(); i != input.end(); i++){
            cout << "(" << real(*i) << "," << imag(*i) << ")" << endl;
        }
    }
    while (count > 0);
    return 0;
}
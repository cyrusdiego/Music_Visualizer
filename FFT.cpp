#include <utility>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
double pi = 3.1415926535897; // use preprocessor or something
using namespace std;

// rearrange array
// @param: array of audio signal (all real values)
void rearrange(vector<pair<double,double>> &samples){
    vector<pair<double,double>> even, odd;
    int N = samples.size();
    for(int i = 0; i < N; i++){
        if(i % 2 == 0){
            even.push_back(*samples.begin());
            samples.erase(samples.begin());
        }
        else{
                odd.push_back(*samples.begin());
                samples.erase(samples.begin());
        }
    }

    samples.insert(samples.begin(), even.begin(),even.end());
    samples.insert(samples.end(),odd.begin(),odd.end());

}
// Convert a + bj to D <(phase)
void mag_phase(){

}

// main fft function
// double check type of the samples, how big of an int
vector<pair<double,double>> FFT(vector<pair<double,double>> samples){
    assert(log2(samples.size()) >= 0); // ensures that the size is 2^m m >= 0

    rearrange(samples);  // rearrange order for easier odd / even
    int N = samples.size(); // get size of array

    if(N == 1){
        return samples;  // figure out what to actually return
    }
    else{
        pair<double,double> W_N = make_pair(cos(2*pi/N),sin(2*pi/N));
        double W = 1;

        // splitting to even and odd
        vector<pair<double,double>> sample_even;
        vector<pair<double,double>> sample_odd;

        samples_even.insert(samples_even.begin(),samples.begin(), samples.begin() + N/2);
        samples_even.insert(samples_even.begin(),samples.begin() + N/2 + 1, samples.end());

        vector<pair<double,double>> Y_even = FFT(sample_even);
        vector<pair<double,double>> Y_odd = FFT(sample_odd);

        vector<pair<double,double>> Y;
        // let c++ decide N/2 - 1
        for(int j = 0; j < N / 2 - 1; j++){




        }

    }

    return Y;
    // return array of complex numbers in frequency domain
}

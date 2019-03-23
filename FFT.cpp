#include <cassert>
#include <cmath>  // for log2
#include <iostream>  // for cout
#include <vector>
#include <complex>
const double pi = 3.141592653589793238460;
using namespace std;

typedef complex<double> complex_num;
typedef vector<complex_num> complex_vec;

// rearrange array
// @param: array of audio signal (all real values)
void rearrange(complex_vec &samples){
    complex_vec even, odd;
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

// main fft function
// double check type of the samples, how big of an int
void FFT(complex_vec& samples){
    assert(log2(samples.size()) >= 0); // ensures that the size is 2^m m >= 0

    int N = samples.size();

    if(N == 1){
        return;  // figure out what to actually return
    }
    else{
        rearrange(samples);  // rearrange order for easier odd / even
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

        for(int j = 0; j < (N / 2); ++j){
            samples.at(j) = sample_even.at(j) + (W * sample_odd.at(j));
            samples.at(j + N/2) = sample_even.at(j) - (W* sample_odd.at(j));
            W *= W_N;
        }

    }

}

int main(){
    double arr[8] = {0,1,2,3,4,5,6,7};

    complex_vec input;
    for(int i = 0; i < 8; i++){
        complex<double> temp(arr[i],0);
        input.push_back(temp);
    }
    cout << "input " << endl;
    for(auto i = input.begin(); i != input.end();i++){
        cout << real(*i) << " " << imag(*i) << endl;
    }
    FFT(input);
    cout << "FFT results" << endl;
    for(auto i = input.begin(); i != input.end(); i++){
        cout << real(*i) << " " << imag(*i) << endl;
    }
    return 0;
}

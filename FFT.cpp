#include <utility>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <complex>
double pi = 3.1415926535897; // use preprocessor or something
using namespace std;

// rearrange array
// @param: array of audio signal (all real values)
void rearrange(vector<complex<double>> &samples){
    vector<complex<double>> even, odd;
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
vector<complex<double>> FFT(vector<complex<double>> samples,string cmd){
    cout << cmd << endl;
    assert(log2(samples.size()) >= 0); // ensures that the size is 2^m m >= 0
    int N = samples.size(); // get size of array


    if(N == 1){
        return samples;  // figure out what to actually return
    }
    else{
        rearrange(samples);  // rearrange order for easier odd / even

        complex<double> W_N = polar((double)1,2*pi/N);
        complex<double> W(1,0);

        // splitting to even and odd
        vector<complex<double>> sample_even;
        vector<complex<double>> sample_odd;

        sample_even.insert(sample_even.begin(),samples.begin(), samples.begin() + N/2);
        sample_odd.insert(sample_odd.begin(),samples.begin() + N/2, samples.end());

        vector<complex<double>> Y_even = FFT(sample_even,"even");
        vector<complex<double>> Y_odd = FFT(sample_odd,"odd");
        vector<complex<double>> Y;
        if(N == 4){
            cout << Y_even.size() << endl;
            cout << Y_odd.size() << endl;
        }
        int counter = 0;
        for(int j = 0; j < N / 2; j++){
            if(N == 2){
                Y.insert(Y.begin() + j,Y_even.at(j) + W*Y_odd.at(j));
                Y.insert(Y.begin() + j + N/2,Y_even.at(j) - W*Y_odd.at(j));
            }
            else{
                Y.insert(Y.begin() + j,Y_even.at(j) + W*Y_odd.at(j));
                Y.insert(Y.begin() + j + N/2 - 1,Y_even.at(j) - W*Y_odd.at(j));
            }

            W *= W_N;
        }

        return Y;
    }

    // return array of complex<double> numbers in frequency domain
}

int main(){
    int arr[] = {1,2,3,4};
    vector<complex<double>> input;
    for(int i = 0; i < 4; i++){
        complex<double> temp((double)arr[i],0);
        input.push_back(temp);
    }
    vector<complex<double>> output = FFT(input, "first");
    for(auto i = output.begin(); i != output.end(); i++){
        cout << real(*i) << " " << imag(*i) << endl;
    }
    return 0;
}

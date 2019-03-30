#include <cassert>
#include <cmath>  // for log2
#include <math.h>
#include <iostream>  // for cout
#include <vector>
#include <complex>
#include <algorithm>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
const double pi = 3.141592653589793238460;
using namespace std;

typedef complex<double> complex_num;
typedef vector<complex_num> complex_vec;

// main fft function
// double check type of the samples, how big of an int
complex_num conjugate (complex_num i) {
    return conj(i);
}
void FFT(complex_vec& samples){
    assert(log2(samples.size()) >= 0); // ensures that the size is 2^m m >= 0

    sf::Uint64 N = samples.size();
    if(N == 1){
        return;  // figure out what to actually return
    }
    else{
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

void IFFT(complex_vec& samples){
    assert(log2(samples.size()) >= 0); // ensures that the size is 2^m m >= 0

    sf::Uint64 N = samples.size();
    if(N == 1){
        return;  // figure out what to actually return
    }
    else{
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

string get_songchoice () {
    std::ifstream file;
    std::string current_song;
    file.open("SONGS.txt"); // open file with song names
    std::string line; // stores the current line read in
    std::vector <std::string> song_name; // vector to store all the names
    sf::Font font;
    int count = 0;

    if (!font.loadFromFile("Marilatte.ttf")){
        std::cout <<"FUCK" << std::endl;
    }
// Create a text
    sf::Text text;
    text.setFont(font);
// read in all of the song names and store them
    while (std::getline(file,line)){
        song_name.push_back(line);
        count++;
    }

    file.close();

    // sets the size and what is going to be printed
    text.setString(song_name.at(0));
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setColor(sf::Color::Red);
    int index = 0;
    current_song = song_name.at(0);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        if(window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                window.close();

            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (index > 0))){
                index--;
                current_song = song_name.at(index);
                text.setString(current_song);

            } else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (index < count-1))) {
                index++;
                current_song = song_name.at(index);
                text.setString(current_song);
        }
    }

        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();

    }

    return current_song;
}

int main() {
    sf::InputSoundFile file;
    string song = get_songchoice();

    if (!file.openFromFile(song));

    sf::Uint64 samplerate = file.getSampleRate();
    double power = log2(samplerate);
    sf::Uint64 rate = ((fmod(power,2.0) == 0.0) ? samplerate : pow(2,(int)power+1));
    sf::Int16 sample[rate] = {0};
    sf::Uint64 count;
    int counter = 0;
    do {
        counter ++;

        count = file.read(sample,samplerate);
        complex_vec input;
        for(sf::Uint64 i = 0; i < rate; i++){
            complex<double> temp((double)sample[i],0);
            input.push_back(temp);
        }
        thing = input.size();
        FFT(input);
        
        //std::transform (input.begin(), input.end(), input.begin(),conjugate);
        // IFFT(input);
        // for(auto i = input.begin(); i != input.end(); i++){
        //     cout << real(*i) << endl;
        // }
    }
    while (counter!=2);
    return 0;
}

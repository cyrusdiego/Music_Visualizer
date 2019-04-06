/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and 1531475
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    globals.h : header file containing content all files require
*/

#ifndef GLOBALS_H
#define GLOBALS_H

// SFML Modules
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

// STL / C++ Libraries 
#include <string>
#include <cassert>  // for assert
#include <cmath>  // for log2
#include <math.h>
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <fstream>
#include <map>

// Constants
const double pi = 3.141592653589793238460;  // needed for fft and hanning window

// alias for complex vecs / numbers
typedef std::complex <double> complex_num;
typedef std::vector <complex_num> complex_vec;

#endif

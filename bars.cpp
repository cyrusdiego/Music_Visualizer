/*
    NAMES: CYRUS DIEGO and DANIEL ROJAS-CARDONA
    ID: 1528911 and
    CMPUT 275 WINTER 2019 Final Project: MUSIC VISUALIZER

    application.cpp : implementation of the application class
*/
#include "globals.h"
#include "bars.h"
#include <iostream>

bars::bars(){
    sf::RectangleShape temp;
    int x = 0;
    int r = 255, g = 30, b = 0;
    for(int i = 0; i < 100; i++){
        temp.setSize(sf::Vector2f(10.0f, 500.0f));
        temp.setPosition(x,800);
        sf::Color temp_color(r - i*2, g + i*2, b + i*2);
        temp.setFillColor(temp_color);
        barGraph.push_back(temp);
        x += 20;
    }
}

bars::~bars(){}

sf::RectangleShape bars::getBar(int i){
    return barGraph.at(i);
}

std::vector<sf::RectangleShape>::const_iterator bars::begin(){
    return barGraph.begin();
}

std::vector<sf::RectangleShape>::const_iterator bars::end(){
    return barGraph.end();
}

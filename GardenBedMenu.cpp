// this file is the garden bed menu file and includes the various necessary 


// include files
#include "GardenBedMenu.h"
#include "Day.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

// constructor
GardenBedMenu::GardenBedMenu(float width, float height){
    
    selectedItemIndex = 0;

    if(!font.loadFromFile("Assets/pacifico/Pacifico.ttf")){
        return;
    };

    gardenBedMenu[0].setFont(font);
    gardenBedMenu[0].setFillColor(sf::Color::Red);
    gardenBedMenu[0].setString("Plant Beetroot?");
    gardenBedMenu[0].setCharacterSize(30);
    gardenBedMenu[0].setPosition(sf::Vector2f(width/10, height/(MAX_BEDS + 1)*0.4));
    
    gardenBedMenu[1].setFont(font);
    gardenBedMenu[1].setFillColor(sf::Color::White);
    gardenBedMenu[1].setString("Plant Carrot?");
    gardenBedMenu[1].setCharacterSize(30);
    gardenBedMenu[1].setPosition(sf::Vector2f(width/10, height/(MAX_BEDS + 1)*1.4));
    
    gardenBedMenu[2].setFont(font);
    gardenBedMenu[2].setFillColor(sf::Color::White);
    gardenBedMenu[2].setString("Plant Radish?");
    gardenBedMenu[2].setCharacterSize(30);
    gardenBedMenu[2].setPosition(sf::Vector2f(width/10, height/(MAX_BEDS + 1)*2.4));

    gardenBedMenu[3].setFont(font);
    gardenBedMenu[3].setFillColor(sf::Color::White);
    gardenBedMenu[3].setString("Plant Rice?");
    gardenBedMenu[3].setCharacterSize(30);
    gardenBedMenu[3].setPosition(sf::Vector2f(width/10, height/(MAX_BEDS + 1)*3.4));

    gardenBedMenu[4].setFont(font);
    gardenBedMenu[4].setFillColor(sf::Color::White);
    gardenBedMenu[4].setString("Water Plants?");
    gardenBedMenu[4].setCharacterSize(30);
    gardenBedMenu[4].setPosition(sf::Vector2f(width/10, height/(MAX_BEDS + 1)*4.4));

    gardenBedMenu[5].setFont(font);
    gardenBedMenu[5].setFillColor(sf::Color::White);
    gardenBedMenu[5].setString("Harvest Crops?");
    gardenBedMenu[5].setCharacterSize(30);
    gardenBedMenu[5].setPosition(sf::Vector2f(width/10, height/(MAX_BEDS + 1)*5.4));
    
    gardenBedMenu[6].setFont(font);
    gardenBedMenu[6].setFillColor(sf::Color::White);
    gardenBedMenu[6].setString("Shovel?");
    gardenBedMenu[6].setCharacterSize(30);
    gardenBedMenu[6].setPosition(sf::Vector2f(width/10, height/(MAX_BEDS + 1)*6.4));



};

// returns the selected index when called
int GardenBedMenu::getPressedItem(){
    return selectedItemIndex;
};

// draws the menu onto a given window when called
void GardenBedMenu::draw(sf::RenderWindow &window){
    for (int i = 0; i < MAX_BEDS; i++){
        window.draw(gardenBedMenu[i]);
    };
};

// simulates moving up in options in the menu
void GardenBedMenu::MoveUp(){

    if(selectedItemIndex - 1 >= 0){
        gardenBedMenu[selectedItemIndex].setFillColor(sf::Color::White);
        
        selectedItemIndex = selectedItemIndex - 1;

        if(selectedItemIndex == -1){
            selectedItemIndex = 2;
        };

        gardenBedMenu[selectedItemIndex].setFillColor(sf::Color::Red);
    };

};

// simulates moving down in options in the menu
void GardenBedMenu::MoveDown(){

    if(selectedItemIndex + 1 <= 4){
        gardenBedMenu[selectedItemIndex].setFillColor(sf::Color::White);
        
        selectedItemIndex = selectedItemIndex + 1;

        if(selectedItemIndex == 5){
            selectedItemIndex = 0;
        };

        gardenBedMenu[selectedItemIndex].setFillColor(sf::Color::Red);
    };

};

// sets the pressed item to a certain given integer
void GardenBedMenu::setPressedItem(int num){
    gardenBedMenu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex = num;
    gardenBedMenu[selectedItemIndex].setFillColor(sf::Color::Red);

};


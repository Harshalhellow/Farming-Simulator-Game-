#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

Menu::Menu(float width, float height){
    
    selectedItemIndex = 0;

    if(!font.loadFromFile("Assets/pacifico/Pacifico.ttf")){
        return;
    };

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setCharacterSize(40);
    menu[0].setPosition(sf::Vector2f(width/8, height/(MAX_NUMBER_OF_ITEMS + 1)*0.4));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("About");
    menu[1].setCharacterSize(40);
    menu[1].setPosition(sf::Vector2f(width/9, height/(MAX_NUMBER_OF_ITEMS + 1)*1.4));
    
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(40);
    menu[2].setPosition(sf::Vector2f(width/8, height/(MAX_NUMBER_OF_ITEMS + 1)*2.4));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color::White);
    menu[3].setString("Store Menu");
    menu[3].setCharacterSize(40);
    menu[3].setPosition(sf::Vector2f(width/8, height/(MAX_NUMBER_OF_ITEMS + 1)*3.4));

    menu[4].setFont(font);
    menu[4].setFillColor(sf::Color::White);
    menu[4].setString("GardenBed Menu");
    menu[4].setCharacterSize(40);
    menu[4].setPosition(sf::Vector2f(width/8, height/(MAX_NUMBER_OF_ITEMS + 1)*4.4));

};

int Menu::getPressedItem(){
    return selectedItemIndex;
};

void Menu::draw(sf::RenderWindow &window){
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
        window.draw(menu[i]);
    };
};

void Menu::MoveUp(){

    if(selectedItemIndex - 1 >= 0){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        
        selectedItemIndex = selectedItemIndex - 1;

        if(selectedItemIndex == -1){
            selectedItemIndex = 2;
        };

        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    };

};

void Menu::MoveDown(){

    if(selectedItemIndex + 1 <= 4){
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        
        selectedItemIndex = selectedItemIndex + 1;

        if(selectedItemIndex == 5){
            selectedItemIndex = 0;
        };

        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    };

};

void Menu::setPressedItem(int num){
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex = num;
    menu[selectedItemIndex].setFillColor(sf::Color::Red);

};
#include "StoreWindow.h"
#include "Item.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

StoreWindow::StoreWindow(float width, float height){
    
    selectedItemIndex = 0;

    if(!font.loadFromFile("Assets/pacifico/Pacifico.ttf")){
        return;
    };

//shovel radish rice beetroot carrot win_game_item

    storeWindow[0].setFont(font);
    storeWindow[0].setFillColor(sf::Color::Red);
    storeWindow[0].setString("Buy Shovel");
    storeWindow[0].setCharacterSize(60);
    storeWindow[0].setPosition(sf::Vector2f(width/2.7, height/(MAX_NUMBER_OF_ITEMS_STORE_WINDOW + 1)*0.7));

    storeWindow[1].setFont(font);
    storeWindow[1].setFillColor(sf::Color::White);
    storeWindow[1].setString("Buy Radish");
    storeWindow[1].setCharacterSize(60);
    storeWindow[1].setPosition(sf::Vector2f(width/2.7, height/(MAX_NUMBER_OF_ITEMS_STORE_WINDOW + 1)*1.7));
    
    storeWindow[2].setFont(font);
    storeWindow[2].setFillColor(sf::Color::White);
    storeWindow[2].setString("Buy Rice");
    storeWindow[2].setCharacterSize(60);
    storeWindow[2].setPosition(sf::Vector2f(width/2.7, height/(MAX_NUMBER_OF_ITEMS_STORE_WINDOW + 1)*2.7));

    storeWindow[3].setFont(font);
    storeWindow[3].setFillColor(sf::Color::White);
    storeWindow[3].setString("Buy Carrot");
    storeWindow[3].setCharacterSize(60);
    storeWindow[3].setPosition(sf::Vector2f(width/2.7, height/(MAX_NUMBER_OF_ITEMS_STORE_WINDOW + 1)*3.7));

    storeWindow[4].setFont(font);
    storeWindow[4].setFillColor(sf::Color::White);
    storeWindow[4].setString("Buy Beetroot");
    storeWindow[4].setCharacterSize(60);
    storeWindow[4].setPosition(sf::Vector2f(width/2.7, height/(MAX_NUMBER_OF_ITEMS_STORE_WINDOW + 1)*4.7));
    
    storeWindow[5].setFont(font);
    storeWindow[5].setFillColor(sf::Color::White);
    storeWindow[5].setString("Buy Win Game Item");
    storeWindow[5].setCharacterSize(60);
    storeWindow[5].setPosition(sf::Vector2f(width/2.7, height/(MAX_NUMBER_OF_ITEMS_STORE_WINDOW + 1)*5.7));

};

int StoreWindow::getPressedItem(){
    return selectedItemIndex;
};

void StoreWindow::draw(sf::RenderWindow &window){
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS_STORE_WINDOW; i++){
        window.draw(storeWindow[i]);
    };
};

void StoreWindow::MoveUp(){

    if(selectedItemIndex - 1 >= 0){
        storeWindow[selectedItemIndex].setFillColor(sf::Color::White);
        
        selectedItemIndex = selectedItemIndex - 1;

        if(selectedItemIndex == -1){
            selectedItemIndex = 2;
        };

        storeWindow[selectedItemIndex].setFillColor(sf::Color::Red);
    };

};

void StoreWindow::MoveDown(){

    if(selectedItemIndex + 1 <= 2){
        storeWindow[selectedItemIndex].setFillColor(sf::Color::White);
        
        selectedItemIndex = selectedItemIndex + 1;

        if(selectedItemIndex == 3){
            selectedItemIndex = 0;
        };

        storeWindow[selectedItemIndex].setFillColor(sf::Color::Red);
    };

};
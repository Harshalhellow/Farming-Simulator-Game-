#include "StoreMenu.h"
#include "Day.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

StoreMenu::StoreMenu(float width, float height, User &user, Day &givenDay){
    
    selectedItemIndex = 0;

    if(!font.loadFromFile("Assets/pacifico/Pacifico.ttf")){
        return;
    };

    // buy beetroot
    storeMenu[0].setFont(font);
    storeMenu[0].setFillColor(sf::Color::Red);
    storeMenu[0].setString("Buy Beetroot for 5 (Harvest 50)");
    storeMenu[0].setCharacterSize(30);
    storeMenu[0].setPosition(sf::Vector2f(width/10, height/(MAX_PRODUCTS + 1)*0.4));
    
    // buy carrot
    storeMenu[1].setFont(font);
    storeMenu[1].setFillColor(sf::Color::White);
    storeMenu[1].setString("Buy Carrot for 7 (Harvest 70)");
    storeMenu[1].setCharacterSize(30);
    storeMenu[1].setPosition(sf::Vector2f(width/10, height/(MAX_PRODUCTS + 1)*1.4));
    
    // buy radish
    storeMenu[2].setFont(font);
    storeMenu[2].setFillColor(sf::Color::White);
    storeMenu[2].setString("Buy Radish for 9 (Harvest 90)");
    storeMenu[2].setCharacterSize(30);
    storeMenu[2].setPosition(sf::Vector2f(width/10, height/(MAX_PRODUCTS + 1)*2.4));
    
    // buy rice
    storeMenu[3].setFont(font);
    storeMenu[3].setFillColor(sf::Color::White);
    storeMenu[3].setString("Buy Rice for 10 (Harvest 10)");
    storeMenu[3].setCharacterSize(30);
    storeMenu[3].setPosition(sf::Vector2f(width/10, height/(MAX_PRODUCTS + 1)*3.4));
    
    // buy game trophy
    storeMenu[4].setFont(font);
    storeMenu[4].setFillColor(sf::Color::White);
    storeMenu[4].setString("Buy Winning Game Trophy");
    storeMenu[4].setCharacterSize(30);
    storeMenu[4].setPosition(sf::Vector2f(width/10, height/(MAX_PRODUCTS + 1)*4.4));

    // display current money string
    storeMenu[5].setFont(font);
    storeMenu[5].setFillColor(sf::Color::White);
    storeMenu[5].setString("Current money is at: ");
    storeMenu[5].setCharacterSize(30);
    storeMenu[5].setPosition(sf::Vector2f(width/10, height/(MAX_PRODUCTS + 1)*5.4));

    int usersMoneyINT = user.GetMoney();
    char userMoneySTR[6];
    std::sprintf(userMoneySTR, "%d", usersMoneyINT); 

    // display current money
    storeMenu[6].setFont(font);
    storeMenu[6].setFillColor(sf::Color::White);
    storeMenu[6].setString(userMoneySTR);
    storeMenu[6].setCharacterSize(30);
    storeMenu[6].setPosition(sf::Vector2f(width/0.5, height/(MAX_PRODUCTS + 1)*5.4));

    // display current time string
    storeMenu[7].setFont(font);
    storeMenu[7].setFillColor(sf::Color::White);
    storeMenu[7].setString("Current day time is at: ");
    storeMenu[7].setCharacterSize(30);
    storeMenu[7].setPosition(sf::Vector2f(width/10, height/(MAX_PRODUCTS + 1)*6.4));

    int dayTime = givenDay.GetCurrentDay();    
    char userDayTime[6];
    std::sprintf(userDayTime, "%d", dayTime); 

    // display current time
    storeMenu[8].setFont(font);
    storeMenu[8].setFillColor(sf::Color::White);
    storeMenu[8].setString(userDayTime);
    storeMenu[8].setCharacterSize(30);
    storeMenu[8].setPosition(sf::Vector2f(width/0.5, height/(MAX_PRODUCTS + 1)*6.4));

};

int StoreMenu::getPressedItem(){
    return selectedItemIndex;
};

void StoreMenu::draw(sf::RenderWindow &window){
    for (int i = 0; i < MAX_PRODUCTS; i++){
        window.draw(storeMenu[i]);
    };
};

void StoreMenu::MoveUp(){

    if(selectedItemIndex - 1 >= 0){
        storeMenu[selectedItemIndex].setFillColor(sf::Color::White);
        
        selectedItemIndex = selectedItemIndex - 1;

        if(selectedItemIndex == -1){
            selectedItemIndex = 2;
        };

        storeMenu[selectedItemIndex].setFillColor(sf::Color::Red);
    };

};

void StoreMenu::MoveDown(){

    if(selectedItemIndex + 1 <= 4){
        storeMenu[selectedItemIndex].setFillColor(sf::Color::White);
        
        selectedItemIndex = selectedItemIndex + 1;

        if(selectedItemIndex == 5){
            selectedItemIndex = 0;
        };

        storeMenu[selectedItemIndex].setFillColor(sf::Color::Red);
    };

};

void StoreMenu::setPressedItem(int num){
    storeMenu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex = num;
    storeMenu[selectedItemIndex].setFillColor(sf::Color::Red);

};
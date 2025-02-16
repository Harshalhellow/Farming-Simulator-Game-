#ifndef MENU
#define MENU
#define MAX_NUMBER_OF_ITEMS 5
#include "SFML/Graphics.hpp"
#include <iostream>

class Menu{

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
    
    public:
        Menu();
        Menu(float width, float height);
        
        int getPressedItem();
        void setPressedItem(int num);
        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
};

#endif
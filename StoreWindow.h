#ifndef STOREWINDOW
#define STOREWINDOW
#define MAX_NUMBER_OF_ITEMS_STORE_WINDOW 6
#include "SFML/Graphics.hpp"
#include <iostream>

class StoreWindow{

    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text storeWindow[MAX_NUMBER_OF_ITEMS_STORE_WINDOW]; 
    
    public:
        //StoreWindow();
        StoreWindow(float width, float height);
        
        int getPressedItem();
        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
};

#endif 
#include "SFML/Graphics.hpp"
#include "User.h"
#include "Day.h"

#ifndef STOREMENU
#define STOREMENU
#define MAX_PRODUCTS 8

class StoreMenu{
    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text storeMenu[MAX_PRODUCTS];
        
    public:
        StoreMenu();
        StoreMenu(float width, float height, User &user, Day &givenDay);
        
        int getPressedItem();
        void setPressedItem(int num);
        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
};

#endif
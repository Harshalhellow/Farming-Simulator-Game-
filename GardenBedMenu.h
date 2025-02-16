#include "SFML/Graphics.hpp"
#include "User.h"
#include "Day.h"

#ifndef GARDENBEDMENU
#define GARDENBEDMENU
#define MAX_BEDS 7

class GardenBedMenu{
    private:
        int selectedItemIndex;
        sf::Font font;
        sf::Text gardenBedMenu[MAX_BEDS];
        
    public:
    
        GardenBedMenu();
        GardenBedMenu(float width, float height);
        
        int getPressedItem();
        void setPressedItem(int num);
        void draw(sf::RenderWindow &window);
        void MoveUp();
        void MoveDown();
};

#endif
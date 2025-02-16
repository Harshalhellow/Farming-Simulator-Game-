#ifndef GAMETILE
#define GAMETILE
#include <SFML/Graphics.hpp>

class GameTile{

    private:
    
    public:
        // to deal with if its moveable or not(i.e., garden beds cannot be walked over but grass can).
        bool isPassable;
        
        // set the position of the tile
        sf::Vector2f pos;

        // sprite and texture
        sf::Texture texture;
        sf::Sprite sprite;

        //create gametile constructor
        GameTile(std::string, float, float, bool);
        
        //honestly idk
        bool setUpSprite(std::string);
};

#endif
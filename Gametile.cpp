#include "Gametile.h"
#include <SFML/Graphics.hpp>
#include <iostream>  
    
    GameTile::GameTile(std::string textureName, float x, float y, bool passable){
        
        //sets up sprite
        if(!setUpSprite(textureName)){
            return;
        };
        
        // sets position of sprite
        pos = sf::Vector2f(x, y);
        sprite.setPosition(pos);
        
        // idk
        isPassable = passable;
    };
/*
    bool GameTile::setUpSprite(std::string textureName){
        if(!texture.loadFromFile("Assets//Finished Files//Grass_Block.png")){
        std::cout << "Could not load grass texture." << std::endl;
        return 0;

        sf::Sprite grassSprite;
        grassSprite.setTexture(texture);
    };
*/

    //takes in the name, loads the sprite, and sets onto the sprite
    bool GameTile::setUpSprite(std::string textureName){
        if(!texture.loadFromFile(textureName)){
            return false;
        };
        
        //makes it so that the edges of the sprite are not blurry
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0,0,50,50));

        return true;
    };


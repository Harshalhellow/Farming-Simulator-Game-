#ifndef GAMEWORLD
#define GAMEWORLD

#include <SFML/Graphics.hpp>
#include "Gametile.h"
#include "WaterHole.h"
#include "GardenBed.h"
#include <vector>

class GameWorld{

    private:
        // position of player, store and row of garden beds
        // sf::Vector2i playerPos;
        sf::Vector2i storePos;
        std::vector<sf::Vector2i> gardenBedPositions; 

    public:
        // array of tiles
        std::vector< std::vector<GameTile*>> tiles;
        int gridLength;
        
        //pointer to a player sprite
        sf::Sprite *Player;

        // constructor
        GameWorld();
        
        // setting values of attributes
        void setUpStorePos();
        void setUpGardenBedPositions();
        void setUpTiles();
        void checkCollision(sf::Sprite &Player, WaterHole &Waterhole, GardenBed &givenGarden);
};

#endif
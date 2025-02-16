#include "Gameworld.h"
#include "WaterHole.h"
#include "User.h"
#include "Shovel.h"

#include <SFML/Graphics.hpp>
#include <iostream>

// constructor
GameWorld::GameWorld(){
    gridLength = 8;
};

// intialise the bed positions
void GameWorld::setUpGardenBedPositions(){
    gardenBedPositions.clear();
    gardenBedPositions.push_back(sf::Vector2i(6,3));
    gardenBedPositions.push_back(sf::Vector2i(6,4));
    gardenBedPositions.push_back(sf::Vector2i(6,5));
    gardenBedPositions.push_back(sf::Vector2i(6,6));
    gardenBedPositions.push_back(sf::Vector2i(6,7));
    gardenBedPositions.push_back(sf::Vector2i(7,3));
    gardenBedPositions.push_back(sf::Vector2i(7,4));
    gardenBedPositions.push_back(sf::Vector2i(7,5));
    gardenBedPositions.push_back(sf::Vector2i(7,6));
    gardenBedPositions.push_back(sf::Vector2i(7,7));
}; 

// intialise the store positions
void GameWorld::setUpStorePos(){
    storePos = sf::Vector2i(gridLength-5, gridLength-3);
};

void GameWorld::checkCollision(sf::Sprite &Player, WaterHole &Waterhole, GardenBed &givenGarden){
    int playerXPosition = Player.getPosition().x;
    int playerYPosition = Player.getPosition().y;

    // water hole collision WORKS!~
    if((playerXPosition > 0 && playerXPosition < 50) && (playerYPosition > 0 && playerYPosition < 50)){
        Waterhole.GiveUserWater();
        Player.setPosition(playerXPosition + 1, playerYPosition + 1);
    }

    // tree collision 
    else if(((playerXPosition > 50 && playerXPosition < 100) && (playerYPosition > 100 && playerYPosition < 150)) || ((playerXPosition > 150 && playerXPosition < 200) && (playerYPosition > 150 && playerYPosition < 200))){
        std::cout << "You hit the tree" << std::endl;
    }
    
    // garden bed collision
    
    // garden bed 0
    else if((playerXPosition > 100 && playerXPosition < 150) && (playerYPosition > 250 && playerYPosition < 300)){

    }

    // garden bed 1
    else if((playerXPosition > 150 && playerXPosition < 200) && (playerYPosition > 250 && playerYPosition < 300)){

    }   

    // garden bed 2
    else if((playerXPosition > 200 && playerXPosition < 250) && (playerYPosition > 250 && playerYPosition < 300)){

    }
    
    // garden bed 3
    else if((playerXPosition > 250 && playerXPosition < 300) && (playerYPosition > 250 && playerYPosition < 300)){

    }

    // garden bed 4
    else if((playerXPosition > 300 && playerXPosition < 350) && (playerYPosition > 250 && playerYPosition < 300)){

    }

    // garden bed 5
    else if((playerXPosition > 100 && playerXPosition < 150) && (playerYPosition > 300 && playerYPosition < 350)){

    }

    // garden bed 6
    else if((playerXPosition > 150 && playerXPosition < 200) && (playerYPosition > 300 && playerYPosition < 350)){

    }

    // garden bed 7
    else if((playerXPosition > 200 && playerXPosition < 250) && (playerYPosition > 300 && playerYPosition < 350)){

    }

    // garden bed 8
    else if((playerXPosition > 250 && playerXPosition < 300) && (playerYPosition > 300 && playerYPosition < 350)){

    }

    // garden bed 9
    else if((playerXPosition > 300 && playerXPosition < 350) && (playerYPosition > 300 && playerYPosition < 350)){
    };

};

void GameWorld::setUpTiles(){
    tiles.clear();

    // row 1
    std::vector<GameTile*> firstRow;
    firstRow.push_back(new GameTile("Assets/FinishedFiles/Water_Well.png", 0, 0, false));
    firstRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 50, 0, true));
    firstRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 100, 0, true));
    firstRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 150, 0, true));
    firstRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 200, 0, true));
    firstRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 250, 0, true));
    firstRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 300, 0, true));
    firstRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 350, 0, true));
    tiles.push_back(firstRow);

    // row 2
    std::vector<GameTile*> secondRow;
    secondRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 0, 50, true));
    secondRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 50, 50, true));
    secondRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 100, 50, true));
    secondRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 150, 50, true));
    secondRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 200, 50, true));
    secondRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 250, 50, true));
    secondRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 300, 50, true));
    secondRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 350, 50, true));
    tiles.push_back(secondRow);

    // row 3
    std::vector<GameTile*> thirdRow;
    thirdRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 0, 100, true));
    thirdRow.push_back(new GameTile("Assets/FinishedFiles/Tree.png", 50, 100, true));
    thirdRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 100, 100, true));
    thirdRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 150, 100, true));
    thirdRow.push_back(new GameTile("Assets/FinishedFiles/Old_Man.png", 200, 100, false));
    thirdRow.push_back(new GameTile("Assets/FinishedFiles/Store.png", 250, 100, false));
    thirdRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 300, 100, true));
    thirdRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 350, 100, true));
    tiles.push_back(thirdRow);

    // row 4
    std::vector<GameTile*> fourthRow;
    fourthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 0, 150, true));
    fourthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 50, 150, true));
    fourthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 100, 150, true));
    fourthRow.push_back(new GameTile("Assets/FinishedFiles/Tree.png", 150, 150, true));
    fourthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 200, 150, true));
    fourthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 250, 150, true));
    fourthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 300, 150, true));
    fourthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 350, 150, true));
    tiles.push_back(fourthRow);

    // row 5
    std::vector<GameTile*> fifthRow;
    fifthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 0, 200, true));
    fifthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 50, 200, true));
    fifthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 100, 200, true));
    fifthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 150, 200, true));
    fifthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 200, 200, true));
    fifthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 250, 200, true));
    fifthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 300, 200, true));
    fifthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 350, 200, true));
    tiles.push_back(fifthRow);

    // row 6
    std::vector<GameTile*> sixthRow;
    sixthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 0, 250, true));
    sixthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 50, 250, true));
    sixthRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 100, 250, true));
    sixthRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 150, 250, true));
    sixthRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 200, 250, true));
    sixthRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 250, 250, true));
    sixthRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 300, 250, true));
    sixthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 350, 250, true));
    tiles.push_back(sixthRow);

    // row 7
    std::vector<GameTile*> seventhRow;
    seventhRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 0, 300, true));
    seventhRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 50, 300, true));
    seventhRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 100, 300, true));
    seventhRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 150, 300, true));
    seventhRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 200, 300, true));
    seventhRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 250, 300, true));
    seventhRow.push_back(new GameTile("Assets/FinishedFiles/Blank_Garden_Bed.png", 300, 300, true));
    seventhRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 350, 300, true));
    tiles.push_back(seventhRow);
    
    // row 8
    std::vector<GameTile*> eighthRow;
    eighthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 0, 350, true));
    eighthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 50, 350, true));
    eighthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 100, 350, true));
    eighthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 150, 350, true));
    eighthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 200, 350, true));
    eighthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 250, 350, true));
    eighthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 300, 350, true));
    eighthRow.push_back(new GameTile("Assets/FinishedFiles/Grass_Block.png", 350, 350, true));
    tiles.push_back(eighthRow);
};
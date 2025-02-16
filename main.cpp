// main.cpp
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <climits>      // For INT_MAX
#include <algorithm>    // For std::min, std::min_element
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>
#include <set>
#include <string>

// Include your class headers (adjust paths as needed)
#include "User.h"
#include "Day.h"
#include "WaterHole.h"
#include "Shovel.h"
#include "Seed.h"
#include "Crop.h"
#include "Win.h"

// ----------------------------------------------------------------------
// Define popup states.
enum class PopupState {
    None,
    Waterhole,
    Shop,
    ShopSeedSelection,  // Submenu for selecting which seed type to buy in the shop.
    Gardenbed,
    GardenbedSlotMenu,
    GameOver
};

// A simple structure to represent a garden slot.
struct GardenSlot {
    bool shoveled;
    Crop* crop;
    GardenSlot() : shoveled(false), crop(nullptr) {}
};

const int NUM_GARDEN_SLOTS = 9;

// Global pointer for the Day object (used by Crop for harvest timing)
Day* currentDayCounter = nullptr;

int main()
{
    // ------------------------ Setup Window ------------------------
    sf::RenderWindow window(sf::VideoMode(800, 600), "Farming Game");
    window.setFramerateLimit(60);

    // ------------------------ Load Textures and Scale ------------------------
    // Background: scale to fill the window.
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/background.png"))
    {
        std::cerr << "Error: Could not load assets/background.png" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Vector2u bgSize = backgroundTexture.getSize();
    sf::Vector2u winSize = window.getSize();
    backgroundSprite.setScale(
        static_cast<float>(winSize.x) / bgSize.x,
        static_cast<float>(winSize.y) / bgSize.y);

    // Player sprite: desired size (e.g., 60x80 pixels).
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/player.png"))
    {
        std::cerr << "Error: Could not load assets/player.png" << std::endl;
        return -1;
    }
    sf::Sprite playerSprite(playerTexture);
    sf::Vector2u playerTexSize = playerTexture.getSize();
    float desiredPlayerWidth = 60.f, desiredPlayerHeight = 80.f;
    playerSprite.setScale(desiredPlayerWidth / playerTexSize.x, desiredPlayerHeight / playerTexSize.y);
    playerSprite.setPosition(100, 100);

    // Shop sprite: desired size (150x150).
    sf::Texture shopTexture;
    if (!shopTexture.loadFromFile("assets/shop.png"))
    {
        std::cerr << "Error: Could not load assets/shop.png" << std::endl;
        return -1;
    }
    sf::Sprite shopSprite(shopTexture);
    sf::Vector2u shopTexSize = shopTexture.getSize();
    float desiredShopWidth = 150.f, desiredShopHeight = 150.f;
    shopSprite.setScale(desiredShopWidth / shopTexSize.x, desiredShopHeight / shopTexSize.y);
    shopSprite.setPosition(50, 400);

    // Waterhole sprite: desired size (150x150).
    sf::Texture waterholeTexture;
    if (!waterholeTexture.loadFromFile("assets/waterhole.png"))
    {
        std::cerr << "Error: Could not load assets/waterhole.png" << std::endl;
        return -1;
    }
    sf::Sprite waterholeSprite(waterholeTexture);
    sf::Vector2u waterholeTexSize = waterholeTexture.getSize();
    float desiredWaterholeWidth = 150.f, desiredWaterholeHeight = 150.f;
    waterholeSprite.setScale(desiredWaterholeWidth / waterholeTexSize.x, desiredWaterholeHeight / waterholeTexSize.y);
    waterholeSprite.setPosition(600, 50);

    // Gardenbed sprite: desired size (250x150).
    sf::Texture gardenTexture;
    if (!gardenTexture.loadFromFile("assets/gardenbed.png"))
    {
        std::cerr << "Error: Could not load assets/gardenbed.png" << std::endl;
        return -1;
    }
    sf::Sprite gardenSprite(gardenTexture);
    sf::Vector2u gardenTexSize = gardenTexture.getSize();
    float desiredGardenWidth = 250.f, desiredGardenHeight = 150.f;
    gardenSprite.setScale(desiredGardenWidth / gardenTexSize.x, desiredGardenHeight / gardenTexSize.y);
    gardenSprite.setPosition(550, 400);

    // ------------------------ Load Font ------------------------
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cerr << "Error: Could not load assets/arial.ttf" << std::endl;
        return -1;
    }
    sf::Text uiText;
    uiText.setFont(font);
    uiText.setCharacterSize(16);
    uiText.setFillColor(sf::Color::White);
    uiText.setPosition(10, 10);

    // ------------------------ Create Game Objects ------------------------
    User user;
    user.SetMoney(100);  // Starting money

    Day day;
    currentDayCounter = &day;  // Global pointer

    WaterHole waterHole(&user);
    Shovel shovel(&user, nullptr); // The shovel's effect will be applied per garden slot.

    // Create available seed types once at game start.
    // (We create 9 seed types.)
    std::vector<Seed> availableSeeds;
    for (int i = 1; i <= 9; i++)
    {
        // For demonstration, each seed is named "SeedX". You can adjust reward, cost, and harvest time.
        availableSeeds.push_back(Seed(&user, "Seed" + std::to_string(i), 10 + i * 2, 5 + i, 200 + (i % 3)));
    }

    Win winItem(&user);

    // The player's generic seed inventory: each element is an index into availableSeeds.
    std::vector<int> seedInventory;

    // Create an array of 9 garden slots.
    GardenSlot gardenSlots[NUM_GARDEN_SLOTS];

    // ------------------------ Game State Variables ------------------------
    PopupState popupState = PopupState::None;
    int selectedSlotIndex = -1;   // Used in GardenbedSlotMenu.
    int seedOptionPage = 0;       // For pagination in the Gardenbed planting submenu.
    int shopSeedOptionPage = 0;   // For pagination in the Shop seed selection submenu.
    bool gameWon = false;

    // ------------------------ Movement Variables ------------------------
    float playerSpeed = 150.f; // Pixels per second.
    sf::Clock deltaClock;

    // ------------------------ Main Game Loop ------------------------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Allow closing the window.
            if (event.type == sf::Event::Closed)
                window.close();

            // --- Process events when a popup is active ---
            if (popupState != PopupState::None)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    switch (popupState)
                    {
                        // --- Waterhole Popup ---
                        case PopupState::Waterhole:
                            if (event.key.code == sf::Keyboard::C)
                            {
                                waterHole.GiveUserWater();
                                popupState = PopupState::None;
                            }
                            else if (event.key.code == sf::Keyboard::Escape)
                                popupState = PopupState::None;
                            break;

                        // --- Shop Popup ---
                        case PopupState::Shop:
                            // Options: 1: Buy Shovel, 2: Buy Seeds (open seed selection), 3: Buy Win.
                            if (event.key.code == sf::Keyboard::Num1)
                            {
                                shovel.BuyThisItem();
                                popupState = PopupState::None;
                            }
                            else if (event.key.code == sf::Keyboard::Num2)
                            {
                                shopSeedOptionPage = 0;  // Reset page.
                                popupState = PopupState::ShopSeedSelection;
                            }
                            else if (event.key.code == sf::Keyboard::Num3)
                            {
                                winItem.BuyThisItem();
                                if (winItem.GetIsBought())
                                    gameWon = true;
                                popupState = PopupState::None;
                            }
                            else if (event.key.code == sf::Keyboard::Escape)
                                popupState = PopupState::None;
                            break;

                        // --- Shop Seed Selection Popup ---
                        case PopupState::ShopSeedSelection:
                        {
                            int optionsPerPage = 5;
                            int totalOptions = availableSeeds.size();
                            int startIndex = shopSeedOptionPage * optionsPerPage;
                            int endIndex = std::min(startIndex + optionsPerPage, totalOptions);
                            // If key 0 is pressed and there are more options, cycle pages.
                            if (event.key.code == sf::Keyboard::Num0 && endIndex < totalOptions)
                            {
                                int maxPages = (totalOptions + optionsPerPage - 1) / optionsPerPage;
                                shopSeedOptionPage = (shopSeedOptionPage + 1) % maxPages;
                                break;
                            }
                            if (event.key.code >= sf::Keyboard::Num1 &&
                                event.key.code < sf::Keyboard::Num1 + (endIndex - startIndex))
                            {
                                int option = event.key.code - sf::Keyboard::Num1;
                                int seedIndex = startIndex + option;
                                if (seedIndex < totalOptions)
                                {
                                    if (user.GetMoney() >= availableSeeds[seedIndex].GetCostOfItem())
                                    {
                                        user.SetMoney(user.GetMoney() - availableSeeds[seedIndex].GetCostOfItem());
                                        seedInventory.push_back(seedIndex);
                                    }
                                    else
                                        std::cout << "Not enough money to buy " 
                                                  << availableSeeds[seedIndex].GetNameOfItem() << std::endl;
                                }
                                popupState = PopupState::Shop;
                            }
                            else if (event.key.code == sf::Keyboard::Escape)
                                popupState = PopupState::Shop;
                        }
                        break;

                        // --- Gardenbed Popup ---
                        case PopupState::Gardenbed:
                            // Press keys 1-9 to select a garden slot.
                            if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9)
                            {
                                int index = event.key.code - sf::Keyboard::Num1;
                                if (index < NUM_GARDEN_SLOTS)
                                {
                                    selectedSlotIndex = index;
                                    seedOptionPage = 0;  // Reset page for gardenbed planting.
                                    popupState = PopupState::GardenbedSlotMenu;
                                }
                            }
                            else if (event.key.code == sf::Keyboard::Escape)
                                popupState = PopupState::None;
                            break;

                        // --- Gardenbed Slot Submenu ---
                        case PopupState::GardenbedSlotMenu:
                        {
                            GardenSlot &slot = gardenSlots[selectedSlotIndex];
                            // If the slot is NOT shoveled: show a simple popup ("Press S to Shovel").
                            if (!slot.shoveled)
                            {
                                if (event.key.code == sf::Keyboard::S)
                                {
                                    if (shovel.GetIsBought())
                                        slot.shoveled = true;
                                    else
                                        std::cout << "You need to buy a shovel first." << std::endl;
                                    popupState = PopupState::Gardenbed;
                                }
                                else if (event.key.code == sf::Keyboard::Escape)
                                    popupState = PopupState::Gardenbed;
                            }
                            // If the slot is shoveled and empty: display the seed selection submenu.
                            else if (slot.shoveled && slot.crop == nullptr)
                            {
                                // Build a list of distinct seed types from seedInventory.
                                std::set<int> distinct;
                                for (int s : seedInventory)
                                    distinct.insert(s);
                                std::vector<int> distinctSeeds(distinct.begin(), distinct.end());
                                int totalOptions = distinctSeeds.size();
                                int optionsPerPage = 5;
                                int startIndex = seedOptionPage * optionsPerPage;
                                int endIndex = std::min(startIndex + optionsPerPage, totalOptions);
                                // If key 0 is pressed and there are more options, cycle pages.
                                if (event.key.code == sf::Keyboard::Num0 && endIndex < totalOptions)
                                {
                                    int maxPages = (totalOptions + optionsPerPage - 1) / optionsPerPage;
                                    seedOptionPage = (seedOptionPage + 1) % maxPages;
                                    break;
                                }
                                if (event.key.code >= sf::Keyboard::Num1 &&
                                    event.key.code < sf::Keyboard::Num1 + (endIndex - startIndex))
                                {
                                    int option = event.key.code - sf::Keyboard::Num1;
                                    int seedType = distinctSeeds[startIndex + option];
                                    // Remove one occurrence of this seed from inventory.
                                    auto it = std::find(seedInventory.begin(), seedInventory.end(), seedType);
                                    if (it != seedInventory.end())
                                        seedInventory.erase(it);
                                    // Create a new crop using the chosen seed type.
                                    Crop* newCrop = new Crop(&user,
                                        availableSeeds[seedType].GetNameOfItem() + std::string(" Crop"),
                                        availableSeeds[seedType].GetRewardForHarvesting(),
                                        availableSeeds[seedType].GetCostOfItem(),
                                        5, // Water required (constant)
                                        availableSeeds[seedType].GetTImeForHarvesting());
                                    newCrop->SetPlantedDay(day.GetCurrentDay());
                                    newCrop->SetIsBought(true);
                                    slot.crop = newCrop;
                                    popupState = PopupState::Gardenbed;
                                }
                                else if (event.key.code == sf::Keyboard::Escape)
                                    popupState = PopupState::Gardenbed;
                            }
                            // If the slot has a crop: allow watering (W) or harvesting (H).
                            else if (slot.shoveled && slot.crop != nullptr)
                            {
                                if (event.key.code == sf::Keyboard::W)
                                {
                                    slot.crop->Water();
                                    popupState = PopupState::Gardenbed;
                                }
                                else if (event.key.code == sf::Keyboard::H)
                                {
                                    slot.crop->CropFinishedGrowing();
                                    delete slot.crop;
                                    slot.crop = nullptr;
                                    popupState = PopupState::Gardenbed;
                                }
                                else if (event.key.code == sf::Keyboard::Escape)
                                    popupState = PopupState::Gardenbed;
                            }
                            if (event.key.code == sf::Keyboard::Escape)
                                popupState = PopupState::Gardenbed;
                        }
                        break;

                        // --- Game Over Popup ---
                        case PopupState::GameOver:
                            if (event.key.code == sf::Keyboard::Enter)
                            {
                                // Reset game: reset money, clear seed inventory, reset all garden slots, reset the shovel.
                                user.SetMoney(100);
                                seedInventory.clear();
                                for (int i = 0; i < NUM_GARDEN_SLOTS; i++)
                                {
                                    if (gardenSlots[i].crop != nullptr)
                                    {
                                        delete gardenSlots[i].crop;
                                        gardenSlots[i].crop = nullptr;
                                    }
                                    gardenSlots[i].shoveled = false;
                                }
                                shovel.SetIsBought(false);
                                gameWon = false;
                                popupState = PopupState::None;
                            }
                            else if (event.key.code == sf::Keyboard::Escape)
                                window.close();
                            break;

                        default:
                            break;
                    } // end switch popupState
                } // end if key pressed (popup)
            }
            // --- Process events when no popup is active ---
            else
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    // When no popup is active, pressing Enter (while inside a zone) opens the corresponding popup.
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
                        if (playerBounds.intersects(waterholeSprite.getGlobalBounds()))
                            popupState = PopupState::Waterhole;
                        else if (playerBounds.intersects(shopSprite.getGlobalBounds()))
                            popupState = PopupState::Shop;
                        else if (playerBounds.intersects(gardenSprite.getGlobalBounds()))
                            popupState = PopupState::Gardenbed;
                        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Debounce.
                    }
                }
            }
        } // end event polling

        // --- Normal movement when no popup is active ---
        if (popupState == PopupState::None)
        {
            float dt = deltaClock.restart().asSeconds();
            sf::Vector2f movement(0.f, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                movement.y -= playerSpeed * dt;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                movement.y += playerSpeed * dt;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                movement.x -= playerSpeed * dt;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                movement.x += playerSpeed * dt;
            playerSprite.move(movement);
        }

        // ------------------------ Check Game Over Condition ------------------------
        int minSeedCost = INT_MAX;
        for (const auto& s : availableSeeds)
            minSeedCost = std::min(minSeedCost, s.GetCostOfItem());
        if (popupState == PopupState::None && user.GetMoney() < minSeedCost && seedInventory.empty())
            popupState = PopupState::GameOver;

        // ------------------------ Rendering ------------------------
        window.clear();
        window.draw(backgroundSprite);
        window.draw(shopSprite);
        window.draw(waterholeSprite);
        window.draw(gardenSprite);
        window.draw(playerSprite);

        // Draw UI stats.
        std::stringstream statsStream;
        statsStream << "Money: $" << user.GetMoney() << "\n"
                    << "Water: " << user.GetWaterStorage() << "\n"
                    << "Total Seeds: " << seedInventory.size() << "\n"
                    << "Day: " << day.GetCurrentDay() << "\n";
        uiText.setString(statsStream.str());
        window.draw(uiText);

        // Draw popup overlays if active.
        if (popupState != PopupState::None)
        {
            sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));
            window.draw(overlay);

            if (popupState == PopupState::Waterhole)
            {
                sf::RectangleShape menuBox(sf::Vector2f(250, 150));
                menuBox.setFillColor(sf::Color(200,200,200));
                menuBox.setPosition(275,225);
                window.draw(menuBox);
                sf::Text menuText("Waterhole Menu", font, 20);
                menuText.setFillColor(sf::Color::Black);
                menuText.setPosition(300,240);
                window.draw(menuText);
                sf::Text instruct("Press C to Collect Water", font, 18);
                instruct.setFillColor(sf::Color::Black);
                instruct.setPosition(290,300);
                window.draw(instruct);
            }
            else if (popupState == PopupState::Shop)
            {
                sf::RectangleShape menuBox(sf::Vector2f(300,250));
                menuBox.setFillColor(sf::Color(200,200,200));
                menuBox.setPosition(250,175);
                window.draw(menuBox);
                sf::Text menuText("Shop Menu", font, 20);
                menuText.setFillColor(sf::Color::Black);
                menuText.setPosition(320,190);
                window.draw(menuText);
                sf::Text opt1("1: Buy Shovel", font, 18);
                opt1.setFillColor(sf::Color::Black);
                opt1.setPosition(300,240);
                window.draw(opt1);
                sf::Text opt2("2: Buy Seeds", font, 18);
                opt2.setFillColor(sf::Color::Black);
                opt2.setPosition(300,280);
                window.draw(opt2);
                sf::Text opt3("3: Buy Win", font, 18);
                opt3.setFillColor(sf::Color::Black);
                opt3.setPosition(300,320);
                window.draw(opt3);
            }
            else if (popupState == PopupState::ShopSeedSelection)
            {
                int optionsPerPage = 5;
                int totalOptions = availableSeeds.size();
                int startIndex = shopSeedOptionPage * optionsPerPage;
                int endIndex = std::min(startIndex + optionsPerPage, totalOptions);
                sf::RectangleShape menuBox(sf::Vector2f(300, 300));
                menuBox.setFillColor(sf::Color(200,200,200));
                menuBox.setPosition(250,150);
                window.draw(menuBox);
                sf::Text menuText("Seed Shop", font, 20);
                menuText.setFillColor(sf::Color::Black);
                menuText.setPosition(320,170);
                window.draw(menuText);
                for (int i = startIndex; i < endIndex; i++)
                {
                    int optionNumber = i - startIndex + 1;
                    sf::Text seedText(std::to_string(optionNumber) + ": " + availableSeeds[i].GetNameOfItem() +
                        " ($" + std::to_string(availableSeeds[i].GetCostOfItem()) + ")",
                        font, 18);
                    seedText.setFillColor(sf::Color::Black);
                    seedText.setPosition(300, 220 + (i - startIndex) * 30);
                    window.draw(seedText);
                }
                if (endIndex < totalOptions)
                {
                    sf::Text instruct("0: Next Page", font, 16);
                    instruct.setFillColor(sf::Color::Black);
                    instruct.setPosition(300, 220 + (endIndex - startIndex) * 30);
                    window.draw(instruct);
                }
                else
                {
                    sf::Text instruct("Press corresponding key", font, 16);
                    instruct.setFillColor(sf::Color::Black);
                    instruct.setPosition(300, 220 + (endIndex - startIndex) * 30);
                    window.draw(instruct);
                }
            }
            else if (popupState == PopupState::Gardenbed)
            {
                sf::RectangleShape menuBox(sf::Vector2f(400,300));
                menuBox.setFillColor(sf::Color(200,200,200));
                menuBox.setPosition(200,150);
                window.draw(menuBox);
                // Draw grid of 9 slots.
                const int cols = 3, rows = 3;
                const float slotSize = 80.f;
                const float spacing = 10.f;
                float startX = 220.f, startY = 170.f;
                for (int i = 0; i < NUM_GARDEN_SLOTS; i++)
                {
                    int col = i % cols;
                    int row = i / cols;
                    sf::RectangleShape slotRect(sf::Vector2f(slotSize, slotSize));
                    slotRect.setPosition(startX + col * (slotSize + spacing),
                                           startY + row * (slotSize + spacing));
                    if (!gardenSlots[i].shoveled)
                        slotRect.setFillColor(sf::Color(200,100,100));
                    else if (gardenSlots[i].crop == nullptr)
                        slotRect.setFillColor(sf::Color(100,200,100));
                    else
                        slotRect.setFillColor(sf::Color(100,100,250));
                    window.draw(slotRect);
                    sf::Text numText(std::to_string(i+1), font, 16);
                    numText.setFillColor(sf::Color::White);
                    numText.setPosition(slotRect.getPosition().x + 30,
                                        slotRect.getPosition().y + 30);
                    window.draw(numText);
                }
                sf::Text instruct("Press 1-9 to select a slot", font, 18);
                instruct.setFillColor(sf::Color::Black);
                instruct.setPosition(250,450);
                window.draw(instruct);
            }
            else if (popupState == PopupState::GardenbedSlotMenu)
            {
                GardenSlot &slot = gardenSlots[selectedSlotIndex];
                if (!slot.shoveled)
                {
                    sf::RectangleShape menuBox(sf::Vector2f(250,100));
                    menuBox.setFillColor(sf::Color(220,220,220));
                    menuBox.setPosition(275,225);
                    window.draw(menuBox);
                    sf::Text menuText("Press S to Shovel", font, 20);
                    menuText.setFillColor(sf::Color::Black);
                    menuText.setPosition(280,240);
                    window.draw(menuText);
                    sf::Text escText("Press Escape to go back", font, 16);
                    escText.setFillColor(sf::Color::Black);
                    escText.setPosition(280,280);
                    window.draw(escText);
                }
                else if (slot.shoveled && slot.crop == nullptr)
                {
                    // Gardenbed planting: dynamic seed selection menu.
                    std::set<int> distinct;
                    for (int s : seedInventory)
                        distinct.insert(s);
                    std::vector<int> distinctSeeds(distinct.begin(), distinct.end());
                    int totalOptions = distinctSeeds.size();
                    int optionsPerPage = 5;
                    int startIndex = seedOptionPage * optionsPerPage;
                    int endIndex = std::min(startIndex + optionsPerPage, totalOptions);
                    float menuHeight = 50.f * ((endIndex - startIndex) + 1);
                    sf::RectangleShape menuBox(sf::Vector2f(250, menuHeight));
                    menuBox.setFillColor(sf::Color(220,220,220));
                    menuBox.setPosition(275,225);
                    window.draw(menuBox);
                    sf::Text menuText("Select Seed to Plant", font, 20);
                    menuText.setFillColor(sf::Color::Black);
                    menuText.setPosition(280,235);
                    window.draw(menuText);
                    for (int i = startIndex; i < endIndex; i++)
                    {
                        int optionNumber = i - startIndex + 1;
                        sf::Text optText(std::to_string(optionNumber) + ": " + availableSeeds[distinctSeeds[i]].GetNameOfItem(),
                                         font, 18);
                        optText.setFillColor(sf::Color::Black);
                        optText.setPosition(300, 280 + (i - startIndex) * 40);
                        window.draw(optText);
                    }
                    if (endIndex < totalOptions)
                    {
                        sf::Text moreText("0: Next Page", font, 18);
                        moreText.setFillColor(sf::Color::Black);
                        moreText.setPosition(300, 280 + (endIndex - startIndex) * 40);
                        window.draw(moreText);
                    }
                }
                else if (slot.shoveled && slot.crop != nullptr)
                {
                    sf::RectangleShape menuBox(sf::Vector2f(250,150));
                    menuBox.setFillColor(sf::Color(220,220,220));
                    menuBox.setPosition(275,225);
                    window.draw(menuBox);
                    sf::Text menuText("Slot Options", font, 20);
                    menuText.setFillColor(sf::Color::Black);
                    menuText.setPosition(310,240);
                    window.draw(menuText);
                    sf::Text opt1("W: Water", font, 18);
                    opt1.setFillColor(sf::Color::Black);
                    opt1.setPosition(300,300);
                    window.draw(opt1);
                    sf::Text opt2("H: Harvest", font, 18);
                    opt2.setFillColor(sf::Color::Black);
                    opt2.setPosition(300,340);
                    window.draw(opt2);
                    sf::Text escText("Press Escape to go back", font, 16);
                    escText.setFillColor(sf::Color::Black);
                    escText.setPosition(300,380);
                    window.draw(escText);
                }
            }
            else if (popupState == PopupState::GameOver)
            {
                // Draw a red game-over box.
                sf::RectangleShape menuBox(sf::Vector2f(400, 200));
                menuBox.setFillColor(sf::Color(180, 50, 50));
                menuBox.setPosition(200, 200);
                window.draw(menuBox);
            
                // Create the "GAME OVER" text with an outline.
                sf::Text overText("GAME OVER", font, 36);
                overText.setFillColor(sf::Color::White);
                overText.setOutlineColor(sf::Color::Black);
                overText.setOutlineThickness(2.f);
                sf::FloatRect textRect = overText.getLocalBounds();
                overText.setOrigin(textRect.left + textRect.width / 2.0f,
                                   textRect.top + textRect.height / 2.0f);
                overText.setPosition(window.getSize().x / 2.0f, 240);
                window.draw(overText);
            
                // Create the instructions text with an outline.
                sf::Text instruct("Press Enter to Restart\nPress Escape to Exit", font, 20);
                instruct.setFillColor(sf::Color::White);
                instruct.setOutlineColor(sf::Color::Black);
                instruct.setOutlineThickness(1.f);
                instruct.setPosition(230, 300);
                window.draw(instruct);
            }
            
        }
        // ------------------------------------------------------------------
        window.display();

        // ------------------------ Check Win Condition ------------------------
        if (gameWon)
        {
            sf::Text winText("Congratulations!\nYou Win!", font, 40);
            winText.setFillColor(sf::Color::Green);
            sf::FloatRect textRect = winText.getLocalBounds();
            winText.setOrigin(textRect.left + textRect.width/2.0f,
                              textRect.top + textRect.height/2.0f);
            winText.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f);
            window.clear();
            window.draw(winText);
            window.display();
            sf::sleep(sf::seconds(3));
            window.close();
        }
    } // End main game loop

    return 0;
}

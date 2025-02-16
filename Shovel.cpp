#include "shovel.h"
#include"Item.h"
#include"User.h"

Shovel::Shovel(User* User1, GardenBed*Garden1) : Item("Shovel", 50),User1(User1),Garden1(Garden1) {
    SetNameOfItem("Shovel"); //sets the name of the item to shovel 
    SetCostOfItem(50);//sets the price of the item to 50 

};





Shovel::~Shovel() {} //destructors for the shovel 



void Shovel::ShovelTheGround() {
    if(!GetIsBought()){//if the item is not  baugh than this fucntion cant be used
        std::cout << "The shovel is not bought yet" << std::endl; 
        return;
    }
    std::cout << "The ground has been shoveled." << std::endl; //displays this message 
    Garden1->SetShoveled(true); //sets the gardenbed ground to be shoveled hence allowing the User1 to plant stuff in the garden bed
}


void Shovel::BuyThisItem(){
    if (GetIsBought()) {
        std::cout << "Shovel is already purchased." << std::endl;
        return;
    }
    int Cost = GetCostOfItem();
    if (User1->GetMoney() >= Cost) {
        User1->SetMoney(User1->GetMoney() - Cost);
        SetIsBought(true);
        std::cout << "Shovel bought successfully!" << std::endl;
    } else {
        std::cout << "Not enough money to buy the Shovel." << std::endl;
    }
}

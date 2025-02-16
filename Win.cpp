#include"Win.h"
#include"User.h"



Win::Win(User* User1) : Item("Win",500),User1(User1){ //the win constructor, inherts from item 
    SetNameOfItem("Win"); //sets the name of the item to win 
    SetCostOfItem(500);//sets the price of the item to 500

}
void Win::BuyThisItem(){
    int Cost = GetCostOfItem();
    if (User1->GetMoney() >= Cost) {
        User1->SetMoney(User1->GetMoney() - Cost);
        SetIsBought(true);  // mark as purchased
        std::cout << "You won!!!!!!!!!" << std::endl;
    } else { 
        SetIsBought(false); // explicitly ensure flag remains false
        std::cout << "Not enough money, plant more crops." << std::endl;
    }
}

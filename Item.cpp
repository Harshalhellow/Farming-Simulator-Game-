#include"Item.h"


Item::Item(std::string NameOfItem, int CostOfItem): NameOfItem("Default"), CostOfItem(0){ //this is the deafult constructor of an item  with a name called deafult and a cost of 0 

};

 Item::~Item(){};
int Item::GetCostOfItem()const{
    return CostOfItem; //getter for the cost of item 
};
void Item::SetCostOfItem(int cost){
    this->CostOfItem = cost; //setter for the cost of the item
}; 
bool Item::GetIsBought(){
    return IsBought; //getter of the Is bought 
}; 
void Item::SetIsBought(bool value){
    this->IsBought = value; //setter of the is bought 
}; 
void Item::SetNameOfItem(string NameOfItem){
    this->NameOfItem = NameOfItem; //seter of  the name of item 
};
string Item::GetNameOfItem(){
    return NameOfItem; //getter of the name 
}; 

void Item::BuyThisItem(){ //a virtual buy this item function that the deafult does nothing but this will overidden by its inhereted classes 
    
};
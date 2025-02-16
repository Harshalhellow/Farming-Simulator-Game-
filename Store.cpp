#include "Store.h"
#include"Item.h"


Store::~Store(){
    delete [] ItemsInStore;//destructor for the store and deletes all the item pointer 
};

Store::Store(int MaxItems) {
    this->MaxItems = MaxItems; //sets max number of items given in the paramater to the max number of items of the store 
    CurrentNumberOfItems = 0; //sets the current number of items to 0 
    ItemsInStore = new Item*[MaxItems]; //assigns the pointer that points to the first array of pointers that point to item class or inhereted class from item
    
};
void Store::AddItemToStore(Item* NewItem){
if(CurrentNumberOfItems < MaxItems){ //if there is room in the shop 
    ItemsInStore[CurrentNumberOfItems] = NewItem; //assigns the next item in the array of pointers to given pointer in the paramter. it does this by doing pointer arthimtic of added the current number of item in the points
    CurrentNumberOfItems++; //increase the number of item in the store by 1 
}
else {
    std::cout << "Store is full cant add items" << std::endl;  //displays this if the store is full 
}


};

void Store::GetListOfItemsInStore() {
  for (int i = 0; i < CurrentNumberOfItems; i++){ //displays the current list of items and thier price  by going through the array of the pointers by using pointer arthimetic in the for loop
    std::cout << "Item: " << ItemsInStore[i]->GetNameOfItem() << "  and the cost of this item is: " << ItemsInStore[i]->GetCostOfItem() << std::endl;
  }
};



void Store::BuyThisItem(int itemNumber) {
    int index = itemNumber - 1; //this is done because indexing starts at 0 in the array however most people say oh i want the first item not the 0th item 
    if (index >= 0 && index < CurrentNumberOfItems) { //this checks if the number they gave is actuall in the store and then  allows them to buy any item if they type the number of the item however i doubt this will be used because we are not doing any written User1 inputs but this is fine as each item as its own buy this item code that be used insead. 
        ItemsInStore[index]->BuyThisItem();
    } else {
        std::cout << "Invalid item number." << std::endl; //if not in the store displays this 
    }
}

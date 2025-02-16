#ifndef STORE_H
#define STORE_H
#include <string>
#include <iostream>
#include"Item.h"
using namespace std;
class Store{
private:
int MaxItems; //holds the max number of items that can be held in the store 
int CurrentNumberOfItems; //holds the current number of items 
Item** ItemsInStore; //holds the pointers of a list of pointers that point to items or classes inheredted by items in our case 
public:

~Store(); //destructor 
Store(int MaxItems); //constructor paramtised 
void GetListOfItemsInStore(); 
void BuyThisItem(int index);

void AddItemToStore(Item* NewItem);


};


#endif
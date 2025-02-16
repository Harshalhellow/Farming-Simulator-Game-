#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
//the item class is never directly used but instead is just a base class that is used for inherentance purpuses for items. 
using namespace std;
class Item{
    private:
string NameOfItem; //the name of the item 
int CostOfItem; //cost of the item 
bool IsBought; // is the item bought or not 
public: 

Item(std::string NameOfItem, int CostOfItem); //constructor 
 ~Item(); //destructor 
int GetCostOfItem()const; 
void SetCostOfItem(int cost);
bool GetIsBought(); 
void SetIsBought(bool value);
void SetNameOfItem(string NameOfItem);
string GetNameOfItem();
virtual void BuyThisItem() = 0;
};

#endif
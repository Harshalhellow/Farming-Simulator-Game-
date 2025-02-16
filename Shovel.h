#ifndef SHOVEL_H 
#define SHOVEL_H 
#include "Store.h"
#include "GardenBed.h"
#include"User.h"

class Shovel : public Item {
private:
    User* User1; // pointer to a user 
    GardenBed* Garden1; // pointer to a garden bed 
public:
    Shovel( User* User1, GardenBed* Garden1); // constructor with a pointer to the user and the garden 
    ~Shovel();
    void ShovelTheGround();
    void BuyThisItem() override;
};


#endif 
//
//  Inventory.h
//  stephen_test_4
//
//  Created by Stephen McGregor on 11/20/15.
//  Copyright (c) 2015 Stephen McGregor. All rights reserved.
//

#include "Items.h"
#include <string>
#include <vector>
using namespace std;
class Inventory
{
private:
    vector<Item*> inventory;
public:
    Inventory()
    {
        //Map* map = new Map;
        //addItem(map);
        //removeItem(map);
    }
    Inventory(vector<Item*> startingInventory)
    {
        inventory = startingInventory;
    }
    
    Item* operator [] (long i) {return inventory[i];}
    
    long getSize() {return inventory.size();}
    void render()
    {
        if(getSize() == 0)
            cout << "backpack empty\n";
        else
        {
            for(long i = 0; i < inventory.size(); i++)
                inventory[i] -> render();
        }
    }
    long searchVector(string term)
    {
        long hold = string::npos;
        for(long i = 0; i < inventory.size(); i ++)
        {
            if(term.find(inventory[i] -> getName()) != string::npos)
            {
                hold = i;
                break;
            }
        }
        return hold;
    }
    void addItem(Item* item)
    {
        inventory.insert(inventory.begin(), item);
    }
    void removeItem(Item* item)
    {
        inventory.erase(inventory.begin() + searchVector(item -> getName()));
        //        delete item;
    }
    
    int getCount(Consumable* consumable)
    {
        return inventory[searchVector(consumable -> getName())] -> getCount();
    }
    
    int findCount(string term)
    {
        return inventory[searchVector(term)] -> getCount();
    }
    void addToConsumable(Item* consumable)
    {
        inventory[searchVector(consumable -> getName())] -> countAdjuster(consumable -> getCount());
    }
    
    void changeCount(string name, int value)
    {
        inventory[searchVector(name)] -> countAdjuster(value);
    }
    
    void inspectItem(string itemName)
    {
        cout << inventory[searchVector(itemName)] -> inspect() << endl;
    }
    string getItemName(string itemName)
    {
        return inventory[searchVector(itemName)] -> getName();
    }
    int attack(string itemName)
    {
        return inventory[searchVector(itemName)] -> attack();
    }
    int eat(string itemName)
    {
        return inventory[searchVector(itemName)] -> eat();
    }
    int drink(string itemName)
    {
        return inventory[searchVector(itemName)] -> drink();
    }
    void use(string itemName)
    {
        inventory[searchVector(itemName)] -> use();
    }
    bool hasItem(string itemName) { if (searchVector(itemName) != string::npos) return true; return false;}
    
    bool consumableCheck(Item* item)
    {
        return inventory[searchVector(item -> getName())] -> consumableCheck();
    }
    void repair(string itemName)
    {
        if (hasItem("duct tape") == true && inventory[searchVector("duct tape")] -> getCount() > 0)
        {
            if(inventory[searchVector(itemName)]->getCount() == 0)
                cout << "This item is beyond repair! Try finding a new one." << endl;
            else
            {
                inventory[searchVector(itemName)] -> repair();
                inventory[searchVector("duct tape")] -> countAdjuster(-1);
            }
            return;
        }
        
        else cout << "You don't have anything to repair this with.\n";
    }
    
};

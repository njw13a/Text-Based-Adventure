//
//  Header.h
//  String Find Test
//
//  Created by Stephen McGregor on 11/19/15.
//  Copyright (c) 2015 Stephen McGregor. All rights reserved.
//
#include <iostream>
#include <sstream>
#include "World.h"
#include "Zombie.h"
using namespace std;
//string actionList[] = {"walk", "jump", "inventory", "status"};
//string attackList[] = {"attack", "fight", "run", "zombie"};
//string targetList[] = {"crowbar", "gun"};
//string directionList[] = {"north", "south", "east", "west", "cancel"};
//string dialogueList[] = {"fight", "attack", "trade", "refuse", "leave"};
string lowerCase(string input)
{
    for (int i = 0; input[i] != 0; i++)
    {
        input[i] = tolower(input[i]);
    }
    return input;
}
string directionList[] = {"north", "south", "east", "west", "cancel"};
void walkInDirection(string input, Player* t, World* A)
{
    int num = rand() % 3 + 1;
    input = lowerCase(input);
    long hold = string::npos;
    for (int i = 0; i < 5; i++)
    {
        if(input.find(directionList[i]) != string::npos)
        {
            hold = i;
            break;
        }
    }
    if (hold == 0) //North
    {
        if (t -> getLocationX() <= 0)
        {
            cout << "You've reached the edge of town. There's nothing for you out there." << endl;
            return;
        }
        if (A->checkMap2(t->getLocationX() -1, t->getLocationY()) == 'I')
            cout << "You already tried going this way. It's impossible. Check your map." << endl;
        else if (A->checkMap(t -> getLocationX()-1, t-> getLocationY()) == 'I')
        {
            t->impasse();
            A->setMap2(t->getLocationX() -1, t->getLocationY(), 'I');
        }
        else
        {
            t->lookedN = false;
            t->lookedS = false;
            t->lookedE = false;
            t->lookedW = false;
            cout << "walked north" << endl;
            A -> setMap2(t-> getLocationX(), t->getLocationY(), 'X');
            t->walkNorth();
            t->setThirst(-5);
            A -> setMap2(t-> getLocationX(), t->getLocationY(), 'P');
            if (t -> getThirst() < 50 && t -> getThirst() > 30)
            {
                if (num == 1)
                    cout << "You are thirsty. Better find some water." << endl;
                else if (num == 2)
                    cout << "Your throat is getting pretty dry." << endl;
                else
                    cout << "You're sweating, losing quite a bit of water." << endl;
            }
            else if (t->getThirst() <= 30 && t->getThirst() >0)
            {
                if (num == 1)
                    cout << "You are extremely parched. It's a serious problem." << endl;
                else if (num == 2)
                    cout << "You feel yourself fading. You really need water." << endl;
                else
                    cout << "Your thirst is starting to affect your motor functions. You won't last much longer." << endl;
            }
            else if (t->getThirst() < 1)
            {
                cout << "You have died from dehydration. Managing recources and supplies is an important part of this game. Next time, try running from zombies less often, as this impacts your thirst level the most. Thank you for playing!!!" << endl;
                exit(0);
            }
        }
    }
    else if (hold == 1) //South
    {
        if (t -> getLocationX() >= A->getLineCount()-1)
        {
            cout << "It's just wilderness. You can't go that way." << endl;
            return;
        }
        if (A->checkMap2(t->getLocationX() +1, t->getLocationY()) == 'I')
            cout << "You already tried going this way. It's impossible. Check your map." << endl;
        else if (A->checkMap(t -> getLocationX()+1, t-> getLocationY()) == 'I')
        {
            t->impasse();
            A->setMap2(t->getLocationX() +1, t->getLocationY(), 'I');
        }
        else
        {
            t->lookedN = false;
            t->lookedS = false;
            t->lookedE = false;
            t->lookedW = false;
            cout << "walked south" << endl;
            A -> setMap2(t-> getLocationX(), t->getLocationY(), 'X');
            t->walkSouth(A->getLineCount());
            t->setThirst(-5);
            A -> setMap2(t-> getLocationX(), t->getLocationY(), 'P');
            if (t -> getThirst() < 50 && t -> getThirst() > 30)
            {
                if (num == 1)
                    cout << "You are thirsty. Better find some water." << endl;
                else if (num == 2)
                    cout << "Your throat is getting pretty dry." << endl;
                else
                    cout << "You're sweating, losing quite a bit of water." << endl;
            }
            else if (t->getThirst() <= 30 && t->getThirst() >0)
            {
                if (num == 1)
                    cout << "You are extremely parched. It's a serious problem." << endl;
                else if (num == 2)
                    cout << "You feel yourself fading. You really need water." << endl;
                else
                    cout << "Your thirst is starting to affect your motor functions. You won't last much longer." << endl;
            }
            else if (t->getThirst() < 1)
            {
                cout << "You have died from dehydration. Managing recources and supplies is an important part of this game. Next time, try running from zombies less often, as this impacts your thirst level the most. Thank you for playing!!!" << endl;
                exit(0);
            }
        }
    }
    else if (hold == 2) //East
    {
        if (t -> getLocationY() >= A->getLineCount()-1)
        {
            cout << "It's just wilderness. You can't go that way." << endl;
            return;
        }
        if (A->checkMap2(t->getLocationX(), t->getLocationY()+1) == 'I')
            cout << "You already tried going this way. It's impossible. Check your map." << endl;
        else if (A->checkMap(t -> getLocationX(), t-> getLocationY()+1) == 'I')
        {
            t->impasse();
            A->setMap2(t->getLocationX(), t->getLocationY()+1, 'I');
        }
        else
        {
            t->lookedN = false;
            t->lookedS = false;
            t->lookedE = false;
            t->lookedW = false;
            cout << "walked east" << endl;
            A -> setMap2(t-> getLocationX(), t->getLocationY(), 'X');
            t->walkEast(A -> getLineCount());
            t->setThirst(-5);
            A -> setMap2(t-> getLocationX(), t->getLocationY(), 'P');
            if (t -> getThirst() < 50 && t -> getThirst() > 30)
            {
                if (num == 1)
                    cout << "You are thirsty. Better find some water." << endl;
                else if (num == 2)
                    cout << "Your throat is getting pretty dry." << endl;
                else
                    cout << "You're sweating, losing quite a bit of water." << endl;
            }
            else if (t->getThirst() <= 30 && t->getThirst() >0)
            {
                if (num == 1)
                    cout << "You are extremely parched. It's a serious problem." << endl;
                else if (num == 2)
                    cout << "You feel yourself fading. You really need water." << endl;
                else
                    cout << "Your thirst is starting to affect your motor functions. You won't last much longer." << endl;
            }
            else if (t->getThirst() < 1)
            {
                cout << "You have died from dehydration. Managing recources and supplies is an important part of this game. Next time, try running from zombies less often, as this impacts your thirst level the most. Thank you for playing!!!" << endl;
                exit(0);
            }
        }
    }
    else if (hold == 3) //West
    {
        if (t -> getLocationY() <= 0)
        {
            cout << "It's just wilderness. You can't go that way." << endl;
            return;
        }
        if (A->checkMap2(t->getLocationX(), t->getLocationY()-1) == 'I')
            cout << "You already tried going this way. It's impossible. Check your map." << endl;
        else if (A->checkMap(t -> getLocationX(), t-> getLocationY()-1) == 'I')
        {
            t->impasse();
            A->setMap2(t->getLocationX(), t->getLocationY()-1, 'I');
        }
        else
        {
            t->lookedN = false;
            t->lookedS = false;
            t->lookedE = false;
            t->lookedW = false;
            cout << "walked west" << endl;
            A -> setMap2(t-> getLocationX(), t->getLocationY(), 'X');
            t->walkWest();
            t->setThirst(-5);
            A -> setMap2(t-> getLocationX(), t->getLocationY(), 'P');
            if (t -> getThirst() < 50 && t -> getThirst() > 30)
            {
                if (num == 1)
                    cout << "You are thirsty. Better find some water." << endl;
                else if (num == 2)
                    cout << "Your throat is getting pretty dry." << endl;
                else
                    cout << "You're sweating, losing quite a bit of water." << endl;
            }
            else if (t->getThirst() <= 30 && t->getThirst() >0)
            {
                if (num == 1)
                    cout << "You are extremely parched. It's a serious problem." << endl;
                else if (num == 2)
                    cout << "You feel yourself fading. You really need water." << endl;
                else
                    cout << "Your thirst is starting to affect your motor functions. You won't last much longer." << endl;
            }
            else if (t->getThirst() < 1)
            {
                cout << "You have died from dehydration. Managing recources and supplies is an important part of this game. Next time, try running from zombies less often, as this impacts your thirst level the most. Thank you for playing!!!" << endl;
                exit(0);
            }
        }
    }
    else if (hold == 4)
        cout << "never mind." << endl;
    else if (hold == string::npos)
    {
        cout << "walk where? (north, south, east, west, cancel)" << endl;
        getline(cin, input);
        walkInDirection(input, t, A);
    }
    
}
void lookInDirection(string input, Player* t, World* A)
{
    input = lowerCase(input);
    long hold = string::npos;
    for (int i = 0; i < 5; i++)
    {
        if(input.find(directionList[i]) != string::npos)
        {
            hold = i;
            break;
        }
    }
    if (hold == 0) //North
    {
        if (t -> getLocationX() <= 0)
        {
            cout << "It's just wilderness. You can't go that way." << endl;
            return;
        }
        else if (t->lookedN == false)
        {
            cout << "looked north" << endl;
            t->lookedN = true;
            if (A->checkMap(t->getLocationX()-1, t->getLocationY()) == 'Z')
            {
                int num = rand() % 3 + 1;
                if (num== 1)
                    cout << "You hear a distinct groan and some shuffling." << endl;
                else if (num ==2)
                    cout << "You don't see anything that would indicate any danger. It's quiet." << endl;
                else
                    cout << "You notice some rustling. Could be the wind, or an animal. Could be something else." << endl;
                A->setMap2(t->getLocationX()-1, t->getLocationY(), '?');
            }
            else if (A->checkMap(t->getLocationX()-1, t->getLocationY()) == 'S')
            {
                int num = rand() % 2 + 1;
                if (num ==1)
                    cout << "You don't see anything that would indicate any danger. It's quiet." << endl;
                else
                    cout << "You notice some rustling. Could be the wind or an animal. Could be something else." << endl;
                A->setMap2(t->getLocationX()-1, t->getLocationY(), '?');
            }
            else if (A->checkMap(t->getLocationX()-1, t->getLocationY()) == 'X')
                cout << "There is nothing of note in that direction. You came through that area not too long ago." << endl;
            else if (A->checkMap(t->getLocationX()-1, t->getLocationY()) == 'D')
                cout << "You can still see the dead zombie you killed earlier sprawled out on the ground." << endl;
            else if (A->checkMap(t->getLocationX()-1, t->getLocationY()) == 'I')
                cout << "Looks like you can't go that way." << endl;
            else
                cout << "You see a building. It could have valuable supplies inside." << endl;
        }
        else
            cout << "You have already looked there. Nothing has changed." << endl;
    }
    else if (hold == 1) //South
    {
        if (t -> getLocationX() >= A->getLineCount()-1)
        {
            cout << "It's just wilderness. You can't go that way." << endl;
            return;
        }
        else if(t->lookedS == false)
        {
            cout << "looked south" << endl;
            t->lookedS = true;
            if (A->checkMap(t->getLocationX()+1, t->getLocationY()) == 'Z')
            {
                int num = rand() % 3 + 1;
                if (num== 1)
                    cout << "You hear a distinct groan and some shuffling." << endl;
                else if (num ==2)
                    cout << "You don't see anything that would indicate any danger. It's quiet." << endl;
                else
                    cout << "You notice some rustling. Could be the wind, or an animal. Could be something else." << endl;
                A->setMap2(t->getLocationX()+1, t->getLocationY(), '?');
            }
            else if (A->checkMap(t->getLocationX()+1, t->getLocationY()) == 'S')
            {
                int num = rand() % 2 + 1;
                if (num ==1)
                    cout << "You don't see anything that would indicate any danger. It's quiet." << endl;
                else
                    cout << "You notice some rustling. Could be the wind or an animal. Could be something else." << endl;
                A->setMap2(t->getLocationX()+1, t->getLocationY(), '?');
            }
            else if (A->checkMap(t->getLocationX()+1, t->getLocationY()) == 'X')
                cout << "There is nothing of note in that direction. You came through that area not too long ago." << endl;
            else if (A->checkMap(t->getLocationX()+1, t->getLocationY()) == 'D')
                cout << "You can still see the dead zombie you killed earlier sprawled out on the ground." << endl;
            else if (A->checkMap(t->getLocationX()+1, t->getLocationY()) == 'I')
                cout << "Looks like you can't go that way." << endl;
            else
                cout << "You see a building. It could have valuable supplies inside." << endl;
        }
        else
            cout << "You have already looked there. Nothing has changed." << endl;
    }
    else if (hold == 2) //East
    {
        if (t -> getLocationY() >= A->getLineCount()-1)
        {
            cout << "It's just wilderness. You can't go that way." << endl;
            return;
        }
        else if(t->lookedE == false)
        {
            cout << "looked east" << endl;
            t->lookedE = true;
            if (A->checkMap(t->getLocationX(), t->getLocationY()+1) == 'Z')
            {
                int num = rand() % 3 + 1;
                if (num== 1)
                    cout << "You hear a distinct groan and some shuffling." << endl;
                else if (num ==2)
                    cout << "You don't see anything that would indicate any danger. It's quiet." << endl;
                else
                    cout << "You notice some rustling. Could be the wind, or an animal. Could be something else." << endl;
                A->setMap2(t->getLocationX(), t->getLocationY()+1, '?');
            }
            else if (A->checkMap(t->getLocationX(), t->getLocationY()+1) == 'S')
            {
                int num = rand() % 2 + 1;
                if (num ==1)
                    cout << "You don't see anything that would indicate any danger. It's quiet." << endl;
                else
                    cout << "You notice some rustling. Could be the wind or an animal. Could be something else." << endl;
                A->setMap2(t->getLocationX(), t->getLocationY()+1, '?');
            }
            else if (A->checkMap(t->getLocationX(), t->getLocationY()+1) == 'X')
                cout << "There is nothing of note in that direction. You came through that area not too long ago." << endl;
            else if (A->checkMap(t->getLocationX(), t->getLocationY()+1) == 'D')
                cout << "You can still see the dead zombie you killed earlier sprawled out on the ground." << endl;
            else if (A->checkMap(t->getLocationX(), t->getLocationY()+1) == 'I')
                cout << "Looks like you can't go that way." << endl;
            else
                cout << "You see a building. It could have valuable supplies inside." << endl;
        }
        else
            cout << "You have already looked there. Nothing has changed." << endl;
    }
    else if (hold == 3) //West
    {
        if (t -> getLocationY() <= 0)
        {
            cout << "It's just wilderness. You can't go that way." << endl;
            return;
        }
        else if(t->lookedW == false)
        {
            cout << "looked west" << endl;
            t->lookedW = true;
            if (A->checkMap(t->getLocationX(), t->getLocationY()-1) == 'Z')
            {
                int num = rand() % 3 + 1;
                if (num== 1)
                    cout << "You hear a distinct groan and some shuffling." << endl;
                else if (num ==2)
                    cout << "You don't see anything that would indicate any danger. It's quiet." << endl;
                else
                    cout << "You notice some rustling. Could be the wind, or an animal. Could be something else." << endl;
                A->setMap2(t->getLocationX(), t->getLocationY()-1, '?');
            }
            else if (A->checkMap(t->getLocationX(), t->getLocationY()-1) == 'S')
            {
                int num = rand() % 2 + 1;
                if (num ==1)
                    cout << "You don't see anything that would indicate any danger. It's quiet." << endl;
                else
                    cout << "You notice some rustling. Could be the wind or an animal. Could be something else." << endl;
                A->setMap2(t->getLocationX(), t->getLocationY()-1, '?');
            }
            else if (A->checkMap(t->getLocationX(), t->getLocationY()-1) == 'X')
                cout << "There is nothing of note in that direction. You came through that area not too long ago." << endl;
            else if (A->checkMap(t->getLocationX(), t->getLocationY()-1) == 'D')
                cout << "You can still see the dead zombie you killed earlier sprawled out on the ground." << endl;
            else if (A->checkMap(t->getLocationX(), t->getLocationY()-1) == 'I')
                cout << "Looks like you can't go that way." << endl;
            else
                cout << "You see a building. It could have valuable supplies inside." << endl;
        }
        else
            cout << "You have already looked there. Nothing has changed." << endl;
    }
    else if (hold == 4)
        cout << "never mind." << endl;
    else if (hold == string::npos)
    {
        cout << "look where? (north, south, east, west, cancel)" << endl;
        getline(cin, input);
        lookInDirection(input, t, A);
    }
}
bool attackAction(string input, Zombie* z, Player* t, World* A)
{
    input = lowerCase(input);
    long hold = string::npos;
    for (int i = 0; i < t -> getBackpack().getSize(); i++)
    {
        if(input.find(t -> getBackpack()[i] -> getName()) != string::npos)
        {
            hold = i;
            break;
        }
    }
    if(hold == string::npos)
    {
        cout << "What do you want to attack with? \n\ninventory: \n-------\n";
        t -> getBackpack().render();
        cout << "-------\n";
        getline(cin, input);
        return attackAction(input, z, t, A);
    }
    else if(t -> getBackpack()[hold] -> getName() == "handgun") //Attack sequence handgun
    {
        if(t -> getBackpack().searchVector("hgbullet") != string::npos)
        {
            //cout << "count: " << t -> getBackpack().findCount("hgbullet") << endl;
            if(t -> getBackpack().findCount("hgbullet") > 0)
            {
                t -> changeConsumableCount("hgbullet", -1);
                int damage = t -> attackWithItem(t -> getBackpack()[hold] -> getName());
                z -> changeHealth((-1)*damage);
                if (A->difficulty == 1)
                {
                    if (z -> getHealth() > 0)
                        cout << "Enemy health: " << z -> getHealth() << endl;
                }
                if (z -> getHealth() > 15)
                {
                    cout << "He's still alive! Watch out, here comes a counterattack!" << endl;
                    z -> attack(t, A);
                    return true;
                }
                else if (z -> getHealth() <= 15 && z -> getHealth() > 0)
                {
                    cout << "How is he still alive?!?! Finish him off!!!" << endl;
                    return true;
                }
                cout << "You have killed him. Hard fought battle. Well done." << endl;
                z -> getZloot(t);
                A->setMap(t->getLocationX(), t->getLocationY(), 'D');
                return false;
            }
            else cout << "You don't have ammo for this.\n";
        }
        else cout << "You don't have ammo for this.\n";
    }
    else if(t -> getBackpack()[hold] -> getName() == "shotgun") //Attack sequence shotgun
    {
        if(t -> getBackpack().searchVector("sgshell") != string::npos)
        {
            //cout << "count: " << t -> getBackpack().findCount("sgshell") << endl;
            if(t -> getBackpack().findCount("sgshell") > 0)
            {
                t -> changeConsumableCount("sgshell", -1);
                int damage = t -> attackWithItem(t -> getBackpack()[hold] -> getName());
                z -> changeHealth((-1)*damage);
                if (A->difficulty == 1)
                {
                    if (z -> getHealth() > 0)
                        cout << "Enemy health: " << z -> getHealth() << endl;
                }
                if (z -> getHealth() > 15)
                {
                    cout << "He's still alive! Watch out, here comes a counterattack!" << endl;
                    z -> attack(t,A);
                    return true;
                }
                else if (z -> getHealth() <= 15 && z -> getHealth() > 0)
                {
                    cout << "How is he still alive?!?! Finish him off!!!" << endl;
                    return true;
                }
                cout << "You have killed him. Hard fought battle. Well done." << endl;
                z -> getZloot(t);
                A->setMap(t->getLocationX(), t->getLocationY(), 'D');
                return false;
            }
            else cout << "You don't have ammo for this.\n";
        }
        else cout << "You don't have ammo for this.\n";
    }
    else //Attack sequence melee
    {
        int damage = t -> attackWithItem(t -> getBackpack()[hold] -> getName());
        z -> changeHealth((-1)*damage);
        if (A->difficulty == 1)
        {
            if (z -> getHealth() > 0)
                cout << "Enemy health: " << z -> getHealth() << endl;
        }
        if (z -> getHealth() > 15)
        {
            int num = rand() % 3 + 1;
            if (num == 1)
                cout << "He's still alive! Watch out, here comes a counterattack!" << endl;
            else if (num == 2)
                cout << "That hurt him, but he's still coming!" << endl;
            else
                cout << "That didn't kill him! He's retaliating!" << endl;
            z -> attack(t, A);
            return true;
        }
        else if (z -> getHealth() <= 15 && z -> getHealth() > 0)
        {
            int num = rand() % 3 + 1;
            if (num == 1)
                cout << "How is he still alive?!?! Finish him off!!!" << endl;
            else if (num == 2)
                cout << "FINISH HIM" << endl;
            else
                cout << "That almost did it. Put him out of his misery." << endl;
            return true;
        }
        int num = rand() % 3 + 1;
        if (num == 1)
            cout << "You have killed him. Hard fought battle. Well done." << endl;
        else if (num == 2)
            cout << "You are victorious...this time." << endl;
        else
            cout << "Whew you broke a pretty heavy sweat in that fight, but a kill is a kill." << endl;
        z -> getZloot(t);
        A->setMap(t->getLocationX(), t->getLocationY(), 'D');
        return false;
    }
    return true;
}
void inspectString(string input, Player* t)
{
    input = lowerCase(input);
    long hold = string::npos;
    for (int i = 0; i < t -> getBackpack().getSize(); i++)
    {
        if(input.find(t -> getBackpack()[i] -> getName()) != string::npos)
        {
            hold = i;
            break;
        }
    }
    if(hold == string::npos)
    {
        cout << "inspect what? \n\ninventory: \n-------\n";
        t -> getBackpack().render();
        cout << "-------\n";
        getline(cin, input);
        inspectString(input, t);
    }
    
    else t -> inspectBackpackItem(t -> getBackpack()[hold] -> getName());
}
void drinkItem(string input, Player* t)
{
    long hold = string::npos;
    for (int i = 0; i < t -> getBackpack().getSize(); i++)
    {
        if(input.find(t -> getBackpack()[i] -> getName()) != string::npos)
        {
            hold = i;
            break;
        }
    }
    Item* itemHold = t -> getBackpack()[hold];
    if(hold == string::npos)
    {
        cout << "drink what? \n\ninventory: \n-------\n";
        t -> getBackpack().render();
        cout << "-------\n";
        getline(cin, input);
        drinkItem(input, t);
    }
    else if (t -> getBackpack().consumableCheck(itemHold) == false || (t->getBackpack()[hold] ->getCount() > 0))
    {
        t -> drinkItem(t -> getBackpack()[hold] -> getName());
    }
    else cout << "You don't have that. \n";
}
void eatItem(string input, Player* t)
{
    long hold = string::npos;
    for (int i = 0; i < t -> getBackpack().getSize(); i++)
    {
        if(input.find(t -> getBackpack()[i] -> getName()) != string::npos)
        {
            hold = i;
            break;
        }
    }
    Item* itemHold = t -> getBackpack()[hold];
    if(hold == string::npos)
    {
        cout << "eat what? \n\ninventory: \n-------\n";
        t -> getBackpack().render();
        cout << "-------\n";
        getline(cin, input);
        eatItem(input, t);
    }
    else if (t -> getBackpack().consumableCheck(itemHold) == false || (t->getBackpack()[hold] ->getCount() > 0))
    {
        t -> eatItem(t -> getBackpack()[hold] -> getName());
    }
    else cout << "You don't have that. \n";
}
void useItem(string input, Player* t)
{
    long hold = string::npos;
    for (int i = 0; i < t -> getBackpack().getSize(); i++)
    {
        if(input.find(t -> getBackpack()[i] -> getName()) != string::npos)
        {
            hold = i;
            break;
        }
    }
    Item* itemHold = t -> getBackpack()[hold];
    if(hold == string::npos)
    {
        cout << "use what? \n\ninventory: \n-------\n";
        t -> getBackpack().render();
        cout << "-------\n";
        getline(cin, input);
        useItem(input, t);
    }
    else if (t -> getBackpack().consumableCheck(itemHold) == false || (t->getBackpack()[hold] ->getCount() > 0))
    {
        t -> useItem(t -> getBackpack()[hold] -> getName());
    }
    else cout << "You don't have that. \n";
}
void repairItem(string input, Player* t)
{
    long hold = string::npos;
    for (int i = 0; i < t -> getBackpack().getSize(); i++)
    {
        if(input.find(t -> getBackpack()[i] -> getName()) != string::npos)
        {
            hold = i;
            break;
        }
    }
    if(hold == string::npos)
    {
        cout << "repair what? \n\ninventory: \n-------\n";
        t -> getBackpack().render();
        cout << "-------\n";
        getline(cin, input);
        repairItem(input, t);
    }
    else
        t -> repairItem(t -> getBackpack()[hold] -> getName());
}
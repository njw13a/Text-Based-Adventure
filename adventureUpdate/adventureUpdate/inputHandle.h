//
//  acceptableStrings.h
//  String Find Test
//
//  Created by Stephen McGregor on 11/14/15.
//  Copyright (c) 2015 Stephen McGregor. All rights reserved.
//
#include "actionFunctions.h"
string attackList[] = {"attack", "fight", "run", "status", "help"};
void handleFightString(string input, Zombie* z, Player* p, World* A)
{
    int num = rand() % 3 + 1;
    input = lowerCase(input);
    int hold = -1;
    
    for (int i = 0; i < 5; i++)
    {
        if(input.find(attackList[i]) != string::npos)
        {
            hold = i;
            break;
        }
    }
    if(hold == 0 || hold == 1) //Attack/Fight
    {
        if (attackAction(input, z, p, A))
        {
            getline(cin, input);
            handleFightString(input, z, p, A);
        }
    }
    else if(hold == 2) //Run
    {
        if (z -> run() == false)
        {
            p -> setHealth((-1) * (z -> getAttack()*A->difficulty));
            if (p -> checkDeath())
            {
                cout << "You have died. Keep an eye on your health and try to keep it as high as possible before exploring and encountering zombies. Thank you for playing!!!" << endl;
                exit(0);
            }
            getline(cin, input);
            handleFightString(input, z, p, A);
        }
        else
        {
            srand(time(NULL));
            p -> setThirst(-10);
            if (p -> getThirst() < 50 && p -> getThirst() > 30)
            {
                if (num == 1)
                    cout << "You are thirsty. Better find some water." << endl;
                else if (num == 2)
                    cout << "Your throat is getting pretty dry." << endl;
                else
                    cout << "You're sweating, losing quite a bit of water." << endl;
            }
            else if (p->getThirst() <= 30 && p->getThirst() >0)
            {
                if (num == 1)
                    cout << "You are extremely parched. It's a serious problem." << endl;
                else if (num == 2)
                    cout << "You feel yourself fading. You really need water." << endl;
                else
                    cout << "Your thirst is starting to affect your motor functions. You won't last much longer." << endl;
            }
            else if (p->getThirst() < 1)
            {
                cout << "You have died from dehydration. Managing recources and supplies is an important part of this game. Next time, try running from zombies less often, as this impacts your thirst level the most. Thank you for playing!!!" << endl;
                exit(0);
            }
            int num = rand() % 3 + 1;
            int randomDirection = rand() % 4 + 1;
            if(randomDirection == 1) //North
            {
                if (p -> getLocationX() <= 0)
                {
                    cout << "You tried to run north, but you're at the edge of town. You'd fare better here against this one zombie than out there versus 20. You couldn't escape!" << endl;
                    getline(cin, input);
                    handleFightString(input, z, p, A);
                }
                else if(A->checkMap(p -> getLocationX()-1, p-> getLocationY()) == 'I')
                {
                    cout << "You tried to run north." << endl;
                    p->impasse();
                    A->setMap2(p->getLocationX() -1, p->getLocationY(), 'I');
                    cout << "You couldn't escape!" << endl;
                    getline(cin, input);
                    handleFightString(input, z, p, A);
                }
                else
                {
                    if (num==1)
                        cout << "You sprinted to safety. That zombie was in surprisingly good shape for being....you know, dead." << endl;
                    else if (num ==2)
                        cout << "You ran as fast as you could and managed to get away. Next time you might not be so lucky..." << endl;
                    else if (num ==3)
                        cout << "You were able to evade his advances and dash away. Running is definitely a little risky." << endl;
                    A -> setMap2(p-> getLocationX(), p->getLocationY(), 'X');
                    p -> walkNorth();
                    A -> setMap2(p-> getLocationX(), p->getLocationY(), 'P');
                    cout << "You escaped to the north\n";
                }
            }
            else if(randomDirection == 2) //South
            {
                if (p -> getLocationX() >= A->getLineCount()-1)
                {
                    cout << "You tried to run south, but you're at the edge of town. You'd fare better here against this one zombie than out there versus 20. You couldn't escape!" << endl;
                    getline(cin, input);
                    handleFightString(input, z, p, A);
                }
                else if(A->checkMap(p -> getLocationX()+1, p-> getLocationY()) == 'I')
                {
                    cout << "You tried to run south." << endl;
                    p->impasse();
                    A->setMap2(p->getLocationX() +1, p->getLocationY(), 'I');
                    cout << "You couldn't escape!" << endl;
                    getline(cin, input);
                    handleFightString(input, z, p, A);
                }
                else
                {
                    if (num==1)
                        cout << "You ran away. This particular zombie was slower than most, so it wasn't too difficult." << endl;
                    else if (num ==2)
                        cout << "You jogged off. Zombies aren't exactly known for their speed." << endl;
                    else if (num ==3)
                        cout << "You trotted off, keeping a steady pace until you reached a safe distance." << endl;
                    A -> setMap2(p-> getLocationX(), p->getLocationY(), 'X');
                    p -> walkSouth(A -> getLineCount());
                    A -> setMap2(p-> getLocationX(), p->getLocationY(), 'P');
                    cout << "You escaped to the south\n";
                }
            }
            else if(randomDirection == 3) //East
            {
                if (p -> getLocationY() >= A->getLineCount()-1)
                {
                    cout << "You tried to run east, but you're at the edge of town. You'd fare better here against this one zombie than out there versus 20. You couldn't escape!" << endl;
                    getline(cin, input);
                    handleFightString(input, z, p, A);
                }
                else if(A->checkMap(p -> getLocationX(), p-> getLocationY()+1) == 'I')
                {
                    cout << "You tried to run east." << endl;
                    p->impasse();
                    A->setMap2(p->getLocationX(), p->getLocationY()+1, 'I');
                    cout << "You couldn't escape!" << endl;
                    getline(cin, input);
                    handleFightString(input, z, p, A);
                }

                else
                {
                    if (num==1)
                        cout << "You turned tail and ran. No shame in that." << endl;
                    else if (num ==2)
                        cout << "You decided to avoid conflict this time. Not a bad choice." << endl;
                    else if (num ==3)
                        cout << "You successfully escaped. Well done Usain Bolt." << endl;
                    A -> setMap2(p-> getLocationX(), p->getLocationY(), 'X');
                    p -> walkEast(A -> getLineCount());
                    A -> setMap2(p-> getLocationX(), p->getLocationY(), 'P');
                    cout << "You escaped to the east\n";
                }
            }
            else if(randomDirection == 4) //West
            {
                if (p -> getLocationY() <= 0)
                {
                    cout << "You tried to run west, but you're at the edge of town. You'd fare better here against this one zombie than out there versus 20. You couldn't escape!" << endl;
                    getline(cin, input);
                    handleFightString(input, z, p, A);
                }
                else if(A->checkMap(p -> getLocationX(), p-> getLocationY()-1) == 'I')
                {
                    cout << "You tried to run west." << endl;
                    p->impasse();
                    A->setMap2(p->getLocationX(), p->getLocationY()-1, 'I');
                    cout << "You couldn't escape!" << endl;
                    getline(cin, input);
                    handleFightString(input, z, p, A);
                }

                else
                {
                    if (num==1)
                        cout << "You ran away with your tail tucked between your legs." << endl;
                    else if (num ==2)
                        cout << "Even though it's not possible, you think you hear the zombie laugh mockingly as you scamper away." << endl;
                    else if (num ==3)
                        cout << "You successfully escaped. Well done Usain Bolt." << endl;
                    A -> setMap2(p-> getLocationX(), p->getLocationY(), 'X');
                    p -> walkWest();
                    A -> setMap2(p-> getLocationX(), p->getLocationY(), 'P');
                    cout << "You escaped to the west\n";
                }
            }
        }
    }
    else if(hold == 3) //Status
    {
        p->renderStatus();
        getline(cin, input);
        handleFightString(input,z,p,A);
    }
    else if (hold == 4) //Help
    {
        cout << "Possible commands: ";
        for (int n = 0; n < 5; n++)
        {
            cout << attackList[n] << "  ";
        }
        cout << endl;
        getline(cin,input);
        handleFightString(input, z, p, A);
    }
    else
    {
        cout << "..." << endl << "(Type help for a list of possible commands)" << endl;
        getline(cin, input);
        handleFightString(input, z, p, A);
    }
}

string dialogueList[] = {"fight", "attack", "trade", "refuse", "leave", "inventory", "status", "help"};
void handleDialogueString(string input, Player* player, npc1* survivor, World* A, int scenario)
{
    input = lowerCase(input);
    
    int hold = -1;
    
    for (int i = 0; i < 8; i++)
    {
        if(input.find(dialogueList[i]) != string::npos)
        {
            hold = i;
            break;
        }
    }
    if (hold == 0 || hold == 1) //Fight/attack
    {
        survivor -> isAttacking();
        handleFightString(input, survivor, player, A);
        return;
    }
    else if (hold == 2) //Trade
    {
        if (scenario == 1)
        {
            if (player -> getBackpack().searchVector("water") != string::npos && player -> getBackpack().findCount("water") > 0)
            {
                player -> changeConsumableCount("water", -1);
                if (player -> getBackpack().searchVector("duct tape") != string::npos)
                    player -> changeConsumableCount("duct tape", 2);
                else
                {
                    DuctTape* ducttape = new DuctTape(2);
                    player -> pickUp(ducttape);
                }
                cout << "You do your business and go your separate ways." << endl;
                return;
            }
            else
                cout << "You don't have the supplies to trade." << endl;
        }
        if (scenario == 2)
        {
            if (player -> getBackpack().searchVector("jerky") != string::npos && player -> getBackpack().findCount("jerky") > 0)
            {
                player -> changeConsumableCount("jerky", -1);
                if (player -> getBackpack().searchVector("medkit") != string::npos)
                    player -> changeConsumableCount("medkit", 1);
                else
                {
                    Medkit* medkit = new Medkit(1);
                    player -> pickUp(medkit);
                }
                cout << "You make the trade and watch as he walks off." << endl;
                return;
            }
            else
                cout << "You don't have what he wants." << endl;
        }
        if (scenario == 3)
        {
            if (player -> getBackpack().searchVector("medkit") != string::npos && player -> getBackpack().findCount("medkit") > 0)
            {
                player -> changeConsumableCount("medkit", -1);
                if (player -> getBackpack().searchVector("hgbullet") != string::npos)
                    player -> changeConsumableCount("hgbullet", 4);
                else
                {
                    HandgunAmmo* handgunAmmo = new HandgunAmmo(4);
                    player -> pickUp(handgunAmmo);
                }
                cout << "Everything goes smoothly and you get your items." << endl;
                return;
            }
            else
                cout << "You can't trade something you don't have." << endl;
        }
    }
    else if (hold == 3 || hold == 4) //Refuse/Leave
    {
        int num = rand() % 3 + 1;
        if (num == 1)
            cout << "You stroll off. Going solo is what it's all about right?" << endl;
        else if (num == 2)
            cout << "You decide not to get involved. You're doing just fine on your own." << endl;
        else
            cout << "In this world humans can be more dangerous than zombies. Leaving was the safest bet." << endl;
        return;
    }
    else if (hold == 5) //Inventory
    {
        player -> checkBackpack();
    }
    else if (hold == 6) //Status
    {
        player -> renderStatus();
    }
    else if (hold == 7) //Help
    {
        cout << "Possible commands: ";
        for (int n = 0; n < 7; n++)
        {
            cout << dialogueList[n] << "  ";
        }
        cout << endl;
    }
    else
    {
        cout << "..." << endl << "(Type help for a list of possible commands)" << endl;
    }
    getline(cin, input);
    handleDialogueString(input, player, survivor, A, scenario);
    
}
//status, inventory
string actionList[] = {"walk", "jump", "yell", "inventory", "status", "inspect", "look", "drink", "eat", "use", "repair", "map", "help", "developer###"};
void handleString(string input, Player* t, World* A)
{
    int num = rand() % 4 + 1;
    input = lowerCase(input);
    int hold = -1;
    for (int i = 0; i < 14; i++)
    {
        if(input.find(actionList[i]) != string::npos)
        {
            hold = i;
            break;
        }
    }
    if (hold == 0) //Walk
    {
        walkInDirection(input, t, A);
    }
    else if (hold == 1) //Jump
    {
        t->setThirst(-5);
        cout << "Jumped. How fun." << endl;
    }
    else if (hold == 2) //Yell
    {
        if (num == 1)
            cout << "You let out a primal scream. The sound echoed through the empty streets." << endl;
        else if (num == 2)
            cout << "You yell out at the top of your lungs. Someone, or something, is sure to have heard it." << endl;
        else if (num == 3)
            cout << "You cry out as loud as you can. There is something headed towards you!" << endl;
        else
            cout << "You bellow out into the crisp, cool air. That definitely got somethings attention." << endl;
        if (num == 3)
        {
            int temp;
            npc1 s;
            temp = s.dialogue();
            getline(cin, input);
            handleDialogueString(input, t, &s, A, temp);
        }
        else
            A->setMap(t->getLocationX(), t->getLocationY(), 'Z');
    }
    else if (hold == 3) //Inventory
    {
        t->checkBackpack();
    }
    else if (hold == 4) //Status
    {
        t -> renderStatus();
    }
    else if (hold == 5) //Inspect
    {
        inspectString(input, t);
    }
    else if (hold == 6) //Look
    {
        lookInDirection(input, t, A);
    }
    else if (hold == 7) //Drink
    {
        drinkItem(input, t);
    }
    else if (hold == 8) //Eat
    {
        eatItem(input, t);
    }
    else if (hold == 9) //Use
    {
        useItem(input, t);
    }
    else if (hold == 10) //Repair
    {
        repairItem(input, t);
    }
    else if (hold == 11) //Map
    {
        A -> printMap();
    }
    else if (hold == 12) //Help
    {
        cout << "Possible commands: ";
        for (int n = 0; n < 12; n++)
        {
            cout << actionList[n] << "  ";
        }
        cout << endl;
    }
    else if (hold == 13)
    {
        A->visualize();
    }
    else
    {
        cout << "..." << endl << "(Type help for a list of possible commands)" << endl;
        getline(cin, input);
        handleString(input, t, A);
    }
}

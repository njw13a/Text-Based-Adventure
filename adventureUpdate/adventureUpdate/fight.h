//
//  start.h
//  fight.h
//
//  Created by Tanner Williams on 11/19/15.
//  Copyright (c) 2015 Drake. All rights reserved.
//
#include "inputHandle.h"
void startFight(Zombie* z, Player* player, World* A)
{
    string input;
    z->isAttacking();
    getline(cin, input);
    handleFightString(input, z, player, A);
}

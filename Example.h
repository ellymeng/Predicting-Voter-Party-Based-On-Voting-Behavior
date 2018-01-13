//
//  Example.h
//  P5
//
//  Created by Shi Yuan Meng on 12/7/17.
//  Copyright © 2017 Elly Meng. All rights reserved.
//

#ifndef Example_h
#define Example_h

#include "Condition.h"
#include <vector>

class Example
{
public:
    bool isPositive;
    bool isDemocrat;
    vector<Condition> observation = {}; // list of all 16 conditions
};

#endif /* Example_h */

//
//  Rule.hpp
//  P5
//
//  Created by Shi Yuan Meng on 12/7/17.
//  Copyright © 2017 Elly Meng. All rights reserved.
//

#ifndef Rule_h
#define Rule_h

#include <stdio.h>
#include <vector>
#include "Condition.h"
#include "DataSet.h"


class Rule
{
public:
    vector<Condition> conditions = {};
    bool match(Example e);

    int countMatches(DataSet dataSet);
    
    double getAccuracy(DataSet growPos, DataSet growNeg);
    double truePos(DataSet growPos);
    double trueNeg(DataSet growNeg);

};

#endif /* Rule_h */

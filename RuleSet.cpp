//
//  RuleSet.cpp
//  P5
//
//  Created by Shi Yuan Meng on 12/7/17.
//  Copyright © 2017 Elly Meng. All rights reserved.
//

#include <stdio.h>
#include "Performance.h"
#include "RuleSet.h"
#include "DataSet.h"
using namespace std;

void RuleSet::eval(DataSet growPos, DataSet growNeg)
{
    
    tp = countMatches(growPos)/rules.size();
    tn = (growNeg.data.size() - countMatches(growNeg))/rules.size();
    
    accuracy = (tp + tn)/2.0;
}

int RuleSet::countMatches(DataSet data)
{
    int count = 0;
    if(rules.size() == 0)
        count = int(data.data.size());
    else
    {
        for (Example e : data.data)
        {
            if(match(e))
                count++;
        }
    }
    return count;
}
bool RuleSet::match(Example e)
{
    bool r = true;
    //    if(conditions.size() != 0)
    //    {
    for(Rule r: rules)
    {
        if(r.match(e))
            return true;
    }
    return false;

}

// Accuracy is a proportion.  It's the number of correct predictions divided by
// the total number of examples (or the total number of prediction).

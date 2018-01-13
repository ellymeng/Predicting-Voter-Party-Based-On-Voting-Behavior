//
//  Rule.cpp
//  P5
//
//  Created by Shi Yuan Meng on 12/7/17.
//  Copyright © 2017 Elly Meng. All rights reserved.
//

#include <iostream>
#include "Rule.h"
#include "Example.h"


bool Rule::match(Example e)
{
    
    bool r = true;
//    if(conditions.size() != 0)
//    {
        for(Condition rv : conditions)
        {
            for(Condition ev : e.observation)
            {
                if(rv.attribute == ev.attribute)
                    if(rv.vote != ev.vote)
                    {
//                        cout << "ra, rv: " << rv.attribute << " " << rv.vote << " ea, ev: " << ev.attribute << " " << ev.vote << endl;
                        return false;
                    }
            }
//        }
    }
    return true;
}

int Rule::countMatches(DataSet dataSet)
{
    int count = 0;
    if(conditions.size() == 0)
        count = int(dataSet.data.size());
    else
    {
        for (Example e : dataSet.data)
        {
            if(match(e))
                count++;
        }
    }
    return count;
}


double Rule::getAccuracy(DataSet growPos, DataSet growNeg)
{
    
    return (truePos(growPos) + trueNeg(growNeg))/2.0;
}

double Rule::truePos(DataSet growPos)
{
    return countMatches(growPos)/conditions.size();
}

double Rule::trueNeg(DataSet growNeg)
{
    return (growNeg.data.size() - countMatches(growNeg))/conditions.size();
}

//
//  RuleSet.h
//  P5
//
//  Created by Shi Yuan Meng on 12/7/17.
//  Copyright © 2017 Elly Meng. All rights reserved.
//

#ifndef RuleSet_h
#define RuleSet_h
#include "Condition.h"
#include "Performance.h"
#include "DataSet.h"
#include "Rule.h"
using namespace std;

class RuleSet
{
    
public:
    vector<Rule> rules = {};
    double tp;
    double tn;
    double accuracy;
    

    // TODO
    void eval(DataSet growPos, DataSet growNeg);

    int countMatches(DataSet data);
    bool match(Example e);
    
};

#endif /* RuleSet_h */

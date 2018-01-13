//
//  DataSet.h
//  P5
//
//  Created by Shi Yuan Meng on 12/7/17.
//  Copyright © 2017 Elly Meng. All rights reserved.
//

#ifndef DataSet_h
#define DataSet_h

#include <vector>
#include "Example.h"
#include "Condition.h"
using namespace std;

//class Rule;

class DataSet
{
    public:
    vector<Example> data = {};
    
    
    // randomly selects examples for new training dataset with a 75/25 size ratio to the original dataset (test)
    vector<DataSet> holdoutSplit(DataSet growPos, DataSet growNeg, double ratio);
    
    DataSet getDemocrats();
    
    DataSet getRepublicans();
    

};

#endif /* DataSet_h */

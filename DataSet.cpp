//
//  DataSet.cpp
//  P5
//
//  Created by Shi Yuan Meng on 12/7/17.
//  Copyright © 2017 Elly Meng. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include "DataSet.h"
using namespace std;

vector<DataSet> DataSet::holdoutSplit(DataSet growPos, DataSet growNeg, double ratio)
{
    double randVal;
    vector<DataSet> train_test;
    DataSet trainSet;
    DataSet testSet;
    
    for(int i = 0; i < growPos.data.size(); i++)
    {
        randVal = (double)rand() / ((double)RAND_MAX+1);
        if(randVal < ratio)
            trainSet.data.push_back(growPos.data[i]);
        else
            testSet.data.push_back(growPos.data[i]);
    }
    
    for(int i = 0; i < growNeg.data.size(); i++)
    {
        randVal = (double)rand() / ((double)RAND_MAX+1);
        if(randVal < ratio)
            trainSet.data.push_back(growNeg.data[i]);
        else
            testSet.data.push_back(growNeg.data[i]);
    }
    
    train_test[0] = trainSet;
    train_test[1] = testSet;
    return train_test;
}

DataSet DataSet::getDemocrats()
{
    DataSet demos;
    
    for(int i = 0; i < data.size(); i++)
    {
        if(data[i].isDemocrat)
            demos.data.push_back(data[i]);
    }
    return demos;
}

DataSet DataSet::getRepublicans()
{
    DataSet repubs;
    for(int i = 0; i < data.size(); i++)
    {
        if(!data[i].isDemocrat)
            repubs.data.push_back(data[i]);
    }
    
    return repubs;
}


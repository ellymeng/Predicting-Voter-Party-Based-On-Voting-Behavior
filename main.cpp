//
//  main.cpp
//  P5
//
//  Created by Shi Yuan Meng on 12/6/17.
//  Copyright © 2017 Elly Meng. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "RuleSet.h"
#include "Example.h"
#include "DataSet.h"
#include "Rule.h"

// growPos = democrat examples
// growNeg = republican examples


// for each condition in rule, test against each of the 16 conditions of each example in dataset (stored in observation vector)
void removeExamples(DataSet &dataset, Rule rule)
{
//    DataSet updatedSet = dataset;
    
    for(int ex = 0; ex < dataset.data.size(); ex++)
    {
        if(rule.match(dataset.data[ex]))
            dataset.data.erase(dataset.data.begin()+ex);
    }
    
//    return &updatedSet;
}


// greedy: repeatedly adds a condition that maximizes FOIL's information gain criterion
// until the rule covers no negative examples from the growing dataset growNeg (information gain becomes 0)
// propositional version of FOIL
double gainScore(Rule r0, Rule r1, DataSet growPos, DataSet growNeg)
{
    double gval = 0.0;
//    cout << "size of growpos, growneg" << growPos.data.size() << " " << growNeg.data.size() << endl;
    int p0 = r0.countMatches(growPos); // num democrats examples covered by r0
    int n0 = r0.countMatches(growNeg); // num republicans examples covered by r0
    int p1 = r1.countMatches(growPos); // num democrats covered by r1
    int n1 = r1.countMatches(growNeg); // num republicans exammples covered by r1
    
//    cout << "gainscore variables: " << p0 << " " << n0 << " " << p1 << " " << n1 << endl;
    
    gval = p1*(log2((p1+1.0)/(p1+n1+1.0)) - log2((p0+1.0)/(p0+n0+1.0)));
    
    return gval;
}


Rule growRule(DataSet growPos, DataSet growNeg)
{
    cout << "inside growRule(): " << endl;
    Condition c;
    
    double gScore;
    
    Rule r0; // original rule
    c.attribute = 0;
    c.vote = 0;
    
    
    while(r0.countMatches(growNeg) != 0)
    {
        cout << "number of conditions in r0: " << r0.conditions.size() << endl;
        cout << "examples covered by r0: " << r0.countMatches(growNeg) << endl;
        Condition newCondition, toAppend;
        double maxGScore = -INFINITY; // reset for each new attribute
        cout << " ------beginning while loop---------------" << endl;
    

        
        for(int i = 0; i < 16; i++)
        {
            newCondition.attribute = i;
            
            // find condition that maximizes gainScore
            for(int v = 0; v < 3; v++)
            {
                Rule r1;
                r1.conditions = r0.conditions;
                newCondition.vote = v;
                
                // make sure condition is not already in rule
                bool flag = true;
                for(Condition cond : r0.conditions)
                {
                    
                    if(cond.attribute == i && cond.vote == v)
                    {
                            flag = false;
                    }
                }
                if(flag)
                {
                    cout << "newcondition: " << newCondition.attribute << " " << newCondition.vote << endl;
                    r1.conditions.push_back(newCondition); // temp condition
                    
                    gScore = gainScore(r0, r1,growPos,growNeg);
                    cout << "gainScore: " << gScore << endl;
                    
                    if(gScore > maxGScore)
                    {
                        
                        maxGScore = gScore;
                        toAppend.attribute = newCondition.attribute;
                        toAppend.vote = newCondition.vote;
                        cout << "toAppend: " << toAppend.attribute << " " << toAppend.vote << endl;
                    }
                }
            }
            
        } // end for
        
        cout << "appending to r0: " << toAppend.attribute << " " << toAppend.vote << endl;
        r0.conditions.push_back(toAppend);
        
        for(Condition c: r0.conditions)
            cout << c.attribute << ", " << c.vote << " ^ ";
        cout << endl;
//        
//        cout << "###############printing growNeg: " << endl;
//        for(int i = 0; i < growPos.data.size(); i++)
//        {
//            if(r0.match(growPos.data[i]))
//                for(int a = 0; a < 16; a++)
//                    cout << growPos.data[i].observation[a].attribute << " " << growPos.data[i].observation[a].vote << endl;
//        }
        
    }
    return r0;
}

// TODO
double accuracy(vector<Condition> rule)
{
    double acc = 0.0;
    return acc;
}


// produces one rule at a time and eliminates all examples covered by that rule
// Stops when no positive examples left

RuleSet IREP(DataSet D)
{
    cout << "inside IREP() " << endl;
    DataSet growPos = D.getDemocrats();
    DataSet growNeg = D.getRepublicans();
    
    cout << "size of growPos: " << growPos.data.size() << endl;
    cout << "size of growNeg: " << growNeg.data.size() << endl;
    
    RuleSet ruleSet;
    
    while(!growPos.data.empty())
    {
        Rule rule = growRule(growPos, growNeg);

//        if(rule.getAccuracy(growPos, growNeg) <= 0.5)
//            return ruleSet;
//        else
//        {
//            cout << "size of growPos before removeExamples(): " << growPos.data.size() << endl;
//            ruleSet.rules.push_back(rule);
//             cout << "size of ruleSet: " << ruleSet.rules.size() << endl;
//            removeExamples(growPos,rule);
//            cout << "size of growPos after removeExamples(): " << growPos.data.size() << endl;
//        }
        
    }
    return ruleSet;
}


ifstream loadFile(string fileName) {
    
    ifstream fin;
    fin.open(fileName);
    if(fin.fail())
        cout << "Error opening file." << endl;
    else
        cout << "File opened successfully!" << endl << endl;
    
    return fin;
}


int main(int argc, const char * argv[]) {
    
    string fileName = argv[1];
    ifstream fin = loadFile(fileName);
    string line;
    int lineCount = 0;
    DataSet D;
    Condition c;
    
    // each person = an example with 16 attributes
    while (fin.peek()!='\n')
    {
        getline(fin, line);
        line.erase(remove( line.begin(), line.end(), ' ' ), line.end() );
        Example e;
        e.isDemocrat = e.isPositive = true;
        for(int i = 0; i < 16; i++)
        {
            c.attribute = i;
            if(line[i] == 'y')
                c.vote = 1;
            else if(line[i] == 'n')
                c.vote = 0;
            else
                c.vote = 2;
            
            e.observation.push_back(c);
        }
        D.data.push_back(e);
    }
    
//    cout << "size of D.data: " << D.data.size() << endl;
    
    
    getline(fin, line); // step over empty line between demo and repub
    
    lineCount = 0;
    
    while (!fin.eof())
    {
        getline(fin, line);
        Example e;
        e.isDemocrat = e.isPositive = false;
        for(int i = 0; i < line.size(); i++)
        {
            Condition c;
            c.attribute = i;
            if(line[i] == 'y')
                c.vote = 1;
            else if(line[i] == 'n')
                c.vote = 0;
            else
                c.vote = 2;
            
            e.observation.push_back(c);
        }
        
        D.data.push_back(e);
    }
//        cout << "size of D.data: " << D.data.size() << endl; // 435

    srand(int(time(0))); // used for holdoutSplit
    RuleSet rules = IREP(D);
    
    Condition cond;
    cond.attribute = 3;
    cond.vote = 1;
    Rule r1;
    r1.conditions.push_back(cond);
    
    vector<DataSet> train_test;
   
    //    for(int i = 0; i < 5; i ++)
//    {
    DataSet growPos = D.getDemocrats();
    DataSet growNeg = D.getRepublicans();
    
    train_test = D.holdoutSplit(growPos, growNeg, 0.75); // train_test[0] = train, train_test[1] = test
    cout << "size of train_test: " << train_test.size() << endl;
    RuleSet ruleSet = IREP(train_test[0]);
    cout << "size of rules: " << ruleSet.rules.size() << endl;
//}
    
    // end testing ############################################################################
    
    

    // You're actually printing the average accuracy after completing five applications (?) of the hold-out method.
    // find overall accuracy of ruleSet:
//    int acc = 0;
//    for(int i = 0; i < ruleSet.rules.size(); i++)
//    {
//        acc += ruleSet.rules[i].match(D);
//    }
//    
//    int avgAcc = acc/ruleSet.rules.size();
//    
//    cout << "accuracy of ruleSet: " << avgAcc << endl;
    
    // ----------------------------------?
//        Performance performance = rules.eval(test);
//        cout << "accuracy: " << performance.getAccuracy();

//    }
    
    return 0;
}

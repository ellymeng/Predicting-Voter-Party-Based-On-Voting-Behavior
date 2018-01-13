# Predicting Party of Voter Based on Voting Behavior
This project implements the machine learning concept of rule induction to predict whether a voter is a Democrat or a Republican based on votes casted on past policies. Data from the 1984 Congressional Voting Record was used, and can be found at http://archive.ics.uci.edu/ml/datasets/Congressional+Voting+Records. 


The hold-out method was used to evaluate the learned rules, which involves selecting a random set of the original examples (~75%) as a training set and using the remaining examples (~25%) as a testing set. The training set serves as input to the IREP (Incremental Reduced Error Pruning) function. Once the program produces a set of rules, it evaluates the rules on the examples of the test set.

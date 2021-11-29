# E19CSE216_Automata Dark Knights

## For code 1 you have to give input like this :- 
Enter the no. of states: 4  
  Enter the matrix of states & outputs for different inputs:  
  1 3 0 2 0  
  2 1 1 4 0  
  3 2 1 1 1  
  4 4 1 3 0  
  
You will get output like this :-   
  The divisions of the state will be:  
  1 1  
  2 2  
  3 1  
  4 2  
  
  Total new states will be 6  
  The new table is:  
  
  1 3 0 20 0  
  20 1 1 40 0  
  21 1 1 40 0  
  3 21 1 1 1  
  40 41 1 3 0  
  41 41 1 3 0  
  
  The moore table is:  
  s 3 20 0  
  1 3 20 1  
  20 1 40 0  
  21 1 40 1  
  3 21 1 0  
  40 41 3 0  
  41 41 3 1  
    
## For code 2 you have to give input like this :-  
Please provide the name of the file where you would like to read the state table from (without extension): inp  
Please provide the name of the file where you would like to read the inputs from (without extension): inp1  
Please provide the name of the file where you would like to write the solution to (without extension): out  
  
You will get output like this :-    
Solution:  
01 11 01 00          A/1    
01 11 01          C/0    
11 10 11 11          D/-    
00 11 10 00          B/1  

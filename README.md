# FinSimProject

The Financial Simulation is a simulation between a financially literate person and a not financially literate person. The simulation lasts for forty years and returns an array of the net worth of each person in each of the forty years. 

The program has many limitations. The simulation has set amount of money that each person earns over time which is not realistic as the older you get the more you make. There is no calculation of inflation, so all numbers are nominal. Additionally, the FL has much more money but to access any of the money they should have to pay capital gains taxes which NFL would not have to pay as much.

Make sure that you that you have the H file and C file in the same folder. Cd to that folder. Then type in the following code:

$ gcc -o FinSim  FinancialSimulation.c
./FInSim

This will create 2 output files output_fl.txt and output_nfl.txt where aach year will be its own line with the amount of net worth in that year. 


Extra Credit: I created a net worth function that calculated the equity the person has in their home  since their home is an asset and owning a $210,000 house is an asset both have access to.



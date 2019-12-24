The program counts the total number of transactions and keep track of their cumulative transaction times and waiting
times. These statistics are sufficient to compute the average transaction times and the average waiting time after the last
event has been processed.

Input


The program uses an input text file of arrival times and transaction times. The filename of this input text file will be
provided by the user. Each line of the file contains the arrival time and required transaction time for a customer.



Sample Input

The following is the sample input:

        1 5
        2 5
        4 5
        20 5
        22 5
        24 5
        26 5
        28 5
        30 5
        88 3




Output

The program displays a trace of the events executed and a summary of the computed statistics (the total number of
transactions processed, the average transaction time, and the average wait time (the average time spent waiting in line).



Sample Output


For the sample input given above, the program produces the following output.

        Simulation Begins
        Processing arrival event at time:   1   5
        Processing arrival event at time:   2   5
        Processing arrival event at time:   4   5
        Processing departure event at time: 6
        Processing departure event at time: 11
        Processing departure event at time: 16
        Processing arrival event at time:   20  5
        Processing arrival event at time:   22  5
        Processing arrival event at time:   24  5    
        Processing departure event at time: 25
        Processing arrival event at time:   26  5
        Processing arrival event at time:   28  5
        Processing arrival event at time:   30  5
        Processing departure event at time: 30
        Processing departure event at time: 35
        Processing departure event at time: 40
        Processing departure event at time: 45
        Processing departure event at time: 50
        Processing arrival event at time:   88  3
        Processing departure event at time: 91
        Simulation Ends
        
        Simulation Statistics
        
        Number of transactions processed: 10
                Average transaction time: 4.80
                       Average wait time: 5.60

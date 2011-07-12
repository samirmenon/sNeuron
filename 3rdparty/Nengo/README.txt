MatrixMultiplication Codes:

init_multiplication.py ->  Performs matrix*matrix

command to run in a script console:
>>run init_multiplication.py
>>init_multiplication(3,100,0.1) //(order,neurons,tauPSC)

**************************************************************
init_multiplication2.py -> matrix*vector

command to run in a script console:
>>run init_multiplication2.py
>>init_multiplication(3,100,0.1)//(order,neurons,tauPSC)

*********************************************************************
init_multiplication4.py -> vector*matrix

command to run in a script console:
>>run init_multiplication4.py
>>init_multiplication(3,100,0.1)//(order,neurons,tauPSC)

*************************************************************************
init_multiplication5.py -> vector*vector

command to run in a script console:
>>run init_multiplication5.py
>>init_multiplication(3,100,0.1)//(order,neurons,tauPSC)
*******************************************************************************************
init_multiplication6.py -> vector*matrix*matrix*vector

command to run in a script console:
>>run init_multiplication6.py
>>init_multiplication3(3,100,0.1)//(order,neurons,tauPSC)
>>init_multiplication1(3,100,0.1)//(order,neurons,tauPSC)
>>init_multiplication2(3,100,0.1)//(order,neurons,tauPSC)
 

Add probe to rZ 

***************************************************************
init_random.py
Can multiply any order of matrices. inputs are random!

*********************************************************

Always remember to clear all node files and everything before you probe a new network, 
or the data will not be correct.
**********************************************************

Exported files are saved in Documents by default!
__________________________________________________________________________
Analysis: 

All the data generated for understanding Nengo software and effect of various parameters on the output in it. 

3 files present:
Meeting1.pdf
Meeting2.pdf
VaryinRadius_and_Rate_for_1simulation.pdf
________________________________________________________________

Nengo_Algorithm:

Has "algorithm.txt"
Contains full detailed version of algorithm that Nengo uses. 

__________________________________________________________________


Matlab:

All matlab plots.
Just run in matlab using the file name.


______________________________________________________________________

AutomatedSimulation_Scripts:

Has all the files to create network, simulate and export data to ".mat" files. Fully automated.

vector_pool.py -> Multiplies a vector(2X1) by vector(1X2) using 2 pools. 1 pool for each vector. Varies the phase differences to analyse its effect on output
vector_pool_rad.py -> Multiplies a vector(2X1) by vector(1X2) using 2 pools. 1 pool for each vector. Varies Radius to analyse its effect on output.

vector_1pool.py -> Multiplies a vector(2X1) by vector(1X2) using 1 big pools. Varies the phase differences to analyse its effect on output
vector_1pool_rad.py -> Multiplies a vector(2X1) by vector(1X2) using just 1 big pool. Varies Radius to analyse its effect on output.

command to run in a script console:
>>run main.py

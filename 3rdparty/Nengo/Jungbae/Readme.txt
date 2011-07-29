In Chronological order.



2DOFchangetrajectory, sohn_global_time: included together, they run 2 DOF arm control in spiking mode and various target trajectory creation. Can also export csv results after the trial for matlab plots.

neurogridAmatrixjvi: matlab file for generating the mass matrix using symbolic matrix calculation. Also serves as verification against srishti's implementation of A matrix network.


3DOFspike.py, test3.py: This is a working implementation of joint space dynamic control in spiking mode. A matrix is implemented separately in test3.py.
In simulation, the limbs are commanded to form 90 degrees from local horizontal reference within 4~5 seconds.
			

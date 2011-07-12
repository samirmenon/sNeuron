from ca.nengo.model import *
from ca.nengo.model.impl import *
from ca.nengo.model.nef.impl import *
from ca.nengo.math.impl import *
from ca.nengo.io import *
from java.io import *

#has just one pool of 400 neurons
# Create a network and add it to the world
def pool1_rad(val,w):
	for trial in range(1,4):
		for z in range(1,5):
			n=z*100;
 			b=[1,2,10,17];
			for i in range(0,4):
				#New network
				network=NetworkImpl()
				network.name="Multiplier"+str(b[i])+str(n);
				w.add(network)
				#specify all parameters for pool
				ef=NEFEnsembleFactoryImpl()
				ef.nodeFactory.tauRC=0.02
				ef.nodeFactory.tauRef=0.002
				ef.nodeFactory.maxRate=IndicatorPDF(100,200)
				ef.nodeFactory.intercept=IndicatorPDF(-1,1)

				#Make a pool with the above parameters
				a=ef.make("A",n,4)
				a.setRadii([b[i],b[i],b[i],b[i]]);
				network.addNode(a);

				#input functions added
				inputA=FunctionInput("InputA", [ConstantFunction(1,2.0*val/3.0)],Units.UNK)
				network.addNode(inputA);
				inputB=FunctionInput("InputB",[ConstantFunction(1,1)],Units.UNK)
				network.addNode(inputB);
				inputC=FunctionInput("InputC",[ConstantFunction(1,1.0*val/3.0)],Units.UNK)
				network.addNode(inputC);

				#Add terminations
				a.addDecodedTermination("a11",[[1.0],[ 0.0],[0.0],[0.0]],0.001,False)
				a.addDecodedTermination("a12",[[0.0],[ 1.0],[0.0],[0.0]],0.001,False)
				a.addDecodedTermination("b11",[[0.0],[0.0],[1.0],[ 0.0]],0.001,False)
				a.addDecodedTermination("b21",[[0.0],[0.0],[0.0],[ 1.0]],0.001,False)

				#Add projections
				network.addProjection(inputB.getOrigin('origin'), a.getTermination("a11"))
				network.addProjection(inputC.getOrigin('origin'), a.getTermination("a12"))
				network.addProjection(inputA.getOrigin('origin'), a.getTermination("b11"))
				network.addProjection(inputB.getOrigin('origin'), a.getTermination("b21"))
				interpreter=DefaultFunctionInterpreter()
				
				#specify the output function
				a.addDecodedOrigin("r1",[interpreter.parse("x0*x2+x1*x3",4)],'AXON')				
				network.simulator.addProbe("a",a,"r1",True);	#Add probe
				network.simulator.run(0.0,2.0,1.0E-4);		#run the simulator
				##Export to matlab	
				me=MatlabExporter();
				me.add("data",network.simulator.getProbes()[0].getData());
				f = open('C:\\Users\\Srish\\Desktop\\NewestSimulations\\1pool_Radius\\'+'Value'+str(val)+'\\Trial'+str(trial)+'\\r'+str(b[i])+str(n)+'.mat','w');	 
				me.write(File('C:\\Users\\Srish\\Desktop\\NewestSimulations\\1pool_Radius\\'+'Value'+str(val)+'\\Trial'+str(trial)+'\\r'+str(b[i])+str(n)+'.mat'));
				w.remove(network);
    

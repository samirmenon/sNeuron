from ca.nengo.model import *
from ca.nengo.model.impl import *
from ca.nengo.model.nef.impl import *
from ca.nengo.math.impl import *
from java.io import *

from ca.nengo.io import *

# Create a network and add it to the world

def pool2_rad(val,w):
	for trial in range(1,6):
		for z in range(1,5):
			n=z*100;
			arr=[1,2,10,17];
			for i in range(0,4):
				
				network=NetworkImpl()
				network.name="Multiplier"+str(arr[i])+str(n);
				w.add(network)
				# Configure the neuron parameters
				ef=NEFEnsembleFactoryImpl()
				ef.nodeFactory.tauRC=0.02
				ef.nodeFactory.tauRef=0.002
				ef.nodeFactory.maxRate=IndicatorPDF(100,200)
				ef.nodeFactory.intercept=IndicatorPDF(-1,1)
				# Create input neural ensembles
				a=ef.make("A",n,2)
				a.setRadii([(2.0*arr[i])/3.0,(2.0*arr[i])/3.0]);
				network.addNode(a)
				b=ef.make("B",n,2)
				b.setRadii([(arr[i])/3.0,(arr[i])/3.0])
				network.addNode(b)

				#Add input functions
				inputA=FunctionInput("InputA", [ConstantFunction(1,2.0*val/3.0)],Units.UNK)
				network.addNode(inputA);
				inputB=FunctionInput("InputB",[ConstantFunction(1,1)],Units.UNK)
				network.addNode(inputB);
				inputC=FunctionInput("InputC",[ConstantFunction(1,val/3.0)],Units.UNK)
				network.addNode(inputC);

				#Add terminations to the pool
				a.addDecodedTermination("a11",[[1.0],[ 0.0]],0.05,False)
				a.addDecodedTermination("a12",[[0.0],[ 1.0]],0.05,False)
				b.addDecodedTermination("b11",[[1.0],[ 0.0]],0.05,False)
				b.addDecodedTermination("b21",[[0.0],[ 1.0]],0.05,False)

				#Add projections from inputs to the pools
				network.addProjection(inputB.getOrigin('origin'), a.getTermination("a11"))
				network.addProjection(inputC.getOrigin('origin'), a.getTermination("a12"))
				network.addProjection(inputA.getOrigin('origin'), b.getTermination("b11"))
				network.addProjection(inputB.getOrigin('origin'), b.getTermination("b21"))
			
				#output pool
				combined = ef.make("combined",2*n,4);
				combined.setRadii([arr[i],arr[i],arr[i],arr[i]])
				network.addNode(combined);
				combined.addDecodedTermination("A",[[1.0, 0.0],  [0.0, 1.0],[0.0, 0.0], [ 0.0, 0.0]],0.05,False);
				combined.addDecodedTermination("B",[[0.0, 0.0],  [0.0, 0.0], [1.0, 0.0],[0.0, 1.0]],0.05,False);
				network.addProjection(a.getOrigin('X'),combined.getTermination("A"))
				network.addProjection(b.getOrigin('X'),combined.getTermination("B"))
				interpreter=DefaultFunctionInterpreter()
				combined.addDecodedOrigin("r11",[interpreter.parse("x0*x2+x1*x3",4)],'AXON')
				network.simulator.addProbe("combined",combined,"r11",True) #add probe
				network.simulator.run(0.0,2.0,5.0E-4);   #run
				#Export
				me=MatlabExporter();
				me.add("data",network.simulator.getProbes()[0].getData());
				f = open('C:\\Users\\Srish\\Desktop\\NewestSimulations\\2pool_Radius\\'+'Value'+str(val)+'\\Trial'+str(trial)+'\\r'+str(arr[i])+str(n)+'.mat','w');	 
				me.write(File('C:\\Users\\Srish\\Desktop\\NewestSimulations\\2pool_Radius\\'+'Value'+str(val)+'\\Trial'+str(trial)+'\\r'+str(arr[i])+str(n)+'.mat'));
				w.remove(network);

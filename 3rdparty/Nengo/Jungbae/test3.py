
from java.io import *
from ca.nengo.model.impl import *
from ca.nengo.model import *
from ca.nengo.model.nef.impl import *
from ca.nengo.model.neuron.impl import *
from ca.nengo.model.neuron import *
from ca.nengo.math.impl import *
from ca.nengo.model.plasticity.impl import *
from ca.nengo.util import *
from ca.nengo.plot import *
from ca.nengo.io import *

from math import * 
import java




def setupA():    

    

	
	
	


	m1=FunctionInput('m1',[ConstantFunction(1,0.5)],Units.UNK);
	m2=FunctionInput('m2',[ConstantFunction(1,0.1)],Units.UNK);
	m3=FunctionInput('m3',[ConstantFunction(1,0.1)],Units.UNK);	
	l1=FunctionInput('l1',[ConstantFunction(1,0.7)],Units.UNK);
	l2=FunctionInput('l2',[ConstantFunction(1,0.75)],Units.UNK);
	l3=FunctionInput('l3',[ConstantFunction(1,0.75)],Units.UNK);

	Iz1=FunctionInput('Iz1',[ConstantFunction(1,0.020833)],Units.UNK);
	Iz2=FunctionInput('Iz2',[ConstantFunction(1,0.004771)],Units.UNK);
	Iz3=FunctionInput('Iz3',[ConstantFunction(1,0.004771)],Units.UNK);




	networkA.addNode(m1);
	networkA.addNode(m2);
	networkA.addNode(m3);
	networkA.addNode(l1);
	networkA.addNode(l2);
	networkA.addNode(l3);
	networkA.addNode(Iz1);
	networkA.addNode(Iz2);
	networkA.addNode(Iz3);
	#networkA.addNode(room);

	ef = NEFEnsembleFactoryImpl()
	ef.nodeFactory=LIFNeuronFactory(tauRC=.020, tauRef=.001, maxRate=IndicatorPDF(200,400), intercept=IndicatorPDF(-1,1))
	a1=ef.make("A1",300,3);#300
	a1.addDecodedTermination("input m1",[[1.0],[0.0],[0.0]],0.001,False);
	a1.addDecodedTermination("input l1",[[0.0],[1.0],[0.0]],0.001,False);
	a1.addDecodedTermination("input Iz1",[[0.0],[0.0],[1.0]],0.001,False);
	
	networkA.addProjection(m1.getOrigin('origin'), a1.getTermination("input m1"));
	networkA.addProjection(l1.getOrigin('origin'), a1.getTermination("input l1"));
	networkA.addProjection(Iz1.getOrigin('origin'), a1.getTermination("input Iz1"));

	interpreter=DefaultFunctionInterpreter();
	a1.addDecodedOrigin("o1",[interpreter.parse("0.5*0.7*0.7+0.020833",3)],"AXON");

	a1.addDecodedOrigin("o2",[interpreter.parse("0",3)],'AXON');
	a1.addDecodedOrigin("o3",[interpreter.parse("0",3)],'AXON');
	a1.addDecodedOrigin("o4",[interpreter.parse("0",3)],'AXON');
	a1.addDecodedOrigin("o5",[interpreter.parse("0",3)],'AXON');
	a1.addDecodedOrigin("o6",[interpreter.parse("0",3)],'AXON');
	a1.addDecodedOrigin("o7",[interpreter.parse("0",3)],'AXON');
	a1.addDecodedOrigin("o8",[interpreter.parse("0",3)],'AXON');
	a1.addDecodedOrigin("o9",[interpreter.parse("0",3)],'AXON');
	networkA.addNode(a1);
	

	a2=ef.make("A2",200,1);#200
	a2.setRadii([1.0]);
	a2.addDecodedTermination("input q2",[[1.0]],0.01,False);



	#networkA.addProjection(room.getOrigin('origin'), a2.getTermination("input q2"));	#Connect this with room-> exposed as Q2

	interpreter=DefaultFunctionInterpreter();

	a2.addDecodedOrigin("o1",[interpreter.parse("0.1*(0.7*0.7+0.75*0.75+2*0.7*0.75*cos(x0))+0.004771",1)],"AXON");
	a2.addDecodedOrigin("o2",[interpreter.parse("0.1*(0.75*0.75+0.7*0.75*cos(x0))+0.004771",1)],'AXON');
	a2.addDecodedOrigin("o3",[interpreter.parse("0",1)],'AXON');

	a2.addDecodedOrigin("o4",[interpreter.parse("0.1*(0.75*0.75+0.7*0.75*cos(x0))+0.004771",1)],'AXON');
	a2.addDecodedOrigin("o5",[interpreter.parse("0.1*0.75*0.75+0.004771",1)],'AXON');
	a2.addDecodedOrigin("o6",[interpreter.parse("0",1)],'AXON');
	a2.addDecodedOrigin("o7",[interpreter.parse("0",1)],'AXON');
	a2.addDecodedOrigin("o8",[interpreter.parse("0",1)],'AXON');
	a2.addDecodedOrigin("o9",[interpreter.parse("0",1)],'AXON');

	networkA.addNode(a2);



	a3=ef.make("A3",400,3); #400
	
	a3.addDecodedTermination("input q1",[[1.0],[0.0],[0.0]],0.01,False);        # x4 = q1
	a3.addDecodedTermination("input q2",[[0.0],[1.0],[0.0]],0.01,False);         #x5 = q2
	a3.addDecodedTermination("input q3",[[0.0],[0.0],[1.0]],0.01,False);         #x6 = q3
           	
	networkA.addNode(a3);






	a3.addDecodedOrigin("o1",[interpreter.parse("0.1*(-0.7*sin(x0)-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))*(-0.7*sin(x0)-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))+0.1*(0.7*cos(x0)+0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))*(0.7*cos(x0)+0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))+0.004771 ",3)],"AXON");

	a3.addDecodedOrigin("o2",[interpreter.parse("0.1*(-0.7*sin(x0)-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))*(-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))+0.1*(0.7*cos(x0)+0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))*(0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))+0.004771",3)],"AXON");


	a3.addDecodedOrigin("o3",[interpreter.parse("-0.1*(-0.7*sin(x0)-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))*0.75*sin(x0+x1+x2)+0.1*(0.7*cos(x0)+0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))*0.75*cos(x0+x1+x2)+0.004771",3)],"AXON");

	a3.addDecodedOrigin("o4",[interpreter.parse("0.1*(-0.7*sin(x0)-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))*(-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))+0.1*(0.7*cos(x0)+0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))*(0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))+0.004771",3)],"AXON");


	a3.addDecodedOrigin("o5",[interpreter.parse("0.1*(-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))*(-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))+0.1*(0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))*(0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))+0.004771",3)],"AXON");

	a3.addDecodedOrigin("o6",[interpreter.parse("-0.1*(-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))*0.75*sin(x0+x1+x2)+0.1*(0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))*0.75*cos(x0+x1+x2)+0.004771",3)],"AXON");

	a3.addDecodedOrigin("o7",[interpreter.parse("-0.1*(-0.7*sin(x0)-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))*0.75*sin(x0+x1+x2)+0.1*(0.7*cos(x0)+0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))*0.75*cos(x0+x1+x2)+0.004771",3)],"AXON");

	a3.addDecodedOrigin("o8",[interpreter.parse("-0.1*(-0.75*sin(x0+x1)-0.75*sin(x0+x1+x2))*0.75*sin(x0+x1+x2)+0.1*(0.75*cos(x0+x1)+0.75*cos(x0+x1+x2))*0.75*cos(x0+x1+x2)+0.004771",3)],"AXON");

	a3.addDecodedOrigin("o9",[interpreter.parse("0.1*0.75*0.75*sin(x0+x1+x2)*sin(x0+x1+x2)+0.1*0.75*0.75*cos(x0+x1+x2)*cos(x0+x1+x2)+0.004771",3)],"AXON");


	fa=ef.make("Final_A",900,9); #900
	fa.addDecodedTermination("d1_1",[[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d1_2",[[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d1_3",[[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	
	fa.addDecodedTermination("d2_1",[[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d2_2",[[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d2_3",[[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);

	fa.addDecodedTermination("d3_1",[[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d3_2",[[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d3_3",[[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);

	fa.addDecodedTermination("d4_1",[[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d4_2",[[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d4_3",[[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);

	fa.addDecodedTermination("d5_1",[[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d5_2",[[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d5_3",[[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0],[0.0]],0.01,False);

	fa.addDecodedTermination("d6_1",[[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d6_2",[[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d6_3",[[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0],[0.0]],0.01,False);

	fa.addDecodedTermination("d7_1",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d7_2",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d7_3",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0],[0.0]],0.01,False);

	fa.addDecodedTermination("d8_1",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d8_2",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0]],0.01,False);
	fa.addDecodedTermination("d8_3",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0],[0.0]],0.01,False);

	fa.addDecodedTermination("d9_1",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0]],0.01,False);
	fa.addDecodedTermination("d9_2",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0]],0.01,False);
	fa.addDecodedTermination("d9_3",[[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[0.0],[1.0]],0.01,False);
	

	fa.addDecodedOrigin("o1",[interpreter.parse("x0",9)],"AXON");
	fa.addDecodedOrigin("o2",[interpreter.parse("x1",9)],"AXON");
	fa.addDecodedOrigin("o3",[interpreter.parse("x2",9)],"AXON");
	fa.addDecodedOrigin("o4",[interpreter.parse("x3",9)],"AXON");
	fa.addDecodedOrigin("o5",[interpreter.parse("x4",9)],"AXON");
	fa.addDecodedOrigin("o6",[interpreter.parse("x5",9)],"AXON");
	fa.addDecodedOrigin("o7",[interpreter.parse("x6",9)],"AXON");
	fa.addDecodedOrigin("o8",[interpreter.parse("x7",9)],"AXON");
	fa.addDecodedOrigin("o9",[interpreter.parse("x8",9)],"AXON");

	networkA.addNode(fa);

	networkA.addProjection(a1.getOrigin('o1'), fa.getTermination("d1_1"));
	networkA.addProjection(a2.getOrigin('o1'), fa.getTermination("d1_2"));
	networkA.addProjection(a3.getOrigin('o1'), fa.getTermination("d1_3"));

	networkA.addProjection(a1.getOrigin('o2'), fa.getTermination("d2_1"));
	networkA.addProjection(a2.getOrigin('o2'), fa.getTermination("d2_2"));
	networkA.addProjection(a3.getOrigin('o2'), fa.getTermination("d2_3"));

	networkA.addProjection(a1.getOrigin('o3'), fa.getTermination("d3_1"));
	networkA.addProjection(a2.getOrigin('o3'), fa.getTermination("d3_2"));
	networkA.addProjection(a3.getOrigin('o3'), fa.getTermination("d3_3"));

	networkA.addProjection(a1.getOrigin('o4'), fa.getTermination("d4_1"));
	networkA.addProjection(a2.getOrigin('o4'), fa.getTermination("d4_2"));
	networkA.addProjection(a3.getOrigin('o4'), fa.getTermination("d4_3"));

	networkA.addProjection(a1.getOrigin('o5'), fa.getTermination("d5_1"));
	networkA.addProjection(a2.getOrigin('o5'), fa.getTermination("d5_2"));
	networkA.addProjection(a3.getOrigin('o5'), fa.getTermination("d5_3"));

	networkA.addProjection(a1.getOrigin('o6'), fa.getTermination("d6_1"));
	networkA.addProjection(a2.getOrigin('o6'), fa.getTermination("d6_2"));
	networkA.addProjection(a3.getOrigin('o6'), fa.getTermination("d6_3"));

	networkA.addProjection(a1.getOrigin('o7'), fa.getTermination("d7_1"));
	networkA.addProjection(a2.getOrigin('o7'), fa.getTermination("d7_2"));
	networkA.addProjection(a3.getOrigin('o7'), fa.getTermination("d7_3"));

	networkA.addProjection(a1.getOrigin('o8'), fa.getTermination("d8_1"));
	networkA.addProjection(a2.getOrigin('o8'), fa.getTermination("d8_2"));
	networkA.addProjection(a3.getOrigin('o8'), fa.getTermination("d8_3"));

	networkA.addProjection(a1.getOrigin('o9'), fa.getTermination("d9_1"));
	networkA.addProjection(a2.getOrigin('o9'), fa.getTermination("d9_2"));
	networkA.addProjection(a3.getOrigin('o9'), fa.getTermination("d9_3"));

	networkA.setMode(SimulationMode.DEFAULT) #for debugging only




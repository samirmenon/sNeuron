from __future__ import generators
import sys

import space
reload(space)

dt=0.001
N=1
pstc=0.01

from java.io import *
from ca.nengo.io import *
from ca.nengo.model.impl import *
from ca.nengo.model import *
from ca.nengo.model.nef.impl import *
from ca.nengo.model.neuron.impl import *
from ca.nengo.model.neuron import *
from ca.nengo.math.impl import *
from ca.nengo.model.plasticity.impl import *
from ca.nengo.util import *
from ca.nengo.plot import *

from com.bulletphysics import *
from com.bulletphysics.linearmath import *
from com.bulletphysics.dynamics.constraintsolver import *
from javax.vecmath import Vector3f
from math import * 

#open test3.py first and then open retarded.py

import java
from java.awt import Color

try:
    world.remove(network)
except:
    pass

#sys.path.append('C:\Users\jsohn123\Desktop\NEURAL CONTROLLER\nengo\nengo-1132\REU')


    
network = NetworkImpl()
network.name ='simple arm controller'

#massMult = NetworkImpl()
#massMult.name = 'A*Torque'

#network.addNode(massMult)

import test3

networkA=NetworkImpl();
networkA.name="A_Matrix";
setupA()
network.addNode(networkA)     #just created an A matrix network

#expose the nodes for the q vectors to enter!

networkA.exposeTermination(networkA.getNode('A2').getTermination('input q2'),'Q2')
networkA.exposeTermination(networkA.getNode('A3').getTermination('input q1'),'Q1')
networkA.exposeTermination(networkA.getNode('A3').getTermination('input q2'),'Q2f3')
networkA.exposeTermination(networkA.getNode('A3').getTermination('input q3'),'Q3')

networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o1'),'A1')
networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o2'),'A2')
networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o3'),'A3')
networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o4'),'A4')
networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o5'),'A5')
networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o6'),'A6')
networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o7'),'A7')
networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o8'),'A8')
networkA.exposeOrigin(networkA.getNode('Final_A').getOrigin('o9'),'A9')




ef = NEFEnsembleFactoryImpl()
ef.nodeFactory=LIFNeuronFactory(tauRC=.020, tauRef=.001, maxRate=IndicatorPDF(200,400), intercept=IndicatorPDF(-1,1))


#Set up the A*T network: takes in qvector, qControl. contains A matrix network, multiplies out the A and qControl. out puts 3 control values (decoupled)











# input functions
refShoulder=FunctionInput('ref1',[ConstantFunction(1,pi/2)],Units.UNK)# shoulder angle goal
refElbow=FunctionInput('ref2',[ConstantFunction(1,pi/2)],Units.UNK)# elbow angle goal
refWrist = FunctionInput('ref3',[ConstantFunction(1,pi/2)],Units.UNK)# wrist angle goal

network.addNode(refShoulder)
network.addNode(refElbow)
network.addNode(refWrist)


# neural populations


#massMatrix = ef.make("A",N,3)                 ######kinetic matrix A compensation, takes in q and qdot
pdGain = ef.make("pdGain",300,3)        ##########pd Gain
controlV=ef.make("control signal v",300,3) # calculate 3D q error
controlV.setRadii([1.0,1.0,1.0]);


network.addNode(controlV)
#network.addNode(controlU)

network.addNode(pdGain)         #############
#network.addNode(massMatrix)     ############


# add terminations




pdGain.addDecodedTermination('shoulderError',[[1.7],[0],[0]],pstc,False)         ############      these are P gains!!!!!!! 1.6,1.7
pdGain.addDecodedTermination('elbowError',[[0],[1.7],[0]],pstc,False)               ###########
pdGain.addDecodedTermination('wristError',[[0],[0],[1.7]],pstc,False)              ############

pdGain.addDecodedTermination('shVel',[[-1.2],[0],[0]],pstc,False)         ############      these are D gains!!!!!!! -1.2
pdGain.addDecodedTermination('elVel',[[0],[-1.2],[0]],pstc,False)               ###########
pdGain.addDecodedTermination('wriVel',[[0],[0],[-1.2]],pstc,False)   


controlV.addDecodedTermination('inputCurrent1shoulder',[[-1],[0],[0]],pstc,False)
controlV.addDecodedTermination('inputCurrent2elbow',[[0],[-1],[0]],pstc,False)
controlV.addDecodedTermination('inputCurrent3wrist',[[0],[0],[-1]],pstc,False)
controlV.addDecodedTermination('inputRef1',[[1],[0],[0]],pstc,False)
controlV.addDecodedTermination('inputRef2',[[0],[1],[0]],pstc,False)
controlV.addDecodedTermination('inputRef3',[[0],[0],[1]],pstc,False)

#massMatrix.addDecodedTermination('tStar1',[[1],[0],[0]],pstc,False)
#massMatrix.addDecodedTermination('tStar2',[[0],[1],[0]],pstc,False)
#massMatrix.addDecodedTermination('tStar3',[[0],[0],[1]],pstc,False)


# add origins
interpreter=DefaultFunctionInterpreter()

#controlU.addDecodedOrigin('u1',[interpreter.parse("x0",2)],"AXON")
#controlU.addDecodedOrigin('u2',[interpreter.parse("x1",2)],"AXON")

controlV.addDecodedOrigin('shoulderE',[interpreter.parse("x0",3)],"AXON")
controlV.addDecodedOrigin('elbowE',[interpreter.parse("x1",3)],"AXON")
controlV.addDecodedOrigin('wristE',[interpreter.parse("x2",3)],"AXON")



######pdGain: 
pdGain.addDecodedOrigin('shoulderTorquest',[interpreter.parse("x0",3)],"AXON")                ##############
pdGain.addDecodedOrigin('elbowTorquest',[interpreter.parse("x1",3)],"AXON")	###########
pdGain.addDecodedOrigin('wristTorquest',[interpreter.parse("x2",3)],"AXON")                 #############

# add projections 



network.addProjection(refShoulder.getOrigin('origin'),controlV.getTermination('inputRef1'))
network.addProjection(refElbow.getOrigin('origin'),controlV.getTermination('inputRef2'))
network.addProjection(refWrist.getOrigin('origin'),controlV.getTermination('inputRef3'))

network.addProjection(controlV.getOrigin('shoulderE'),pdGain.getTermination('shoulderError'))
network.addProjection(controlV.getOrigin('elbowE'),pdGain.getTermination('elbowError'))
network.addProjection(controlV.getOrigin('wristE'),pdGain.getTermination('wristError'))




finalControlShsum = ef.make("finalControlS",100,1)
finalControlS1 = ef.make("A11*SH",200,2)
finalControlS2 = ef.make("A12*EL",200,2)
finalControlS3 = ef.make("A13*WR",200,2)


finalControlS1.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlS1.addDecodedTermination('pdshoulder',[[0],[1] ],pstc,False)
finalControlS1.addDecodedOrigin('Shoulder1',[interpreter.parse("x0*x1",2)],"AXON")

finalControlS2.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlS2.addDecodedTermination('pdelbow',[[0],[1] ],pstc,False)
finalControlS2.addDecodedOrigin('Shoulder2',[interpreter.parse("x0*x1",2)],"AXON")

finalControlS3.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlS3.addDecodedTermination('pdwrist',[[0],[1] ],pstc,False)
finalControlS3.addDecodedOrigin('Shoulder3',[interpreter.parse("x0*x1",2)],"AXON")

finalControlShsum.addDecodedTermination('first',[ [1] ],pstc,False)
finalControlShsum.addDecodedTermination('second',[[1] ],pstc,False)
finalControlShsum.addDecodedTermination('third',[[1] ],pstc,False)
finalControlShsum.addDecodedOrigin('SHOULDER',[interpreter.parse("x0",1)],"AXON")





finalControlElsum = ef.make("finalControlE",100,1)
finalControlE1 = ef.make("A21*SH",200,2)
finalControlE2 = ef.make("A22*EL",200,2)
finalControlE3 = ef.make("A23*WR",200,2)


finalControlE1.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlE1.addDecodedTermination('pdshoulder',[[0],[1] ],pstc,False)
finalControlE1.addDecodedOrigin('Elbow1',[interpreter.parse("x0*x1",2)],"AXON")

finalControlE2.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlE2.addDecodedTermination('pdelbow',[[0],[1] ],pstc,False)
finalControlE2.addDecodedOrigin('Elbow2',[interpreter.parse("x0*x1",2)],"AXON")

finalControlE3.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlE3.addDecodedTermination('pdwrist',[[0],[1] ],pstc,False)
finalControlE3.addDecodedOrigin('Elbow3',[interpreter.parse("x0*x1",2)],"AXON")

finalControlElsum.addDecodedTermination('first',[ [1] ],pstc,False)
finalControlElsum.addDecodedTermination('second',[[1] ],pstc,False)
finalControlElsum.addDecodedTermination('third',[[1] ],pstc,False)
finalControlElsum.addDecodedOrigin('ELBOW',[interpreter.parse("x0",1)],"AXON")





finalControlWrsum = ef.make("finalControlW",100,1)
finalControlW1 = ef.make("A31*SH",200,2)
finalControlW2 = ef.make("A32*EL",200,2)
finalControlW3 = ef.make("A33*WR",200,2)


finalControlW1.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlW1.addDecodedTermination('pdshoulder',[[0],[1] ],pstc,False)
finalControlW1.addDecodedOrigin('Wrist1',[interpreter.parse("x0*x1",2)],"AXON")

finalControlW2.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlW2.addDecodedTermination('pdelbow',[[0],[1] ],pstc,False)
finalControlW2.addDecodedOrigin('Wrist2',[interpreter.parse("x0*x1",2)],"AXON")

finalControlW3.addDecodedTermination('massmat1',[ [1],[0] ],pstc,False)
finalControlW3.addDecodedTermination('pdwrist',[[0],[1] ],pstc,False)
finalControlW3.addDecodedOrigin('Wrist3',[interpreter.parse("x0*x1",2)],"AXON")

finalControlWrsum.addDecodedTermination('first',[ [1] ],pstc,False)
finalControlWrsum.addDecodedTermination('second',[[1] ],pstc,False)
finalControlWrsum.addDecodedTermination('third',[[1] ],pstc,False)
finalControlWrsum.addDecodedOrigin('WRIST',[interpreter.parse("x0",1)],"AXON")


network.addNode(finalControlS1)
network.addNode(finalControlS2)
network.addNode(finalControlS3)
network.addNode(finalControlShsum)

network.addNode(finalControlE1)
network.addNode(finalControlE2)
network.addNode(finalControlE3)
network.addNode(finalControlElsum)

network.addNode(finalControlW1)
network.addNode(finalControlW2)
network.addNode(finalControlW3)
network.addNode(finalControlWrsum)

network.addProjection(networkA.getOrigin('A1'),finalControlS1.getTermination('massmat1'))
network.addProjection(networkA.getOrigin('A2'),finalControlS2.getTermination('massmat1'))
network.addProjection(networkA.getOrigin('A3'),finalControlS3.getTermination('massmat1'))

network.addProjection(networkA.getOrigin('A4'),finalControlE1.getTermination('massmat1'))
network.addProjection(networkA.getOrigin('A5'),finalControlE2.getTermination('massmat1'))
network.addProjection(networkA.getOrigin('A6'),finalControlE3.getTermination('massmat1'))

network.addProjection(networkA.getOrigin('A7'),finalControlW1.getTermination('massmat1'))
network.addProjection(networkA.getOrigin('A8'),finalControlW2.getTermination('massmat1'))
network.addProjection(networkA.getOrigin('A9'),finalControlW3.getTermination('massmat1'))

network.addProjection(pdGain.getOrigin('shoulderTorquest'),finalControlS1.getTermination('pdshoulder'))
network.addProjection(pdGain.getOrigin('elbowTorquest'),finalControlS2.getTermination('pdelbow'))
network.addProjection(pdGain.getOrigin('wristTorquest'),finalControlS3.getTermination('pdwrist'))

network.addProjection(pdGain.getOrigin('shoulderTorquest'),finalControlE1.getTermination('pdshoulder'))
network.addProjection(pdGain.getOrigin('elbowTorquest'),finalControlE2.getTermination('pdelbow'))
network.addProjection(pdGain.getOrigin('wristTorquest'),finalControlE3.getTermination('pdwrist'))

network.addProjection(pdGain.getOrigin('shoulderTorquest'),finalControlW1.getTermination('pdshoulder'))
network.addProjection(pdGain.getOrigin('elbowTorquest'),finalControlW2.getTermination('pdelbow'))
network.addProjection(pdGain.getOrigin('wristTorquest'),finalControlW3.getTermination('pdwrist'))

network.addProjection(finalControlS1.getOrigin('Shoulder1'), finalControlShsum.getTermination('first'))
network.addProjection(finalControlS2.getOrigin('Shoulder2'), finalControlShsum.getTermination('second'))
network.addProjection(finalControlS3.getOrigin('Shoulder3'), finalControlShsum.getTermination('third'))

network.addProjection(finalControlE1.getOrigin('Elbow1'), finalControlElsum.getTermination('first'))
network.addProjection(finalControlE2.getOrigin('Elbow2'), finalControlElsum.getTermination('second'))
network.addProjection(finalControlE3.getOrigin('Elbow3'), finalControlElsum.getTermination('third'))

network.addProjection(finalControlW1.getOrigin('Wrist1'), finalControlWrsum.getTermination('first'))
network.addProjection(finalControlW2.getOrigin('Wrist2'), finalControlWrsum.getTermination('second'))
network.addProjection(finalControlW3.getOrigin('Wrist3'), finalControlWrsum.getTermination('third'))


world.add(network)
import ccm

import random
random.seed(11)

from math import pi
from com.threed.jpct import SimpleVector
from com.bulletphysics.linearmath import Transform
from javax.vecmath import Vector3f

class Room(space.Room):
    def __init__(self):
        space.Room.__init__(self,10,10,gravity=0,color=[Color(0xFFFFFF),Color(0xFFFFFF),Color(0xEEEEEE),Color(0xDDDDDD),Color(0xCCCCCC),Color(0xBBBBBB)])
    def start(self):    
        
        self.target=space.Sphere(0.2,mass=1,color=Color(0xFF0000))
        self.add(self.target,0,0,2)
        
        torso=space.Box(0.1,0.1,1.5,mass=100000,draw_as_cylinder=True,color=Color(0x4444FF))
        self.add(torso,0,0,1)
        
        upperarm=space.Box(0.1,0.7,0.1,mass=0.5,draw_as_cylinder=True,color=Color(0x8888FF),overdraw_radius=1.2,overdraw_length=1.2)
        self.add(upperarm,0.7,0.5,2)
        upperarm.add_sphere_at(0,0.5,0,0.1,Color(0x4444FF),self)
        upperarm.add_sphere_at(0,-0.5,0,0.1,Color(0x4444FF),self)
        
        lowerarm=space.Box(0.1,0.75,0.1,mass=0.1,draw_as_cylinder=True,color=Color(0x8888FF),overdraw_radius=1.2,overdraw_length=1.1)
        self.add(lowerarm,0.7,1.5,2)
        lowerarm.add_sphere_at(0,0.5,0,0.1,Color(0x4444FF),self)            ##########

        thirdarm = space.Box(0.1,0.75,0.1,mass=0.1,draw_as_cylinder=True,color=Color(0x8888FF),overdraw_radius=1.2,overdraw_length=1.1)	    ###########
        self.add(thirdarm,0.7,2.5,2) ############

        shoulder=HingeConstraint(torso.physics,upperarm.physics,
                            Vector3f(0.7,0.1,1),Vector3f(0,-0.5,0),
                            Vector3f(0,0,1),Vector3f(0,0,1))
               
        elbow=HingeConstraint(upperarm.physics,lowerarm.physics,
                            Vector3f(0,0.5,0),Vector3f(0,-0.5,0),
                            Vector3f(0,0,1),Vector3f(0,0,1))


        wrist = HingeConstraint(lowerarm.physics,thirdarm.physics,                        
                            Vector3f(0,0.5,0),Vector3f(0,-0.5,0),
                            Vector3f(0,0,1),Vector3f(0,0,1))                #############
                            
        shoulder.setLimit(-pi/2,pi/2+.1)
        elbow.setLimit(-pi,0)
        wrist.setLimit(-pi,0) ###########
        
        self.physics.addConstraint(elbow)
        self.physics.addConstraint(shoulder)
        self.physics.addConstraint(wrist) ##########       

       
        self.sch.add(space.Room.start,args=(self,))
        self.update_neurons()
        self.upperarm=upperarm
        self.lowerarm=lowerarm
        self.thirdarm = thirdarm   ########

        self.shoulder=shoulder
        self.elbow=elbow
        self.wrist = wrist ########       

        self.hinge1=self.shoulder.hingeAngle
        self.hinge2=self.elbow.hingeAngle
        self.hinge3 = self.wrist.hingeAngle    ###############

        self.upperarm.physics.setSleepingThresholds(0,0)
        self.lowerarm.physics.setSleepingThresholds(0,0)
        self.thirdarm.physics.setSleepingThresholds(0,0)  ############
            
    def update_neurons(self):
        while True:
            scale=0.0003
           # m1=finalControlS.getOrigin('finalShoulderControl').getValues().getValues()[0]*scale
            m1 = finalControlShsum.getOrigin('SHOULDER').getValues().getValues()[0]*scale
            m2 = finalControlElsum.getOrigin('ELBOW').getValues().getValues()[0]*scale
            m3 = finalControlWrsum.getOrigin('WRIST').getValues().getValues()[0]*scale
            #m2=finalControlE.getOrigin('finalElbowControl').getValues().getValues()[0]*scale
            #m3 =finalControlW.getOrigin('finalWristControl').getValues().getValues()[0]*scale
            #########    add u3 for wrist here #######

            v1=Vector3f(0,0,0)
            v2=Vector3f(0,0,0)
            v3=Vector3f(0,0,0)	##########
            #java.lang.System.out.println("m1: %f   m2:%f"%(m1,m2))

            self.upperarm.physics.applyTorqueImpulse(Vector3f(0,0,m1))
            self.lowerarm.physics.applyTorqueImpulse(Vector3f(0,0,m2))
            self.thirdarm.physics.applyTorqueImpulse(Vector3f(0,0,m3))      #########


            self.hinge1=-(self.shoulder.hingeAngle-pi/2)
            self.hinge2=-self.elbow.hingeAngle
            self.hinge3 = -self.wrist.hingeAngle   
            #java.lang.System.out.println("angle1: %f   angle2:%f"%(self.hinge1,self.hinge2))   
	
            self.upperarm.physics.getAngularVelocity(v1)
            self.lowerarm.physics.getAngularVelocity(v2)
            self.thirdarm.physics.getAngularVelocity(v3) ##################
            # put bounds on the velocity possible
            if v1.z > 2: self.upperarm.physics.setAngularVelocity(Vector3f(0,0,2))
            if v1.z < -2: self.upperarm.physics.setAngularVelocity(Vector3f(0,0,-2))
            if v2.z > 2: self.lowerarm.physics.setAngularVelocity(Vector3f(0,0,2))
            if v2.z < -2: self.lowerarm.physics.setAngularVelocity(Vector3f(0,0,-2))
            if v3.z > 2: self.thirdarm.physics.setAngularVelocity(Vector3f(0,0,2))         ##############
            if v3.z < -2: self.thirdarm.physics.setAngularVelocity(Vector3f(0,0,-2))    ################



            shouldererror = controlV.getOrigin('shoulderE').getValues().getValues()[0]
            elbowerror = controlV.getOrigin('elbowE').getValues().getValues()[0]
            wristerror = controlV.getOrigin('wristE').getValues().getValues()[0]

            f = open('anyfile.txt',"a");
            f.write( "%f,%f,%f\n" %(shouldererror,elbowerror,wristerror))

            
            self.upperarm.physics.getAngularVelocity(v1)
            self.lowerarm.physics.getAngularVelocity(v2)
            self.thirdarm.physics.getAngularVelocity(v3) ##################
            
            #wt=Transform()
            #wt.setIdentity()
            
            #getting target ball commnad from GUI
           # t1=controlV.getTermination('inputRef1').input
	

            #if t1 is not None:
              #  wt.origin.x=t1.values[0]+0.7
            #else:    
              #  wt.origin.x=0.7
            #t2=controlV.getTermination('inputRef2').input
            #if t2 is not None:
            #    wt.origin.y=t2.values[0]+0.1
            #else:    
            #    wt.origin.y=0.1
            #wt.origin.z=2

           # self.target.physics.motionState.worldTransform=wt
            
            
            self.vel1=v1.z
            self.vel2=v2.z
            self.vel3 = v3.z ####################
	
           
            yield 0.0001
    
r=ccm.nengo.create(Room)
network.addNode(r)

# need to make hinge1, hinge2, vel1, and vel external nodes and hook up the output to the FX matrix
r.exposeOrigin(r.getNode('hinge1').getOrigin('origin'),'shoulderAngle')
r.exposeOrigin(r.getNode('hinge2').getOrigin('origin'),'elbowAngle')
r.exposeOrigin(r.getNode('hinge3').getOrigin('origin'),'wristAngle')		

r.exposeOrigin(r.getNode('vel1').getOrigin('origin'),'shoulderVel')
r.exposeOrigin(r.getNode('vel2').getOrigin('origin'),'elbowVel')
r.exposeOrigin(r.getNode('vel3').getOrigin('origin'),'wristVel')                         

network.addProjection(r.getOrigin('shoulderAngle'),controlV.getTermination('inputCurrent1shoulder'))
network.addProjection(r.getOrigin('elbowAngle'),controlV.getTermination('inputCurrent2elbow'))
network.addProjection(r.getOrigin('wristAngle'),controlV.getTermination('inputCurrent3wrist'))

network.addProjection(r.getOrigin('shoulderAngle'),networkA.getTermination('Q1'))    #connecting angle information with A matrix input
network.addProjection(r.getOrigin('elbowAngle'),networkA.getTermination('Q2'))
network.addProjection(r.getOrigin('elbowAngle'),networkA.getTermination('Q2f3'))
network.addProjection(r.getOrigin('wristAngle'),networkA.getTermination('Q3'))


network.addProjection(r.getOrigin('shoulderVel'),pdGain.getTermination('shVel'))
network.addProjection(r.getOrigin('elbowVel'),pdGain.getTermination('elVel'))
network.addProjection(r.getOrigin('wristVel'),pdGain.getTermination('wriVel'))




#Up to here, simulator is set up, the uncompensated Q control vector is available to be multiplied with the A matrix.

#Setup A*T network. Input: 9 elements of A, 3 elements of T. Output: 3 elements of A*T

#expose terminations

#massMult.exposeTermination(massMult.getNode('hinge1').getOrigin('origin'),'shoulderAngle')




# put everything in direct mode
network.setMode(SimulationMode.DEFAULT) #for debugging only
# except the last population
controlV.setMode(SimulationMode.DEFAULT)
pdGain.setMode(SimulationMode.DEFAULT)
r.setMode(SimulationMode.DIRECT)

	
	

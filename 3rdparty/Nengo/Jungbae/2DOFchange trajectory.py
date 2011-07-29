
from __future__ import generators
import sys

import space
reload(space)

dt=0.001
N=1
pstc=0.01



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
import java
from java.awt import Color

try:
    world.remove(network)
except:
    pass
    
network = NetworkImpl()
network.name ='simple arm controller'

class getShoulder(ca.nengo.math.Function):
  def map(self,X):
	x = float(X[0])
	y = float(X[1])
	# make sure we're in the unit circle
	if sqrt(x**2+y**2) > 1: 
		x = x / (sqrt(x**2+y**2))
		y = y / (sqrt(x**2+y**2))

	L1 = .5
	L2 = .5
	EPS = 1e-10
	D = (x**2 + y**2 - L1**2 - L2**2) / (2*L1*L2) # law of cosines
	if (x**2+y**2) < (L1**2+L2**2):  
		D = -D

	# find elbow down angles from shoulder to elbow

        #java.lang.System.out.println("x: %f   y:%f"%(x,y))
	if D < 1 and D > -1:
		elbow = acos(D)
	else:
		elbow = 0

	if (x**2+y**2) < (L1**2+L2**2):  
		elbow = pi - elbow
	
	if x==0 and y==0: y = y+EPS

	inside = L2*sin(elbow)/(sqrt(x**2+y**2))
	if inside > 1: inside = 1
	if inside < -1: inside = -1

	if x==0: 
		shoulder = 1.5708 - asin(inside) # magic numbers from matlab
	else:
		shoulder = atan(y/x) - asin(inside)
	if x < 0:  shoulder = shoulder + pi

	return shoulder
  def getDimension(self):
	return 2

class getElbow(ca.nengo.math.Function):
  def map(self,X):
	x = float(X[0])
	y = float(X[1])
	# make sure we're in the unit circle
	if sqrt(x**2+y**2) > 1: 
		x = x / (sqrt(x**2+y**2))
		y = y / (sqrt(x**2+y**2))
	L1 = .5
	L2 = .5
	D = (x**2 + y**2 - L1**2 - L2**2) / (2*L1*L2) # law of cosines
	if (x**2+y**2) < (L1**2+L2**2):  
		D = -D

	# find elbow down angles from shoulder to elbow

	if D < 1 and D > -1:
		elbow = acos(D)
	else:
		elbow = 0

	if (x**2+y**2) < (L1**2+L2**2):  
		elbow = pi - elbow

	return elbow
  def getDimension(self):
	return 2

class getX(ca.nengo.math.Function):
  def map(self,X):
	shoulder = X[0]
	elbow = X[1]
	L1 = .5
	L2 = .5
	
	return L1*cos(shoulder)+L2*cos(shoulder+elbow)
	
  def getDimension(self):
	return 2

class getY(ca.nengo.math.Function):
  def map(self,X):
	shoulder = X[0]
	elbow = X[1]
	L1 = .5
	L2 = .5
	
	return L1*sin(shoulder)+L2*sin(shoulder+elbow)
	
  def getDimension(self):
	return 2



ef = NEFEnsembleFactoryImpl()
ef.nodeFactory=LIFNeuronFactory(tauRC=.020, tauRef=.001, maxRate=IndicatorPDF(200,400), intercept=IndicatorPDF(-1,1))

# input functions
refX=FunctionInput('refX',[ConstantFunction(1,-1)],Units.UNK)# X coordinate of target
refY=FunctionInput('refY',[ConstantFunction(1,1)],Units.UNK)# Y coordinate of target


F=FunctionInput('F',[ConstantFunction(1,-1),ConstantFunction(1,0),ConstantFunction(1,-1), \
ConstantFunction(1,0),ConstantFunction(1,0),ConstantFunction(1,-1),ConstantFunction(1,0), \
ConstantFunction(1,-1)],Units.UNK) # used to stabilize system

network.addNode(refX)
network.addNode(refY)
#network.addNode(Tfunc)
network.addNode(F)

# neural populations
convertXY=ef.make("convert XY",300,2)
convertXY.setRadii([2.0,2.0]);

convertAngles=ef.make("convert Angles",300,2)
convertAngles.setRadii([2.0,2.0]);


FX=ef.make("FX",300,12)
FX.setRadii([5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0,5.0]);

controlV=ef.make("control signal v",200,2) # calculate 2D control signal
controlU=ef.make("control signal u",500,2) # calculates joint torque control signal

network.addNode(convertXY)
network.addNode(convertAngles)

network.addNode(FX)
network.addNode(controlV)
network.addNode(controlU)

# add terminations
convertXY.addDecodedTermination('refXY',[[1,0],[0,1]],pstc,False)

convertAngles.addDecodedTermination('shoulder',[[1],[0]],pstc,False)
convertAngles.addDecodedTermination('elbow',[[0],[1]],pstc,False)

FX.addDecodedTermination('inputFs',[[1,0,0,0,0,0,0,0],[0,1,0,0,0,0,0,0],[0,0,1,0,0,0,0,0], \
[0,0,0,1,0,0,0,0],[0,0,0,0,1,0,0,0],[0,0,0,0,0,1,0,0],[0,0,0,0,0,0,1,0],[0,0,0,0,0,0,0,1], \
[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0]],pstc,False)
#FX.addDecodedTermination('X1',[[0],[0],[0],[0],[0],[0],[0],[0],[1],[0],[0],[0]],pstc,False)
#FX.addDecodedTermination('X2',[[0],[0],[0],[0],[0],[0],[0],[0],[0],[1],[0],[0]],pstc,False)
#FX.addDecodedTermination('X3',[[0],[0],[0],[0],[0],[0],[0],[0],[0],[0],[1],[0]],pstc,False)
#FX.addDecodedTermination('X4',[[0],[0],[0],[0],[0],[0],[0],[0],[0],[0],[0],[1]],pstc,False)

FX.addDecodedTermination('X1',[[0],[0],[0],[0],[0],[0],[0],[0],[-1],[0],[0],[0]],pstc,False)
FX.addDecodedTermination('X2',[[0],[0],[0],[0],[0],[0],[0],[0],[0],[-1],[0],[0]],pstc,False)
FX.addDecodedTermination('X3',[[0],[0],[0],[0],[0],[0],[0],[0],[0],[0],[-1],[0]],pstc,False)
FX.addDecodedTermination('X4',[[0],[0],[0],[0],[0],[0],[0],[0],[0],[0],[0],[-1]],pstc,False)

controlV.addDecodedTermination('inputCurrentX',[[-1],[0]],pstc,False)
controlV.addDecodedTermination('inputCurrentY',[[0],[-1]],pstc,False)
controlV.addDecodedTermination('inputRefX',[[1],[0]],pstc,False)
controlV.addDecodedTermination('inputRefY',[[0],[1]],pstc,False)

controlU.addDecodedTermination('inputFuncT1',[[1],[0]],pstc,False)
controlU.addDecodedTermination('inputFuncT2',[[0],[1]],pstc,False)
controlU.addDecodedTermination('inputFX1',[[1],[0]],pstc,False)
controlU.addDecodedTermination('inputFX2',[[0],[1]],pstc,False)

# add origins
interpreter=DefaultFunctionInterpreter()

convertXY.addDecodedOrigin('elbowRef',[getElbow()],"AXON")
convertXY.addDecodedOrigin('shoulderRef',[getShoulder()],"AXON")

convertAngles.addDecodedOrigin('currentX',[getX()],"AXON")
convertAngles.addDecodedOrigin('currentY',[getY()],"AXON")

#-1 0 -1 0 0 -1 0 -1 0
# 0 1  2 3 4  5 6  7  8

FX.addDecodedOrigin('FX1',[interpreter.parse("x8+x10",12)],"AXON")
FX.addDecodedOrigin('FX2',[interpreter.parse("x9+x11",12)],"AXON")


controlU.addDecodedOrigin('u1',[interpreter.parse("x0",2)],"AXON")
controlU.addDecodedOrigin('u2',[interpreter.parse("x1",2)],"AXON")



# add projections 
network.addProjection(controlV.getOrigin('X'),convertXY.getTermination('refXY'))

network.addProjection(refX.getOrigin('origin'),controlV.getTermination('inputRefX'))
network.addProjection(refY.getOrigin('origin'),controlV.getTermination('inputRefY'))

network.addProjection(convertAngles.getOrigin('currentX'),controlV.getTermination('inputCurrentX'))
network.addProjection(convertAngles.getOrigin('currentY'),controlV.getTermination('inputCurrentY'))

network.addProjection(F.getOrigin('origin'),FX.getTermination('inputFs'))



#added by me
network.addProjection(convertXY.getOrigin('shoulderRef'),controlU.getTermination('inputFuncT1'))
network.addProjection(convertXY.getOrigin('elbowRef'),controlU.getTermination('inputFuncT2'))





network.addProjection(FX.getOrigin('FX1'),controlU.getTermination('inputFX1'))
network.addProjection(FX.getOrigin('FX2'),controlU.getTermination('inputFX2'))





















world.add(network)
import ccm

import random
random.seed(11)

from math import pi
from com.threed.jpct import SimpleVector
from com.bulletphysics.linearmath import Transform
from javax.vecmath import Vector3f
import  sohn_global_time


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

        shoulder=HingeConstraint(torso.physics,upperarm.physics,
                            Vector3f(0.7,0.1,1),Vector3f(0,-0.5,0),
                            Vector3f(0,0,1),Vector3f(0,0,1))
               
        elbow=HingeConstraint(upperarm.physics,lowerarm.physics,
                            Vector3f(0,0.5,0),Vector3f(0,-0.5,0),
                            Vector3f(0,0,1),Vector3f(0,0,1))
                            
        shoulder.setLimit(-pi/2,pi/2+.1)
        elbow.setLimit(-pi,0)
        
        self.physics.addConstraint(elbow)
        self.physics.addConstraint(shoulder)
       
        #upperarm.physics.applyTorqueImpulse(Vector3f(0,0,300))
        #lowerarm.physics.applyTorqueImpulse(Vector3f(0,0,300))
            
        self.sch.add(space.Room.start,args=(self,))
        self.update_neurons()
        self.upperarm=upperarm
        self.lowerarm=lowerarm
        self.shoulder=shoulder
        self.elbow=elbow
        self.hinge1=self.shoulder.hingeAngle
        self.hinge2=self.elbow.hingeAngle
        self.upperarm.physics.setSleepingThresholds(0,0)
        self.lowerarm.physics.setSleepingThresholds(0,0)
            	
    def update_neurons(self):
        while True:
            sohn_global_time.time_index = sohn_global_time.time_index+1;
            scale=0.0003
            scale2 = 0.00002
            m1=controlU.getOrigin('u1').getValues().getValues()[0]*scale
            m2=controlU.getOrigin('u2').getValues().getValues()[0]*scale
            v1=Vector3f(0,0,0)
            v2=Vector3f(0,0,0)
           
            mover = -1+sohn_global_time.time_index*scale2
            if mover >1:
            		sohn_global_time.time_index = 0;
	

            refX=FunctionInput('refX',[ConstantFunction(1,mover)],Units.UNK)# X coordinate of target
            #refX.setFunctions([ConstantFunction(1,mover)]);

            java.lang.System.out.println("m1: %f   m2:%f"%(m1,m2))
            java.lang.System.out.println("time:%d,  inc:%f"%(sohn_global_time.time_index,mover))

            control1 = controlU.getOrigin('u1').getValues().getValues()[0]
            control2 = controlU.getOrigin('u2').getValues().getValues()[0]	
            errorx = controlV.getOrigin('X').getValues().getValues()[0] 
            errory = controlV.getOrigin('X').getValues().getValues()[1]
            curx = convertAngles.getOrigin('currentX').getValues().getValues()[0] 
            cury = convertAngles.getOrigin('currentY').getValues().getValues()[0]
            shoulder_error = 	convertXY.getOrigin('shoulderRef') .getValues().getValues()[0] 
            elbow_error = convertXY.getOrigin('elbowRef') .getValues().getValues()[0] 
            shoulder_damp = FX.getOrigin('FX1').getValues().getValues()[0] 
            elbow_damp = FX.getOrigin('FX2').getValues().getValues()[0] 

            shoulder_angle =self.hinge1
            elbow_angle = self.hinge2
           

            self.upperarm.physics.applyTorqueImpulse(Vector3f(0,0,m1))
            self.lowerarm.physics.applyTorqueImpulse(Vector3f(0,0,m2))

            self.hinge1=-(self.shoulder.hingeAngle-pi/2)
            self.hinge2=-self.elbow.hingeAngle
            
            java.lang.System.out.println("angle1: %f   angle2:%f"%(self.hinge1,self.hinge2))   
	
            self.upperarm.physics.getAngularVelocity(v1)
            self.lowerarm.physics.getAngularVelocity(v2)
            # put bounds on the velocity possible
            if v1.z > 2: self.upperarm.physics.setAngularVelocity(Vector3f(0,0,2))
            if v1.z < -2: self.upperarm.physics.setAngularVelocity(Vector3f(0,0,-2))
            if v2.z > 2: self.lowerarm.physics.setAngularVelocity(Vector3f(0,0,2))
            if v2.z < -2: self.lowerarm.physics.setAngularVelocity(Vector3f(0,0,-2))
            self.upperarm.physics.getAngularVelocity(v1)
            self.lowerarm.physics.getAngularVelocity(v2)
            
            shoulder_vel =   v1.z
            elbow_vel = v2.z	
          
            f = open('anyfile.txt',"a");
            f.write( "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,\n" %(shoulder_angle,elbow_angle,shoulder_vel,elbow_vel, curx,cury, mover,1, errorx,errory, shoulder_error,elbow_error,shoulder_damp,elbow_damp, control1,control2))
           #printing shA, elA,shV,elV,curx,cury,refx(mover),refy,errorx,errory,shoulder_err, elbow_err, shoulder_damp,elbow_damp,control1,control2
           #	        1    2     3     4    5      6      7                     8       9        10       11                      12                13                14                  15           16
            wt=Transform()
            #self.target.physics.motionState.getWorldTransform(wt)
            wt.setIdentity()
            
            tx=controlV.getTermination('inputRefX').input
           

            if tx is not None:
                #wt.origin.x=tx.values[0]+0.7
                   wt.origin.x = mover+0.7
            else:    
                wt.origin.x=0.7
            
            ty=controlV.getTermination('inputRefY').input
            

            if ty is not None:
                wt.origin.y=ty.values[0]+0.1
            else:    
                wt.origin.y=0.1
            wt.origin.z=2

            self.target.physics.motionState.worldTransform=wt
            
            
            self.vel1=v1.z
            self.vel2=v2.z

           
	
  
          
	
           
            yield 0.0001
    
r=ccm.nengo.create(Room)
network.addNode(r)

# need to make hinge1, hinge2, vel1, and vel external nodes and hook up the output to the FX matrix
r.exposeOrigin(r.getNode('hinge1').getOrigin('origin'),'shoulderAngle')
r.exposeOrigin(r.getNode('hinge2').getOrigin('origin'),'elbowAngle')
r.exposeOrigin(r.getNode('vel1').getOrigin('origin'),'shoulderVel')
r.exposeOrigin(r.getNode('vel2').getOrigin('origin'),'elbowVel')

network.addProjection(r.getOrigin('shoulderAngle'),FX.getTermination('X1'))
network.addProjection(r.getOrigin('elbowAngle'),FX.getTermination('X2'))
network.addProjection(r.getOrigin('shoulderVel'),FX.getTermination('X3'))
network.addProjection(r.getOrigin('elbowVel'),FX.getTermination('X4'))

network.addProjection(r.getOrigin('shoulderAngle'),convertAngles.getTermination('shoulder'))
network.addProjection(r.getOrigin('elbowAngle'),convertAngles.getTermination('elbow'))




# add probes


network.simulator.addProbe(controlU.getName(),'u1',True)
network.simulator.addProbe(controlU.getName(),'u2',True)


network.simulator.addProbe(convertXY.getName(),'shoulderRef',True)
network.simulator.addProbe(convertXY.getName(),'elbowRef',True)

network.simulator.addProbe(r.getName(),'shoulderAngle',True)
network.simulator.addProbe(r.getName(),'elbowAngle',True)
network.simulator.addProbe(r.getName(),'shoulderVel',True)
network.simulator.addProbe(r.getName(),'elbowVel',True)

network.simulator.addProbe(FX.getName(),'FX1',True)
network.simulator.addProbe(FX.getName(),'FX2',True)


network.simulator.addProbe(controlV.getName(),'X',True)

network.simulator.addProbe(convertAngles.getName(),'currentX',True)
network.simulator.addProbe(convertAngles.getName(),'currentY',True)


         

# put everything in direct mode
network.setMode(SimulationMode.DIRECT)

# except the last population
controlU.setMode(SimulationMode.DEFAULT)
controlV.setMode(SimulationMode.DEFAULT)
convertAngles.setMode(SimulationMode.DEFAULT)
convertXY.setMode(SimulationMode.DEFAULT)
FX.setMode(SimulationMode.DEFAULT)

	

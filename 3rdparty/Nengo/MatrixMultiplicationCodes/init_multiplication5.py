# init_multiplication.py:
 
# By default, the python engine does not import any of the nengo # classes, so this must be done before any of the nengo classes # can be instantiated:

from ca.nengo.model import *
from ca.nengo.model.impl import *
from ca.nengo.model.nef.impl import *
from ca.nengo.model.neuron import *
from ca.nengo.math.impl import *                    
 

network_outer=NetworkImpl()
network_outer.name="VecVec"
world.add(network_outer)

network=NetworkImpl()
network.name="Mult"
network_outer.addNode(network)

input5=FunctionInput("Input5", [ConstantFunction(1,0.5)],Units.UNK)
input4=FunctionInput("Input4", [ConstantFunction(1,0.4)],Units.UNK)
input0=FunctionInput("Input0", [ConstantFunction(1,0.0)],Units.UNK)
input1=FunctionInput("Input1", [ConstantFunction(1,1.0)],Units.UNK)

network_outer.addNode(input5)
network_outer.addNode(input4)
network_outer.addNode(input0)
network_outer.addNode(input1)

# This function will create the NEFEnsembles for matrix
# multiplication.
 
#  network - This is the network to which we wish to add matrix
#    multiplication.
#  populationSize - This is the number of neurons in each
#    NEFEnsemble representing the entries and cross terms.
#  tau - This is the synaptic time constant of the terminations.
#  n - the dimension of the matrices
 
def init_multiplication(n,populationSize,tau):
 
  # The NEFEnsembleFactory interface lets you create 
  # NEFEnsembles with given properties.   Here, we have asked for
  # default properties.
 
  ef = NEFEnsembleFactoryImpl();
  ef.nodeFactory.tauRC=0.02
  ef.nodeFactory.tauRef=0.002
  ef.nodeFactory.maxRate=IndicatorPDF(100,200)
  ef.nodeFactory.intercept=IndicatorPDF(-1,1)

  # First, we will create NEFEnsembles to represent the
  #   entries of each matrix.
 
  a = [ [None] for i in range(0,n) ];
  b = [ [None] for i in range(0,n) ];
  aT = [ [None] for i in range(0,n) ];
  bT = [ [None] for i in range(0,n) ];
  aO = [ [None] for i in range(0,n) ];
  bO = [ [None] for i in range(0,n) ];
 
  r = [ [None] ];
  rT = [ [None] ];
  rO = [ [None] ];
 
  IdentityFunction = Polynomial([0,1]);
  Product = PostfixFunction(None,"x0*x1",2);
 
  for i in range(0,n):
    
    # Creating ensembles for the vector.
    b[i] = ef.make("b"+str(i+1), \
        populationSize, 1, "b"+str(i+1), 0);
    bT[i] = b[i].addDecodedTermination \
        ("b"+str(i+1), [[1]], tau, 0);
    bO[i] = b[i].addDecodedOrigin \
        ("b"+str(i+1), [IdentityFunction], \
        Neuron.AXON);
    network.addNode(b[i]);
    network.exposeTermination \
        (bT[i], "b"+str(i+1));

 
    # Creating ensembles for the vector.
    a[i] = ef.make("a"+str(i+1), \
        populationSize, 1, "a"+str(i+1), 0);
    aT[i] = a[i].addDecodedTermination \
        ("a"+str(i+1), [[1]], tau, 0);
    aO[i] = a[i].addDecodedOrigin \
        ("a"+str(i+1), [IdentityFunction], \
        Neuron.AXON);
    network.addNode(a[i]);
    network.exposeTermination \
        (aT[i], "a"+str(i+1));
 
      
  network_outer.addProjection(input4.getOrigin('origin'), network.getTermination("a1"))
  network_outer.addProjection(input0.getOrigin('origin'), network.getTermination("a2"))
  network_outer.addProjection(input1.getOrigin('origin'), network.getTermination("a3"))

  network_outer.addProjection(input1.getOrigin('origin'), network.getTermination("b1"))  
  network_outer.addProjection(input0.getOrigin('origin'), network.getTermination("b2"))
  network_outer.addProjection(input5.getOrigin('origin'), network.getTermination("b3"))

  # Now, for each row i and column j we must sum the cross
  # terms to produce the i][j-th entry of the result.
  

    # This ensemble is the i][j-th entry of the result.
  r = ef.make("r", \
      populationSize, 1, "r", 0);
  network.addNode(r);
    
  for j in range(0,n):
 
      # This is the k-th cross term between the i-th row
       # of the matrix 'a' and the j-th column of the matrix
       # 'b': a[i,k]b[k,j].
 
        # Each coordinate of this two dimensional representation
        # is in the range [-1,1], so the magnitude of the
        # largest vector we might have to represent is              
        # sqrt(1+1)=sqrt(2)=1.414
 
      c = ef.make \
          ("a"+str(j+1)+"b"+str(j+1),\
          populationSize, [1.414,1.414]);
 
      # The ensemble is added to the network.
      network.addNode(c);
 
      # The i,k-th entry of matrix 'a' will project to the
      # first dimension of this cross term.
      ca = c.addDecodedTermination \
          ("a"+str(j+1)+"b"+str(j+1)+"_a", \
        [[1.0],[0.0]], tau, 0);
      network.addProjection(aO[j], ca);
 
        # The k,j-th entry of matrix 'b' will project to the
        # second dimension of this cross term.
      cb = c.addDecodedTermination \
          ("a"+str(j+1)+"b"+str(j+1)+"_b", \
          [[0.0],[1.0]], tau, 0);
      network.addProjection(bO[j], cb);
 
        # This origin will decode the product of the two
        # dimensions of the cross term population.
      cO = c.addDecodedOrigin \
          ("a"+str(j+1)+"b"+str(j+1), \
          [Product], Neuron.AXON);
 
        # The i,j-th entry of the result is the sum of
        # these cross terms, so the cross terms must project .
      rT = r.addDecodedTermination( \
          "a"+str(j+1)+"b"+str(j+1),\
          [[1.0]],tau,0);
      network.addProjection(cO,rT);
 
  #  Add an origin to the i][j-th entry and expose it
  #  so that it can be used by parent networks.
 
  rO = r.addDecodedOrigin("r", \
        [IdentityFunction], Neuron.AXON);
  network.exposeOrigin(rO, "r");

  network.simulator.addProbe("r",r,"r",True);
  network.exposeState(r,"r","r");    
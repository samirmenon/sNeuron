# init_multiplication.py:
 
# By default, the python engine does not import any of the nengo # classes, so this must be done before any of the nengo classes # can be instantiated:

from ca.nengo.model import *
from ca.nengo.model.impl import *
from ca.nengo.model.nef.impl import *
from ca.nengo.model.neuron import *
from ca.nengo.math.impl import *                    
 
#create a new network that will contain all the nodes
network_outer=NetworkImpl()
network_outer.name="VecMat"
world.add(network_outer)

#Add a sub network to the original network. This is responsible for all the multiplication.
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
 
  a = [ [None]*n for i in range(0,n) ];
  b = [ [None] for i in range(0,n) ];
  aT = [ [None]*n for i in range(0,n) ];
  bT = [ [None] for i in range(0,n) ];
  aO = [ [None]*n for i in range(0,n) ];
  bO = [ [None] for i in range(0,n) ];
 
  r = [ [None] for i in range(0,n)];
  rT = [ [None] for i in range(0,n) ];
  rO = [ [None] for i in range(0,n) ];

  #Specifying functional inputs 
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

    for j in range(0,n):
 
      # We use ef to create an ensemble to represent the value
      #  of the i][j-th entry of the first matrix.
      a[i][j] = ef.make("a"+str(i+1)+str(j+1), \
        populationSize, 1, "a"+str(i+1)+str(j+1), 0);
 
 
      # A termination is added.   Other ensembles in the parent
      # network will project to this terminal and set the
      # i,j-th value of the first matrix.
      aT[i][j] = a[i][j].addDecodedTermination \
        ("a"+str(i+1)+str(j+1), [[1]], tau, 0);
 
      # An origin is added from this ensemble.
      # It will project to the cross terms.
      aO[i][j] = a[i][j].addDecodedOrigin \
        ("a"+str(i+1)+str(j+1), [IdentityFunction], \
        Neuron.AXON);
 
      # The ensemble is added to the network.
      network.addNode(a[i][j]);
 
      # The terminal is exposed to the parent network.
      network.exposeTermination \
        (aT[i][j] , "a"+str(i+1)+str(j+1));
 
  #project origin of inputs to terminations of your matrix
  network_outer.addProjection(input5.getOrigin('origin'), network.getTermination("a11"))
  network_outer.addProjection(input5.getOrigin('origin'), network.getTermination("a31"))
  network_outer.addProjection(input5.getOrigin('origin'), network.getTermination("a32"))
  network_outer.addProjection(input4.getOrigin('origin'), network.getTermination("a23"))  
  network_outer.addProjection(input0.getOrigin('origin'), network.getTermination("a12"))
  network_outer.addProjection(input0.getOrigin('origin'), network.getTermination("a21"))
  network_outer.addProjection(input0.getOrigin('origin'), network.getTermination("a33"))
  network_outer.addProjection(input1.getOrigin('origin'), network.getTermination("a13"))
  network_outer.addProjection(input1.getOrigin('origin'), network.getTermination("a22"))

  network_outer.addProjection(input0.getOrigin('origin'), network.getTermination("b1"))
  network_outer.addProjection(input4.getOrigin('origin'), network.getTermination("b2"))
  network_outer.addProjection(input5.getOrigin('origin'), network.getTermination("b3"))

  # Now, for each row i and column j we must sum the cross
  # terms to produce the i][j-th entry of the result.
  for i in range(0,n):

    # This ensemble is the i][j-th entry of the result.
    r[i] = ef.make("r"+str(i+1)+str(j+1), \
      populationSize, 1, "r"+str(i+1)+str(j+1), 0);
    network.addNode(r[i]);
    
    for j in range(0,n):
 
      # This is the k-th cross term between the i-th row
       # of the matrix 'a' and the j-th column of the matrix
       # 'b': a[i,k]b[k,j].
 
        # Each coordinate of this two dimensional representation
        # is in the range [-1,1], so the magnitude of the
        # largest vector we might have to represent is              
        # sqrt(1+1)=sqrt(2)=1.414
 
      c = ef.make \
          ("a"+str(i+1)+str(j+1)+"b"+str(j+1),\
          populationSize, [1.414,1.414]);
 
      # The ensemble is added to the network.
      network.addNode(c);
 
      # The i,k-th entry of matrix 'a' will project to the
      # first dimension of this cross term.
      ca = c.addDecodedTermination \
          ("a"+str(i+1)+str(j+1)+"b"+str(j+1)+"_a", \
        [[1.0],[0.0]], tau, 0);
      network.addProjection(aO[i][j], ca);
 
        # The k,j-th entry of matrix 'b' will project to the
        # second dimension of this cross term.
      cb = c.addDecodedTermination \
          ("a"+str(i+1)+str(j+1)+"b"+str(j+1)+"_b", \
          [[0.0],[1.0]], tau, 0);
      network.addProjection(bO[j], cb);
 
        # This origin will decode the product of the two
        # dimensions of the cross term population.
      cO = c.addDecodedOrigin \
          ("a"+str(i+1)+str(j+1)+"b"+str(j+1), \
          [Product], Neuron.AXON);
 
        # The i,j-th entry of the result is the sum of
        # these cross terms, so the cross terms must project .
      rT = r[i].addDecodedTermination( \
          "a"+str(i+1)+str(j+1)+"b"+str(j+1),\
          [[1.0]],tau,0);
      network.addProjection(cO,rT);
 
    #  Add an origin to the i][j-th entry and expose it
    #  so that it can be used by parent networks.
 
    rO = r[i].addDecodedOrigin("r"+str(i+1), \
        [IdentityFunction], Neuron.AXON);
    network.exposeOrigin(rO, "r"+str(i+1));
    network.simulator.addProbe("r"+str(i+1), r[i],"r"+str(i+1),True)
    network.exposeState(r[i],"r"+str(i+1), "r"+str(i+1))    

# init_multiplication.py:
 
# By default, the python engine does not import any of the nengo # classes, so this must be done before any of the nengo classes # can be instantiated:

from ca.nengo.model import *
from ca.nengo.model.impl import *
from ca.nengo.model.nef.impl import *
from ca.nengo.model.neuron import *
from ca.nengo.math.impl import *                    
 

network_outer=NetworkImpl()
network_outer.name="VecMatMatVec"
world.add(network_outer)

network1=NetworkImpl()
network1.name="MatVec"
network_outer.addNode(network1)

network2=NetworkImpl()
network2.name="VecMat"
network_outer.addNode(network2)

network3=NetworkImpl()
network3.name="VecVec"
network_outer.addNode(network3)

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
def init_multiplication3(n,populationSize,tau):
 
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
    b[i] = ef.make("bZ"+str(i+1), \
        populationSize, 1, "bZ"+str(i+1), 0);
    bT[i] = b[i].addDecodedTermination \
        ("bZ"+str(i+1), [[1]], tau, 0);
    bO[i] = b[i].addDecodedOrigin \
        ("bZ"+str(i+1), [IdentityFunction], \
        Neuron.AXON);
    network3.addNode(b[i]);
    network3.exposeTermination \
        (bT[i], "bZ"+str(i+1));

 
    # Creating ensembles for the vector.
    a[i] = ef.make("aZ"+str(i+1), \
        populationSize, 1, "aZ"+str(i+1), 0);
    aT[i] = a[i].addDecodedTermination \
        ("aZ"+str(i+1), [[1]], tau, 0);
    aO[i] = a[i].addDecodedOrigin \
        ("aZ"+str(i+1), [IdentityFunction], \
        Neuron.AXON);
    network3.addNode(a[i]);
    network3.exposeTermination \
        (aT[i], "aZ"+str(i+1));
 
  # Now, for each row i and column j we must sum the cross
  # terms to produce the i][j-th entry of the result.
  

    # This ensemble is the i][j-th entry of the result.
  r = ef.make("rZ", \
      populationSize, 1, "rZ", 0);
  network3.addNode(r);
    
  for j in range(0,n):
 
      # This is the k-th cross term between the i-th row
       # of the matrix 'a' and the j-th column of the matrix
       # 'b': a[i,k]b[k,j].
 
        # Each coordinate of this two dimensional representation
        # is in the range [-1,1], so the magnitude of the
        # largest vector we might have to represent is              
        # sqrt(1+1)=sqrt(2)=1.414
 
      c = ef.make \
          ("aZ"+str(j+1)+"bZ"+str(j+1),\
          populationSize, [1.414,1.414]);
 
      # The ensemble is added to the network.
      network3.addNode(c);
 
      # The i,k-th entry of matrix 'a' will project to the
      # first dimension of this cross term.
      ca = c.addDecodedTermination \
          ("aZ"+str(j+1)+"bZ"+str(j+1)+"_aZ", \
        [[1.0],[0.0]], tau, 0);
      network3.addProjection(aO[j], ca);
 
        # The k,j-th entry of matrix 'b' will project to the
        # second dimension of this cross term.
      cb = c.addDecodedTermination \
          ("aZ"+str(j+1)+"bZ"+str(j+1)+"_bZ", \
          [[0.0],[1.0]], tau, 0);
      network3.addProjection(bO[j], cb);
 
        # This origin will decode the product of the two
        # dimensions of the cross term population.
      cO = c.addDecodedOrigin \
          ("aZ"+str(j+1)+"bZ"+str(j+1), \
          [Product], Neuron.AXON);
 
        # The i,j-th entry of the result is the sum of
        # these cross terms, so the cross terms must project .
      rT = r.addDecodedTermination( \
          "aZ"+str(j+1)+"bZ"+str(j+1),\
          [[1.0]],tau,0);
      network3.addProjection(cO,rT);
 
  #  Add an origin to the i][j-th entry and expose it
  #  so that it can be used by parent networks.
 
  rO = r.addDecodedOrigin("rZ", \
        [IdentityFunction], Neuron.AXON);
  network3.exposeOrigin(rO, "rZ");   

def init_multiplication1(n,populationSize,tau):
 
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
 
  IdentityFunction = Polynomial([0,1]);
  Product = PostfixFunction(None,"x0*x1",2);
 
  for i in range(0,n):
    
    # Creating ensembles for the vector.
    b[i] = ef.make("bX"+str(i+1), \
        populationSize, 1, "bX"+str(i+1), 0);
    bT[i] = b[i].addDecodedTermination \
        ("bX"+str(i+1), [[1]], tau, 0);
    bO[i] = b[i].addDecodedOrigin \
        ("bX"+str(i+1), [IdentityFunction], \
        Neuron.AXON);
    network1.addNode(b[i]);
    network1.exposeTermination \
        (bT[i], "bX"+str(i+1));

    for j in range(0,n):
 
      # We use ef to create an ensemble to represent the value
      #  of the i][j-th entry of the first matrix.
      a[i][j] = ef.make("aX"+str(i+1)+str(j+1), \
        populationSize, 1, "aX"+str(i+1)+str(j+1), 0);
 
 
      # A termination is added.   Other ensembles in the parent
      # network will project to this terminal and set the
      # i,j-th value of the first matrix.
      aT[i][j] = a[i][j].addDecodedTermination \
        ("aX"+str(i+1)+str(j+1), [[1]], tau, 0);
 
      # An origin is added from this ensemble.
      # It will project to the cross terms.
      aO[i][j] = a[i][j].addDecodedOrigin \
        ("aX"+str(i+1)+str(j+1), [IdentityFunction], \
        Neuron.AXON);
 
      # The ensemble is added to the network.
      network1.addNode(a[i][j]);
 
      # The terminal is exposed to the parent network.
      network1.exposeTermination \
        (aT[i][j] , "aX"+str(i+1)+str(j+1));
 
      
  network_outer.addProjection(input5.getOrigin('origin'), network1.getTermination("aX11"))
  network_outer.addProjection(input5.getOrigin('origin'), network1.getTermination("aX31"))
  network_outer.addProjection(input5.getOrigin('origin'), network1.getTermination("aX32"))
  network_outer.addProjection(input4.getOrigin('origin'), network1.getTermination("aX23"))  
  network_outer.addProjection(input0.getOrigin('origin'), network1.getTermination("aX12"))
  network_outer.addProjection(input0.getOrigin('origin'), network1.getTermination("aX21"))
  network_outer.addProjection(input0.getOrigin('origin'), network1.getTermination("aX33"))
  network_outer.addProjection(input1.getOrigin('origin'), network1.getTermination("aX13"))
  network_outer.addProjection(input1.getOrigin('origin'), network1.getTermination("aX22"))

  network_outer.addProjection(input0.getOrigin('origin'), network1.getTermination("bX1"))
  network_outer.addProjection(input4.getOrigin('origin'), network1.getTermination("bX2"))
  network_outer.addProjection(input5.getOrigin('origin'), network1.getTermination("bX3"))

  # Now, for each row i and column j we must sum the cross
  # terms to produce the i][j-th entry of the result.
  for i in range(0,n):

    # This ensemble is the i][j-th entry of the result.
    r[i] = ef.make("rX"+str(i+1)+str(j+1), \
      populationSize, 1, "rX"+str(i+1)+str(j+1), 0);
    network1.addNode(r[i]);
    
    for j in range(0,n):
 
      # This is the k-th cross term between the i-th row
       # of the matrix 'a' and the j-th column of the matrix
       # 'b': a[i,k]b[k,j].
 
        # Each coordinate of this two dimensional representation
        # is in the range [-1,1], so the magnitude of the
        # largest vector we might have to represent is              
        # sqrt(1+1)=sqrt(2)=1.414
 
      c = ef.make \
          ("aX"+str(i+1)+str(j+1)+"bX"+str(j+1),\
          populationSize, [1.414,1.414]);
 
      # The ensemble is added to the network.
      network1.addNode(c);
 
      # The i,k-th entry of matrix 'a' will project to the
      # first dimension of this cross term.
      ca = c.addDecodedTermination \
          ("aX"+str(i+1)+str(j+1)+"bX"+str(j+1)+"_aX", \
        [[1.0],[0.0]], tau, 0);
      network1.addProjection(aO[i][j], ca);
 
        # The k,j-th entry of matrix 'b' will project to the
        # second dimension of this cross term.
      cb = c.addDecodedTermination \
          ("aX"+str(i+1)+str(j+1)+"bX"+str(j+1)+"_bX", \
          [[0.0],[1.0]], tau, 0);
      network1.addProjection(bO[j], cb);
 
        # This origin will decode the product of the two
        # dimensions of the cross term population.
      cO = c.addDecodedOrigin \
          ("aX"+str(i+1)+str(j+1)+"bX"+str(j+1), \
          [Product], Neuron.AXON);
 
        # The i,j-th entry of the result is the sum of
        # these cross terms, so the cross terms must project .
      rT = r[i].addDecodedTermination( \
          "aX"+str(i+1)+str(j+1)+"bX"+str(j+1),\
          [[1.0]],tau,0);
      network1.addProjection(cO,rT);
 
    #  Add an origin to the i][j-th entry and expose it
    #  so that it can be used by parent networks.
 
    rO = r[i].addDecodedOrigin("rX"+str(i+1), \
        [IdentityFunction], Neuron.AXON);
    network1.exposeOrigin(rO, "rX"+str(i+1));
  
  network_outer.addProjection(network1.getOrigin('rX1'), network3.getTermination("bZ1"))  
  network_outer.addProjection(network1.getOrigin('rX2'), network3.getTermination("bZ2"))
  network_outer.addProjection(network1.getOrigin('rX3'), network3.getTermination("bZ3"))
  
def init_multiplication2(n,populationSize,tau):
 
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
 
  IdentityFunction = Polynomial([0,1]);
  Product = PostfixFunction(None,"x0*x1",2);
 
  for i in range(0,n):
    
    # Creating ensembles for the vector.
    b[i] = ef.make("bY"+str(i+1), \
        populationSize, 1, "bY"+str(i+1), 0);
    bT[i] = b[i].addDecodedTermination \
        ("bY"+str(i+1), [[1]], tau, 0);
    bO[i] = b[i].addDecodedOrigin \
        ("bY"+str(i+1), [IdentityFunction], \
        Neuron.AXON);
    network2.addNode(b[i]);
    network2.exposeTermination \
        (bT[i], "bY"+str(i+1));

    for j in range(0,n):
 
      # We use ef to create an ensemble to represent the value
      #  of the i][j-th entry of the first matrix.
      a[i][j] = ef.make("aY"+str(i+1)+str(j+1), \
        populationSize, 1, "aY"+str(i+1)+str(j+1), 0);
 
 
      # A termination is added.   Other ensembles in the parent
      # network will project to this terminal and set the
      # i,j-th value of the first matrix.
      aT[i][j] = a[i][j].addDecodedTermination \
        ("aY"+str(i+1)+str(j+1), [[1]], tau, 0);
 
      # An origin is added from this ensemble.
      # It will project to the cross terms.
      aO[i][j] = a[i][j].addDecodedOrigin \
        ("aY"+str(i+1)+str(j+1), [IdentityFunction], \
        Neuron.AXON);
 
      # The ensemble is added to the network.
      network2.addNode(a[i][j]);
 
      # The terminal is exposed to the parent network.
      network2.exposeTermination \
        (aT[i][j] , "aY"+str(i+1)+str(j+1));
 
      
  network_outer.addProjection(input5.getOrigin('origin'), network2.getTermination("aY11"))
  network_outer.addProjection(input5.getOrigin('origin'), network2.getTermination("aY31"))
  network_outer.addProjection(input5.getOrigin('origin'), network2.getTermination("aY32"))
  network_outer.addProjection(input4.getOrigin('origin'), network2.getTermination("aY23"))  
  network_outer.addProjection(input0.getOrigin('origin'), network2.getTermination("aY12"))
  network_outer.addProjection(input0.getOrigin('origin'), network2.getTermination("aY21"))
  network_outer.addProjection(input0.getOrigin('origin'), network2.getTermination("aY33"))
  network_outer.addProjection(input1.getOrigin('origin'), network2.getTermination("aY13"))
  network_outer.addProjection(input1.getOrigin('origin'), network2.getTermination("aY22"))

  network_outer.addProjection(input0.getOrigin('origin'), network2.getTermination("bY1"))
  network_outer.addProjection(input4.getOrigin('origin'), network2.getTermination("bY2"))
  network_outer.addProjection(input5.getOrigin('origin'), network2.getTermination("bY3"))

  # Now, for each row i and column j we must sum the cross
  # terms to produce the i][j-th entry of the result.
  for i in range(0,n):

    # This ensemble is the i][j-th entry of the result.
    r[i] = ef.make("rY"+str(i+1)+str(j+1), \
      populationSize, 1, "rY"+str(i+1)+str(j+1), 0);
    network2.addNode(r[i]);
    
    for j in range(0,n):
 
      # This is the k-th cross term between the i-th row
       # of the matrix 'a' and the j-th column of the matrix
       # 'b': a[i,k]b[k,j].
 
        # Each coordinate of this two dimensional representation
        # is in the range [-1,1], so the magnitude of the
        # largest vector we might have to represent is              
        # sqrt(1+1)=sqrt(2)=1.414
 
      c = ef.make \
          ("aY"+str(i+1)+str(j+1)+"bY"+str(j+1),\
          populationSize, [1.414,1.414]);
 
      # The ensemble is added to the network.
      network2.addNode(c);
 
      # The i,k-th entry of matrix 'a' will project to the
      # first dimension of this cross term.
      ca = c.addDecodedTermination \
          ("aY"+str(i+1)+str(j+1)+"bY"+str(j+1)+"_aY", \
        [[1.0],[0.0]], tau, 0);
      network2.addProjection(aO[j][i], ca);
 
        # The k,j-th entry of matrix 'b' will project to the
        # second dimension of this cross term.
      cb = c.addDecodedTermination \
          ("aY"+str(i+1)+str(j+1)+"bY"+str(j+1)+"_bY", \
          [[0.0],[1.0]], tau, 0);
      network2.addProjection(bO[j], cb);
 
        # This origin will decode the product of the two
        # dimensions of the cross term population.
      cO = c.addDecodedOrigin \
          ("aY"+str(i+1)+str(j+1)+"bY"+str(j+1), \
          [Product], Neuron.AXON);
 
        # The i,j-th entry of the result is the sum of
        # these cross terms, so the cross terms must project .
      rT = r[i].addDecodedTermination( \
          "aY"+str(i+1)+str(j+1)+"bY"+str(j+1),\
          [[1.0]],tau,0);
      network2.addProjection(cO,rT);
 
    #  Add an origin to the i][j-th entry and expose it
    #  so that it can be used by parent networks.
 
    rO = r[i].addDecodedOrigin("rY"+str(i+1), \
        [IdentityFunction], Neuron.AXON);
    network2.exposeOrigin(rO, "rY"+str(i+1));     
  
  network_outer.addProjection(network2.getOrigin('rY1'), network3.getTermination("aZ1"))
  network_outer.addProjection(network2.getOrigin('rY2'), network3.getTermination("aZ2"))
  network_outer.addProjection(network2.getOrigin('rY3'), network3.getTermination("aZ3"))
 
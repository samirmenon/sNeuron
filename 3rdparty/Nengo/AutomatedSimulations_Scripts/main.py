from ca.nengo.model import *
from ca.nengo.model.impl import *
from ca.nengo.model.nef.impl import *
from ca.nengo.math.impl import *
from ca.nengo.io import *
from java.io import *

#has just one pool of 400 neurons

import vector_pool
reload(vector_pool)
import vector_1pool
reload(vector_1pool)
import vector_1pool_rad
reload(vector_1pool_rad)
import vector_pool_rad
reload(vector_pool_rad)

values = [2,4];
for i in range(0,2):
	vector_1pool.pool1_rate(values[i],world);
	vector_1pool_rad.pool1_rad(values[i],world);
	vector_pool.pool2_rate(values[i],world);
	vector_pool_rad.pool2_rad(values[i],world);
print 'done!! :)';

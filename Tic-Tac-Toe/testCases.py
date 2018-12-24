# -*- coding: utf-8 -*-
"""
Created on Sun Dec 23 05:17:48 2018

@author: jdgal
"""

from obFile import *
# In[0]
# Random test
import random
testBoard = board()
plays = 0
while plays < 9:
    try:
        testBoard.playOn(random.randint(1,3), random.randint(1,3))
        plays+=1
    except wonGame:
        print(testBoard)
        break
    except occupiedSpace:
        print("bad input caught")
    
del testBoard
# In[]
        

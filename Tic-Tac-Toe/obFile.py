# -*- coding: utf-8 -*-
"""
Created on Thu Dec 20 16:18:35 2018

@author: jdgal
"""

class occupiedSpace(Exception):
    pass

class badInput(Exception):
    pass

class wonGame(Exception):
    pass

class board: 
    def __init__(self):
        self.__field__ = []
        self.__owners__ = []
        self.turn = 0
        for x in range(3):
            self.__field__.append([False, False, False])
            self.__owners__.append([-1,-1,-1])
    
    # [] access operator overload. Allows for <Board>[0][0] for easy lookup        
    def __getitem__(self, key):
        return self.__field__[key]
    
    def __setitem__(self, key, value):
        self.__field__[key] = value
        self.__owners__[key] = self.turn
    
    def __delitem__(self, key):
        self.__field__[key] = False
        self.__owners__[key] = -1
        
    def __wincheck__(self):
        #TODO implement graph for finding wins
        #raise wonGame
        return
    
    def playOn(self, row, col):
        if (row > 3 or row < 1 or col > 3 or row < 1):
            raise badInput
        
        if (self[row-1][col-1]):
            raise occupiedSpace
        
        self.__field__[row-1][col-1] = True
        self.__owners__[row-1][col-1] = self.turn
        self.__wincheck__()
        self.turn+=1
        self.turn%=2
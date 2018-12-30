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
        self.__playedOn__ = 0
        self.__field__ = []
        self.__owners__ = []
        self.__playerSums__ = [{"row":[0,0,0], "col":[0,0,0], "diag":[0,0]},
                                {"row":[0,0,0], "col":[0,0,0], "diag":[0,0]}]
        self.__boardVals__ = [8,1,6,3,5,7,4,9,2]
        self.turn = 0
        for x in range(3):
            self.__field__.append([False, False, False])
            self.__owners__.append([-1,-1,-1])
    
    def __decodeSpaceVal__(self, r, c):
        return 3*(r) + (c)
                    
    def __getitem__(self, key):
        '''[] access operator overload. Allows for <Board>[0][0] for easy
        lookup'''
        return self.__field__[key]
    
    def __setitem__(self, key, value):
        self.__field__[key] = value
        self.__owners__[key] = self.turn
    
    def __delitem__(self, key):
        self.__field__[key] = False
        self.__owners__[key] = -1
        
    def __wincheck__(self):
        for player in self.__playerSums__:
            for x in range(3):
                if player["row"][x] >= 15 or player["col"][x] >= 15:
                    raise wonGame
            if player["diag"][0] >= 15 or player["diag"][1] >= 15:
                raise wonGame
            
        return False
    
    def __updateSums__(self):
        '''Update winning sum values stored in board, calls wincheck and will
        raise the exception if there is a winner. Only call this after 
        directly setting items using <board>[]=x operation as this is not
        a fast op. Playing the game by using playOn automatically updates
        the winning sum values meaning this function does not need to be used'''
        self.__playerSums__ = [{"row":[0,0,0], "col":[0,0,0], "diag":[0,0]},
                                {"row":[0,0,0], "col":[0,0,0], "diag":[0,0]}]
        for y in range(3):
            for x in range(3):
                if self.__owners__[y][x] != -1: #If space is owned
                    val = self.__boardVals__[self.__decodeSpaceVal__(x+1, y+1)]
                    self.__playerSums__[(self.__owners__[y][x])]["row"][x] += val
                    self.__playerSums__[(self.__owners__[y][x])]["col"][y] += val
                    if (x-y) == 0: #Downwards Diagonal
                        self.__playerSums__[(self.__owners__[y][x])]["diag"][0] += val
                    if (x+y) == 2: #Upwards Diagonal
                        self.__playerSums__[(self.__owners__[y][x])]["diag"][1] += val
        
        self.__wincheck__()
    
    def playOn(self, row, col):
        val = self.__boardVals__[self.__decodeSpaceVal__(row-1, col-1)]
        print(val)
        if (row > 3 or row < 1 or col > 3 or row < 1):
            raise badInput
        
        if (self[row-1][col-1]):
            raise occupiedSpace
        
        self.__playedOn__ += 1
        self.__field__[row-1][col-1] = True
        self.__owners__[row-1][col-1] = int(self.turn)
        self.__playerSums__[self.turn]["row"][row-1] += val
        self.__playerSums__[self.turn]["col"][col-1] += val
        if (row == col): #Downwards Diagonal
            self.__playerSums__[self.turn]["diag"][0] += val
        if (row + col) == 4: #Upwards Diagonal
            self.__playerSums__[self.turn]["diag"][1] += val
        self.__wincheck__()
        self.turn+=1
        self.turn%=2
    
    def __str__(self):
        s = "| - - - - - |\n"
        for r in range(3):
            s+= "|"
            for c in range(3):
                if self.__field__[r][c]:
                    if self.__owners__[r][c] == 0:
                        s+=" X"
                    else:
                        s+=" O"
                    s+= " |"
                else:
                    s+="   |"
                    
            s+= "\n| - - - - - |\n"
        return s
            
    def __repr__(self):
        #TODO Complete Full Repr
        represent = ""
        represent += "Turn: Player %d\n" % self.turn
        for p in range(2):
            represent += "\nPlayer %d Win vals:\n\tRows\n\t" % p
            for x in range(3):
                represent += " "+str(self.__playerSums__[p]["row"][x])
            represent += "\n\tCols\n\t"
            for x in range(3):
                represent += " "+str(self.__playerSums__[p]["col"][x])
            represent += "\n\tDiags\n\t"
            for x in range(2):
                represent += " "+str(self.__playerSums__[p]["diag"][x])
        represent+= "\n" + str(self)
        return represent
            
    def isPlayable(self):
        return self.__playedOn__ < 9
         
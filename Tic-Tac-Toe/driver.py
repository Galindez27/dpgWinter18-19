from obFile import *
import signal

def keyboardHandler(signum, frame):
	print("Ending game.\nBye!!")
	exit(2)

gameBoard = board()
while(True):

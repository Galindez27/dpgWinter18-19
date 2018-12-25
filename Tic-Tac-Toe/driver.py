from obFile import *
import signal

def quitHandler(signum, frame):
	print("Ending game.\nBye!!")
	exit(2)

def newGameHandler(signum, frame):
	print("Resetting Board\n")
	del gameBoard
	gameBoard = board()
	print(str(gameBoard) + '\n')

gameBoard = board()
signal.signal(signal.SIGINT, quitHandler) #Link ctrl-c interrupt to handler
signal.signal(signal.SIGQUIT, newGameHandler) #Link ctrl-\ intterupt to handler

print("Input example for middle spot (row, col):\n\tPlay On: 2 2")
while(gameBoard.isPlayable()):
	print("Turn:\t%d\n" % gameBoard.turn+1)
	print(gameBoard)
	playerIn = input("Play On: ").split(' ', 2)
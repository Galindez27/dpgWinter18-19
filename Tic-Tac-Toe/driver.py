from obFile import *
import signal
import time
import os

# In[0]
# Determine OS and setup clear command
plat = os.uname()[0]
clearCommand = ""
if (plat == "Linux" or plat == "macOS"):
	clearCommand = "clear"
elif plat == "Windows":
	clearCommand = "cls"
else:
	print("Unknown OS! Use without frame clearing.\n")

os.system(clearCommand)

# In[1]
gameBoard = board() # Game Board object to be used in play
continuePlay = True # Used to end play from user

# In[2]
# Signal Handlers and linking them to ctrl keys
def quitHandler(signum, frame):
	print("Ending game.\nBye!!")
	exit(2)

def newGameHandler(signum, frame):
	global gameBoard
	print("Resetting Board\n")
	del gameBoard
	gameBoard = board()
	print(str(gameBoard) + '\n')

signal.signal(signal.SIGINT, quitHandler) #Link ctrl-c interrupt to quit handler
signal.signal(signal.SIGQUIT, newGameHandler) #Link ctrl-\ intterupt to new game handler


# In[3]
# Gameplay
print("Input example for middle spot (row, col):\n\tPlay On: 2 2\nIgnore the 0 at the top of the frame.\n")
while(gameBoard.isPlayable() and continuePlay):
	print("Player %d's turn\n" % (gameBoard.turn+1))
	print(gameBoard)
	playerIn = input("Play On: ").split(' ', 2)
	inLen = len(playerIn)

	if inLen == 2:
		try:
			gameBoard.playOn(int(playerIn[0]), int(playerIn[1]))
		except occupiedSpace:
			print("ERROR: Space already occupied!\n")
			time.sleep(1)
		except badInput:
			print("ERROR: Bad input coordinates!\n")
			time.sleep(1)
		except wonGame:
			print("Player %d Won!\n\n" % (gameBoard.turn + 1))
			while(True):
				cont = input("Start a new game? [y/n]: ")
				try:
					if cont.lower()[0] == 'y':
						newGameHandler(0,0)
						break
					elif cont.lower()[0] == 'n':
						print("Quitting.\n")
						continuePlay = False
						exit(gameBoard.turn)
					else:
						raise Exception()
				except:
					print("ERROR: Bad input.\n")
					del cont
					sleep(1)

	elif inLen > 2:
		print("ERROR: Too many inputs.\n")
	else:
		print("ERROR: Too few inputs.\n")

	del playerIn
	del inLen 
	os.system(clearCommand)

print("Ending game.\nBye!!")
exit(1)
import board
import pygame
import time

constMul = 19
constSize = 50
sleepTime = 0
random1constant0 = 0
percentOfAlive = 3

game = board.Board(constSize, constSize)

game.SetConstBoard()
if random1constant0 == 1:
    game.SetRandomBoard(percentOfAlive)


#print(game.Width())
# print(game.Height())

# print(game.GetPixelState(3,3))

# try:
#     print(game.GetPixelState(16,16))
# except:
#     print("Argument exception")
# import pygame

pygame.init()
gameDisplay = pygame.display.set_mode((constMul*constSize,constMul*constSize))

white = (255,255,255)
black  = (0,0,0)

gameExit = False


while not gameExit:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            gameExit = True
    
    gameDisplay.fill(black)


    time.sleep(sleepTime) #zmniejsza użycie procesora


    for heightArg in range(0,game.Height()):
        for widthArg in range(0,game.Width()):
            if game.GetPixelState(heightArg,widthArg) > 0:
                pygame.draw.rect(gameDisplay, (game.GetPixelState(heightArg,widthArg), 255*(1==(game.GetPixelState(heightArg,widthArg))), 0 ), [heightArg * constMul ,widthArg * constMul,constMul*1,constMul*1])
    game.Update()
    pygame.display.update()


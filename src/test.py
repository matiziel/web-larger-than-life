import board
import pygame
import time

constMul = 10
constSize = 64
game = board.Board(constSize, constSize)
game.SetConstBoard()


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
    
    gameDisplay.fill(white)
    game.Update()
    time.sleep(1) #zmniejsza użycie procesora
    for heightArg in range(0,game.Height()):
        for widthArg in range(0,game.Width()):
            if game.GetPixelState(heightArg,widthArg) == 1:
                pygame.draw.rect(gameDisplay, black, [heightArg * constMul ,widthArg * constMul,constMul*1,constMul*1])
    pygame.display.update()


import grid
import pygame

game = grid.Grid(256, 256)
game.SetRandomGrid()

#print(game.Width())
# print(game.Height())

# print(game.GetPixelState(3,3))

# try:
#     print(game.GetPixelState(16,16))
# except:
#     print("Argument exception")
# import pygame

pygame.init()
gameDisplay = pygame.display.set_mode((5*256,5*256))

white = (255,255,255)
black  = (0,0,0)

gameExit = False

while not gameExit:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            gameExit = True
    
    gameDisplay.fill(white)
    for heightArg in range(game.Height()):
        for widthArg in range(game.Width()):
            if game.GetPixelState(heightArg,widthArg) == 1:
                pygame.draw.rect(gameDisplay, black, [heightArg * 5 ,widthArg * 5,5*1,5*1])
    pygame.display.update()


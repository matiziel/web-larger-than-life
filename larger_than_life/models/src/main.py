import board
import pygame
import time
import json

constMul = 3 
constSize = 300
sleepTime = 0.02
random1constant0 = 0
percentOfAlive = 50

Moore = 0
Neumann = 1
Circular = 2

game = board.Board(constSize, constSize)

game.SetConstBoard()
if random1constant0 == 1:
    game.SetRandomBoard(percentOfAlive)

nameOfFile = input("Enter name of file:")

try:
    with open("./rules/{}.json".format(nameOfFile), "r") as jsonFileRules:
        data = json.load(jsonFileRules)
        game.SetRules(data["range"], data["numberOfStates"], data["middleCell"], data["survivalMin"], data["survivalMax"], data["birthMin"], data["birthMax"], data["neighbourhoodType"])
except:
    print("Cannot open file, setting default rules\n")
    game.SetRules(6,0,0,2,3,3,3,Moore)

pygame.init()
gameDisplay = pygame.display.set_mode((constMul*constSize,constMul*constSize))

white = (255,255,255)
black  = (0,0,0)

gameExit = False
i=0

while not gameExit:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            gameExit = True
    
    gameDisplay.fill(black)


    time.sleep(sleepTime) #zmniejsza użycie procesora

    print(i)
    i+=1
    for heightArg in range(0,game.Height()):
        for widthArg in range(0,game.Width()):

            if game.GetPixelState(heightArg,widthArg) >0:
                pygame.draw.rect(gameDisplay, (255,255,game.GetPixelState(heightArg,widthArg)) , [heightArg * constMul ,widthArg * constMul,constMul*1,constMul*1])
    game.Update()
    pygame.display.update()


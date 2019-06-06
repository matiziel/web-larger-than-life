from larger_than_life import app
from flask import render_template
from larger_than_life.models.src import board
import json
import random

constSize = 256
constMul = 4
gameBoard = board.Board(constSize, constSize)
gameBoard.SetConstBoard()


try:
    with open("./../models/src/rules/Gnarl.json", "r") as jsonFileRules:
        data = json.load(jsonFileRules)
        gameBoard.SetRules(data["range"], data["numberOfStates"], data["middleCell"], data["survivalMin"], data["survivalMax"], data["birthMin"], data["birthMax"], data["neighbourhoodType"])
except:
    print("Cannot open file, setting default rules\n")
    gameBoard.SetRules(1,0,0,2,3,3,3,0)


@app.route('/')
def index():
    appName = "Larger Than Life"
    return render_template('index.html', title=appName)

@app.route('/game')
def game():
    appName = "Larger Than Life"
    return render_template('game.html', title=appName, boardHeight=constMul*constSize, boardWidth=constMul*constSize, mul=constMul)

@app.route('/test')
def test():
    return str(random.randint(0,100))

@app.route('/gameData')
def gameData():
    gameBoard.Update()
    retJson = []
    for i in range(constSize):
        retJson.append([])
        for j in range(constSize):
            retJson[i].append(gameBoard.GetPixelState(i,j))
    return json.dumps(retJson)
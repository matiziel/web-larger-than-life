from larger_than_life import app
from flask import render_template
from larger_than_life.models.src import board
import json
import time
import random

constSize = 256
constMul = 4
gameBoard = board.Board(constSize, constSize)
#gameBoard.SetConstBoard()
gameBoard.SetRandomBoard(50)

try:
    with open("./larger_than_life/models/src/rules/Bosco.json", "r") as jsonFileRules:
        data = json.load(jsonFileRules)
        gameBoard.SetRules(data["range"], data["numberOfStates"], data["middleCell"], data["survivalMin"], data["survivalMax"], data["birthMin"], data["birthMax"], data["neighbourhoodType"])
except:
    print("Cannot open file, setting default rules\n")
    gameBoard.SetRules(1,0,0,2,3,3,3,0)

@app.route('/', methods=['GET','POST'])
def index():
    appName = "Larger Than Life"
    return render_template('index.html', title=appName)

@app.route('/game/<rule>')
def game(rule):
    try:
        with open("./larger_than_life/models/src/rules/{}.json".format(rule), "r") as jsonFileRules:
            data = json.load(jsonFileRules)
            gameBoard.SetRules(data["range"], data["numberOfStates"], data["middleCell"], data["survivalMin"], data["survivalMax"], data["birthMin"], data["birthMax"], data["neighbourhoodType"])
    except:
        print("Cannot open file, setting default rules\n")
        gameBoard.SetRules(1,0,0,2,3,3,3,0)
    appName = "Larger Than Life"
    return render_template('game.html', title=appName, boardHeight=constMul*constSize, boardWidth=constMul*constSize, mul=constMul, constRule=rule)

@app.route('/gameData')
def gameData():
    gameBoard.Update()
    retJson = []
    for i in range(constSize):
        retJson.append([])
        for j in range(constSize):
            retJson[i].append(gameBoard.GetPixelState(i,j))

    return json.dumps(retJson)
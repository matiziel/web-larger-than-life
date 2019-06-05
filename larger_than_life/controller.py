from larger_than_life import app
from flask import render_template
from larger_than_life.models.src import board

@app.route('/')
def index():
    appName = "Larger Than Life"
    return render_template('index.html', title=appName)

@app.route('/game')
def game():
    appName = "Larger Than Life"
    return render_template('game.html', title=appName, boardHeight=1024, boardWidth=1024)
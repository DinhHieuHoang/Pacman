import turtle
import time

wn = turtle.Screen()
wn.bgcolor("black")
wn.title("Pacman")
wn.setup(1300, 700)

class Pen(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("white")
        self.penup()
        self.speed(0)

class Pacman(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("yellow")
        self.penup()
        self.speed(0)

    def goUp(self):
        self.goto(self.xcor(), self.ycor() + 24)

    def goDown(self):
        self.goto(self.xcor(), self.ycor() - 24)

    def goLeft(self):
        self.goto(self.xcor() - 24, self.ycor())

    def goRight(self):
        self.goto(self.xcor() + 24, self.ycor())

class Monster(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("red")
        self.penup()
        self.speed(0)

class Food(turtle.Turtle):
    def __init__(self):
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("green")
        self.penup()
        self.speed(0)






# 15x15 block with 700x700 screen -> center of the first block will be -340, 340

mapFile = open("input.txt", "r")
mapFile.readline()
mapFile.readline()
maze = mapFile.readlines()

moveFile = open("moveList.txt", "r")
move = moveFile.readline()

for i in range(len(maze)):
    maze[i] = maze[i].replace(' ', '')

move = move.replace(' ', '')

def setupMaze(maze):
    for y in range(len(maze)):
        for x in range(len(maze[y])):
            character = maze[y][x]

            xPos = -340 + 24*x
            yPos = 340 - 24*y

            if character == "0":
                pen.goto(xPos, yPos)
                pen.stamp()
            
            if character == "3":
                pacman.goto(xPos, yPos)

            if character == "4":
                monster.goto(xPos, yPos)
                monster.stamp()

            if character == "1":
                food.goto(xPos, yPos)
                food.stamp()


pen = Pen()
pen.goto(-1000, -1000)
pacman = Pacman()
pacman.goto(-1000, -1000)
food = Food()
food.goto(-1000, -1000)
monster = Monster()
monster.goto(-1000, -1000)

setupMaze(maze)

for i in range(len(move)):
    if (move[i] == '0'):
        pacman.goUp()
    elif (move[i] == '1'):
        pacman.goRight()
    elif (move[i] == '2'):
        pacman.goDown()
    elif move[i] == '3':
        pacman.goLeft()

    time.sleep(0.5)

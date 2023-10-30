from pyamaze import maze, COLOR, agent
from numpy import random
from math import *
import time

""" 定义常量 """
ROW = 30
COLUMN = 30
LOOPPERCENT = 50
DIRECTIONS = ['N', 'S', 'W', 'E']
INDIVIDUALSNUM = 50  # 一代中个体数目
HERITABILITY = 0.2  # 遗传个体比率
ITERATENUM = 50  # 迭代次数

""" 定义变量 """
LastPoint = [1, 1]
OptimalPath = []  # 存储当前最优路径
AlterTropism = {}  # 趋向度改变值

""" 计算曼哈顿距离 """
def Manhattan(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)

""" 计算欧几里得距离 """
def Euclid(x1, y1, x2, y2):
    return sqrt(abs(x1 ** 2 - x2 ** 2) + abs(y1 ** 2 - y2 ** 2))

""" 轮盘赌计算概率 """
def Roulette(EventList, ProList):
    EventListIndex = range(len(EventList))
    return EventList[random.choice(EventListIndex, p = ProList)]

""" 初始化迷宫 """
def MazeInit():
    global Maze, Agent
    Maze = maze(ROW, COLUMN)
    Maze.CreateMaze(ROW, COLUMN, theme = COLOR.dark, loopPercent = LOOPPERCENT)
    Agent = agent(Maze, x = 1, y = 1, goal = (ROW, COLUMN), footprints = True)

""" 初始化趋向度（T） """
def TropismInit():
    # 定义趋向度（T）公式为(Manhattan ^ 2) * Euclid
    global Tropism
    Tropism = {}
    for i in range(ROW):
        for j in range(COLUMN):
            Tropism.update({(i + 1, j + 1): Manhattan(1, 1, i + 1, j + 1) + Euclid(1, 1, i + 1, j + 1) ** 0.1})
            AlterTropism.update({(i + 1, j + 1): 0})


""" 减弱趋向度（T） """
def WaneTropism(Row, Column):
    Tropism[(Row, Column)] -= Tropism[(Row, Column)] - 0.01


""" 增强趋向度（T） """
def AddTropism(PathList):
    for Unit in PathList:
        AlterTropism[Unit] += (ROW + COLUMN) / len(PathList) + Tropism[Unit]


""" 更新趋向度（T） """
def UpdateTropism():
    for i in range(ROW):
        for j in range(COLUMN):
            Tropism[(i + 1, j + 1)] += AlterTropism[(i + 1, j + 1)]
            AlterTropism.update({(i + 1, j + 1): 0})

""" 判断生物移动方向 """
def SingleMovement(Row, Column):
    DirectionsList = []
    ProList = []
    TotalTropism = 0

    WaneTropism(Row, Column)

    for Direction in DIRECTIONS:
        if Maze.maze_map[(Row, Column)][Direction] == 1:
            match Direction:
                case 'N':
                    if tuple(LastPoint) != (Row - 1, Column):
                        DirectionsList.append((Row - 1, Column))
                        TotalTropism += Tropism[(Row - 1, Column)]
                case 'S':
                    if tuple(LastPoint) != (Row + 1, Column):
                        DirectionsList.append((Row + 1, Column))
                        TotalTropism += Tropism[(Row + 1, Column)]
                case 'W':
                    if tuple(LastPoint) != (Row, Column - 1):
                        DirectionsList.append((Row, Column - 1))
                        TotalTropism += Tropism[(Row, Column - 1)]
                case 'E':
                    if tuple(LastPoint) != (Row, Column + 1):
                        DirectionsList.append((Row, Column + 1))
                        TotalTropism += Tropism[(Row, Column + 1)]

    if len(DirectionsList) != 0:
        for Direction in DirectionsList:
            ProList.append(Tropism[Direction] / TotalTropism)
        Path.append(Roulette(DirectionsList, ProList))
        LastPoint[0] = Row
        LastPoint[1] = Column
        return True

    return False

""" 生物一代中的移动 """
def GenerationMovement(Row, Column):
    Paths = {}
    IndividualNum = 0
    if OptimalPath:
        Paths.update({tuple(OptimalPath): len(OptimalPath)})
    while IndividualNum <= INDIVIDUALSNUM:
        global Path
        Path = []
        Step = 0
        Row = 1
        Column = 1
        while Step <= ROW * COLUMN:
            if SingleMovement(Row, Column):
                Row = Path[len(Path) - 1][0]
                Column = Path[len(Path) - 1][1]
                if Row == ROW and Column == COLUMN:
                    if len(Paths) <= INDIVIDUALSNUM * HERITABILITY:
                        Paths.update({tuple(Path): len(Path)})
                    else:
                        if len(Path) < Paths[list(Paths.keys())[-1]]:
                            Paths.pop(list(Paths.keys())[-1])
                            Paths.update({tuple(Path): len(Path)})
                    PathsList = sorted(Paths.items(), key=lambda x: x[-1])
                    Paths.clear()
                    for path in PathsList:
                        Paths.update({tuple(path[0]): path[1]})
                Step += 1
            else:
                break

        if len(list(Paths.keys())) != 0:
            OptimalPath.clear()
            for Unit in list(Paths.keys())[0]:
                OptimalPath.append(Unit)
        for path in Paths.keys():
            AddTropism(list(path))
        UpdateTropism()
        IndividualNum += 1

if __name__ == '__main__':
    MazeInit()
    TropismInit()
    T1 = time.time()
    IterateNum = 0
    while True:
        while IterateNum <= ITERATENUM:
            GenerationMovement(1, 1)
            IterateNum += 1
        if len(OptimalPath) == 0:
            IterateNum -= 3
        else:
            break
    T2 = time.time()
    print(T2 - T1)
    print(len(OptimalPath))
    Maze.tracePath({Agent: OptimalPath}, delay = 10)
    Maze.run()
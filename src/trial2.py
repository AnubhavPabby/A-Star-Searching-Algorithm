import math
class cell():

    def __init__(self, start=None, end=None):
        self.start = start
        self.end = end

        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.end == other.end

def isinvalid(maze, node_end):
    if node_end[0] > (len(maze) - 1) or node_end[0] < 0 or node_end[1] > (len(maze[len(maze)-1]) -1) or node_end[1] < 0:
        return True
    else:
        return False

def isBlocked(maze,node_end):
    if(maze[node_end[0]][node_end[1]] != 0):
        return True
    else:
        return False

def isDestination(start, end):
    if(start[0] == end[0] and start[1] == end[1]):
        print("We are already at destination.")
        return True
    else:
        return False

def astar(maze, start, end):

    start_cell = cell(None, start)
    start_cell.g = 0
    start_cell.h = 0
    start_cell.f = 0
    end_cell = cell(None, end)
    end_cell.g = 0
    end_cell.h = 0
    end_cell.f = 0

    if(isDestination(start,end)):
        return

    open_list = []
    closed_list = []

    open_list.append(start_cell)

    while len(open_list) > 0:
        curr = open_list[0]
        current_index = 0
        for index, item in enumerate(open_list):
            if item.f < curr.f:
                curr = item
                current_index = index

        open_list.pop(current_index)
        closed_list.append(curr)

        if curr == end_cell:
            path = []
            current = curr
            while current is not None:
                path.append(current.end)
                current = current.start
            return path[::-1]

        cell_position = []
        successor = [(0, -1), (0, 1), (-1, 0), (1, 0), (-1, -1), (-1, 1), (1, -1), (1, 1)]
        for new_end in successor:

            node_end = (curr.end[0] + new_end[0], curr.end[1] + new_end[1])

            if isinvalid(maze,node_end):
                continue

            if maze[node_end[0]][node_end[1]] != 0:
                continue

            new_node = cell(curr, node_end)

            cell_position.append(new_node)


        for item1 in cell_position:

            for closed_child in closed_list:
                if item1 == closed_child:
                    continue

            item1.g = curr.g + 1
            item1.h = math.sqrt(((item1.end[0] - end_cell.end[0]) ** 2) + ((item1.end[1] - end_cell.end[1]) ** 2))
            item1.f = item1.g + item1.h

            for open_node in open_list:
                if item1 == open_node and item1.f > open_node.f:
                    continue

            open_list.append(item1)



maze = [[0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]

start = (0, 0)
end = (7, 6)

path = astar(maze, start, end)
print(path)
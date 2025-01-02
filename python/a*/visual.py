import pygame
import heapq
import random

# Constants
WIDTH, HEIGHT = 1200, 800
GRID_ROWS = 80  # Number of rows in the grid
GRID_COLS = 120  # Number of columns in the grid
FPS = 60

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (169, 169, 169)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
ORANGE = (255, 165, 0)  # Color to show maze generation process
PURPLE = (128, 0, 128)  # Color to show evaluated nodes
BROWN = (139, 69, 19)   # Color for obstacles

class Node:
    def __init__(self, position, parent=None):
        self.position = position
        self.parent = parent
        self.g = 0
        self.h = 0
        self.f = 0

    def __lt__(self, other):
        return self.f < other.f

def prims_algorithm(rows, cols, screen):
    maze = [[1] * cols for _ in range(rows)]
    walls = []
    start_x, start_y = 0, 0
    maze[start_x][start_y] = 0
    for dx, dy in [(-2, 0), (2, 0), (0, -2), (0, 2)]:
        nx, ny = start_x + dx, start_y + dy
        if 0 <= nx < rows and 0 <= ny < cols:
            walls.append(((start_x, start_y), (nx, ny)))

    while walls:
        pygame.event.pump()
        wall = random.choice(walls)
        x1, y1 = wall[0]
        x2, y2 = wall[1]
        walls.remove(((x1, y1), (x2, y2)))
        if maze[x2][y2] == 1:
            maze[x2][y2] = 0
            maze[(x1 + x2) // 2][(y1 + y2) // 2] = 0
            for dx, dy in [(-2, 0), (2, 0), (0, -2), (0, 2)]:
                nx, ny = x2 + dx, y2 + dy
                if 0 <= nx < rows and 0 <= ny < cols and maze[nx][ny] == 1:
                    walls.append(((x2, y2), (nx, ny)))
        screen.fill(GRAY)
        draw_grid(screen, maze, (0, 0), (cols - 1, rows - 1), [])
        draw_walls(screen, walls)
        pygame.display.flip()
        pygame.time.delay(10)  # Slow down the maze generation process for visualization

    return maze

def draw_grid(screen, grid, start, goal, path, open_list=None, closed_list=None, obstacles=None):
    cell_size = min(screen.get_width() // GRID_COLS, screen.get_height() // GRID_ROWS)
    for x in range(len(grid)):
        for y in range(len(grid[0])):
            rect = pygame.Rect(y * cell_size, x * cell_size, cell_size, cell_size)
            if (x, y) == start:
                pygame.draw.rect(screen, GREEN, rect)
            elif (x, y) == goal:
                pygame.draw.rect(screen, RED, rect)
            elif grid[x][y] == 1:
                pygame.draw.rect(screen, BLACK, rect)
            elif (x, y) in path:
                pygame.draw.rect(screen, BLUE, rect)
            elif obstacles and (x, y) in obstacles:
                pygame.draw.rect(screen, BROWN, rect)  # Show obstacles
            elif open_list and (x, y) in open_list:
                pygame.draw.rect(screen, PURPLE, rect)  # Show open list nodes
            elif closed_list and (x, y) in closed_list:
                pygame.draw.rect(screen, ORANGE, rect)  # Show closed list nodes
            else:
                pygame.draw.rect(screen, WHITE, rect)
            pygame.draw.rect(screen, GRAY, rect, 1)

def draw_walls(screen, walls):
    cell_size = min(screen.get_width() // GRID_COLS, screen.get_height() // GRID_ROWS)
    for (x1, y1), (x2, y2) in walls:
        rect1 = pygame.Rect(y1 * cell_size, x1 * cell_size, cell_size, cell_size)
        rect2 = pygame.Rect(y2 * cell_size, x2 * cell_size, cell_size, cell_size)
        pygame.draw.rect(screen, ORANGE, rect1)
        pygame.draw.rect(screen, ORANGE, rect2)

def get_neighbors(position, grid_rows, grid_cols):
    x, y = position
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]
    neighbors = []

    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < grid_rows and 0 <= ny < grid_cols:
            neighbors.append((nx, ny))

    return neighbors

def a_star_algorithm(start, goal, grid, screen, obstacles):
    open_list = []
    closed_list = set()
    open_nodes = set()  # To visualize nodes in the open list
    closed_nodes = set()  # To visualize nodes in the closed list
    start_node = Node(start)
    goal_node = Node(goal)
    
    heapq.heappush(open_list, start_node)
    open_nodes.add(start)

    while open_list:
        pygame.event.pump()
        current_node = heapq.heappop(open_list)
        closed_list.add(current_node.position)
        open_nodes.discard(current_node.position)
        closed_nodes.add(current_node.position)
        
        if current_node.position == goal_node.position:
            path = []
            while current_node:
                path.append(current_node.position)
                current_node = current_node.parent
            return path[::-1]
        
        neighbors = get_neighbors(current_node.position, len(grid), len(grid[0]))
        
        for next_position in neighbors:
            if next_position in closed_list:
                continue
            
            if grid[next_position[0]][next_position[1]] == 1 or next_position in obstacles:
                continue
            
            neighbor_node = Node(next_position, current_node)
            neighbor_node.g = current_node.g + (1 if (next_position[0] == current_node.position[0] or next_position[1] == current_node.position[1]) else 1.414)  # Diagonal distance cost
            neighbor_node.h = abs(neighbor_node.position[0] - goal_node.position[0]) + abs(neighbor_node.position[1] - goal_node.position[1])
            neighbor_node.f = neighbor_node.g + neighbor_node.h
            
            if any(node.position == neighbor_node.position and node.f < neighbor_node.f for node in open_list):
                continue
            
            heapq.heappush(open_list, neighbor_node)
            open_nodes.add(next_position)
        
        screen.fill(GRAY)
        draw_grid(screen, grid, start, goal, [], open_nodes, closed_list, obstacles)
        pygame.display.flip()
        pygame.time.delay(50)  # Slow down the pathfinding process for visualization

    return []

def main():
    global WIDTH, HEIGHT, GRID_ROWS, GRID_COLS
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.RESIZABLE)
    pygame.display.set_caption("A* Pathfinding")
    clock = pygame.time.Clock()

    rows = GRID_ROWS
    cols = GRID_COLS
    grid = prims_algorithm(rows, cols, screen)  # Generate the maze
    start = (0, 0)
    goal = (cols - 1, rows - 1)
    path = []  # Initialize path as an empty list
    obstacles = set()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_k:
                    rows = max(10, screen.get_height() // (min(screen.get_width(), screen.get_height()) // GRID_ROWS))
                    cols = max(10, screen.get_width() // (min(screen.get_width(), screen.get_height()) // GRID_COLS))
                    grid = prims_algorithm(rows, cols, screen)  # Regenerate maze
                    start = (0, 0)
                    goal = (cols - 1, rows - 1)
                    path = []  # Reset path
                    obstacles = set()
                elif event.key == pygame.K_r:
                    path = a_star_algorithm(start, goal, grid, screen, obstacles)
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                cell_size = min(screen.get_width() // GRID_COLS, screen.get_height() // GRID_ROWS)
                x, y = x // cell_size, y // cell_size
                if event.button == 1:  # Left click
                    if (0 <= x < cols) and (0 <= y < rows):
                        start = (y, x)
                        path = a_star_algorithm(start, goal, grid, screen, obstacles)
                elif event.button == 3:  # Right click
                    if (0 <= x < cols) and (0 <= y < rows):
                        goal = (y, x)
                        path = a_star_algorithm(start, goal, grid, screen, obstacles)
                elif event.button == 2:  # Middle click
                    if (0 <= x < cols) and (0 <= y < rows):
                        if (y, x) in obstacles:
                            obstacles.remove((y, x))
                        else:
                            obstacles.add((y, x))
                        path = a_star_algorithm(start, goal, grid, screen, obstacles)

        screen.fill(GRAY)
        draw_grid(screen, grid, start, goal, path, obstacles=obstacles)
        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()

if __name__ == "__main__":
    main()
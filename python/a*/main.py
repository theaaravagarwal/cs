#python 3
import pygame
import heapq
import random

WIDTH, HEIGHT = 1600, 1200
GRID_ROWS, GRID_COLS = 60, 60  # Define number of rows and columns
FPS = 60
ANIMATION_SPEED = "instant"
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (169, 169, 169)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

class Node:
    def __init__(self, position, parent=None):
        self.position = position
        self.parent = parent
        self.g = 0
        self.h = 0
        self.f = 0

    def __lt__(self, other):
        return self.f < other.f

def generate_maze(rows, cols):
    maze = [[1] * cols for _ in range(rows)]
    stack = [(0, 0)]
    maze[0][0] = 0

    while stack:
        x, y = stack[-1]
        neighbors = []

        for dx, dy in [(2, 0), (-2, 0), (0, 2), (0, -2), (2, 2), (2, -2), (-2, 2), (-2, -2)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < rows and 0 <= ny < cols and maze[nx][ny] == 1:
                if abs(dx) == 2 and abs(dy) == 2:
                    mx, my = (x + nx) // 2, (y + ny) // 2
                    if maze[mx][my] == 0:
                        neighbors.append((nx, ny))
                else:
                    neighbors.append((nx, ny))

        if neighbors:
            nx, ny = random.choice(neighbors)
            maze[nx][ny] = 0
            if abs(nx - x) == 2:
                maze[(x + nx) // 2][y] = 0
            if abs(ny - y) == 2:
                maze[x][(y + ny) // 2] = 0
            stack.append((nx, ny))
        else:
            stack.pop()

    return maze

def get_neighbors(position, rows, cols):
    x, y = position
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]
    neighbors = []

    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < rows and 0 <= ny < cols:
            neighbors.append((nx, ny))

    return neighbors

def a_star_algorithm(start, goal, grid):
    open_list = []
    closed_list = set()
    start_node = Node(start)
    goal_node = Node(goal)
    
    heapq.heappush(open_list, start_node)
    
    while open_list:
        current_node = heapq.heappop(open_list)
        closed_list.add(current_node.position)
        
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
            
            if grid[next_position[0]][next_position[1]] == 1:
                continue
            
            neighbor_node = Node(next_position, current_node)
            neighbor_node.g = current_node.g + (1 if (next_position[0] == current_node.position[0] or next_position[1] == current_node.position[1]) else 1.414)
            neighbor_node.h = abs(neighbor_node.position[0] - goal_node.position[0]) + abs(neighbor_node.position[1] - goal_node.position[1])
            neighbor_node.f = neighbor_node.g + neighbor_node.h
            
            if any(node.position == neighbor_node.position and node.f < neighbor_node.f for node in open_list):
                continue
            
            heapq.heappush(open_list, neighbor_node)
    
    return []

def draw_grid(screen, grid, start, goal, path, path_index):
    cell_width = screen.get_width() // GRID_COLS
    cell_height = screen.get_height() // GRID_ROWS
    for x in range(GRID_ROWS):
        for y in range(GRID_COLS):
            rect = pygame.Rect(y * cell_width, x * cell_height, cell_width, cell_height)
            if (x, y) == start:
                pygame.draw.rect(screen, GREEN, rect)
            elif (x, y) == goal:
                pygame.draw.rect(screen, RED, rect)
            elif grid[x][y] == 1:
                pygame.draw.rect(screen, BLACK, rect)
            elif (x, y) in path[:path_index + 1]:
                pygame.draw.rect(screen, BLUE, rect)
            else:
                pygame.draw.rect(screen, WHITE, rect)
            pygame.draw.rect(screen, GRAY, rect, 1)
    
    pygame.draw.circle(screen, GREEN, (start[1] * cell_width + cell_width // 2, start[0] * cell_height + cell_height // 2), min(cell_width, cell_height) // 4)
    pygame.draw.circle(screen, RED, (goal[1] * cell_width + cell_width // 2, goal[0] * cell_height + cell_height // 2), min(cell_width, cell_height) // 4)

def main():
    global WIDTH, HEIGHT, GRID_ROWS, GRID_COLS
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.RESIZABLE)
    pygame.display.set_caption("A*")
    clock = pygame.time.Clock()

    rows, cols = GRID_ROWS, GRID_COLS
    grid = generate_maze(rows, cols)
    start = (0, 0)
    goal = (rows - 2, cols - 2)
    path = []
    path_index = 0
    show_path_animation = False
    editing_maze = False

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_k:
                    grid = generate_maze(rows, cols)
                    start = (0, 0)
                    goal = (rows - 1, cols - 1)
                    path = []
                    path_index = 0
                    show_path_animation = False
                elif event.key == pygame.K_r:
                    path = a_star_algorithm(start, goal, grid)
                    show_path_animation = True
                elif event.key == pygame.K_l:
                    # Clear grid (make all cells empty)
                    grid = [[0] * cols for _ in range(rows)]
                    start = (0, 0)
                    goal = (rows - 2, cols - 2)
                    path = []
                    path_index = 0
                    show_path_animation = False
                    editing_maze = True  # Enter maze editing mode
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                cell_width = screen.get_width() // GRID_COLS
                cell_height = screen.get_height() // GRID_ROWS
                x, y = x // cell_width, y // cell_height
                if event.button == 1:  # Left click
                    if (0 <= x < cols) and (0 <= y < rows):
                        if editing_maze:
                            grid[y][x] = 1 if grid[y][x] == 0 else 0  # Toggle obstacle
                        else:
                            start = (y, x)
                            path = a_star_algorithm(start, goal, grid)
                            path_index = 0
                            show_path_animation = True
                elif event.button == 3:  # Right click
                    if (0 <= x < cols) and (0 <= y < rows):
                        goal = (y, x)
                        path = a_star_algorithm(start, goal, grid)
                        path_index = 0
                        show_path_animation = True

        screen.fill(GRAY)

        if show_path_animation:
            if ANIMATION_SPEED == "instant":
                path_index = len(path) - 1
                show_path_animation = False
            else:
                path_index = min(path_index + ANIMATION_SPEED, len(path) - 1)
                if path_index >= len(path) - 1:
                    show_path_animation = False

        draw_grid(screen, grid, start, goal, path, path_index)
        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()

if __name__ == "__main__":
    main()

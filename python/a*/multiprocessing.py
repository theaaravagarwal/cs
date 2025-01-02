import pygame
import heapq
import random
import multiprocessing as mp

# Constants
WIDTH, HEIGHT = 1600, 1200
GRID_SIZE = 100
FPS = 60
ANIMATION_SPEED = 4  # Number of frames to reveal each path segment

# Colors
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

def generate_maze_segment(start_x, end_x, grid_size):
    maze_segment = [[1] * grid_size for _ in range(grid_size)]
    stack = [(start_x, 0)]
    maze_segment[start_x][0] = 0

    while stack:
        x, y = stack[-1]
        neighbors = []

        for dx, dy in [(2, 0), (-2, 0), (0, 2), (0, -2), (2, 2), (2, -2), (-2, 2), (-2, -2)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < grid_size and 0 <= ny < grid_size and maze_segment[nx][ny] == 1:
                # Check if there's already a path in the middle
                if abs(dx) == 2 and abs(dy) == 2:
                    mx, my = (x + nx) // 2, (y + ny) // 2
                    if maze_segment[mx][my] == 0:
                        neighbors.append((nx, ny))
                else:
                    neighbors.append((nx, ny))

        if neighbors:
            nx, ny = random.choice(neighbors)
            maze_segment[nx][ny] = 0
            if abs(nx - x) == 2:
                maze_segment[(x + nx) // 2][y] = 0
            if abs(ny - y) == 2:
                maze_segment[x][(y + ny) // 2] = 0
            stack.append((nx, ny))
        else:
            stack.pop()

    return maze_segment

def combine_segments(segments, grid_size):
    maze = [[1] * grid_size for _ in range(grid_size)]
    segment_size = len(segments[0])  # Assume all segments are of the same size

    for i, segment in enumerate(segments):
        start_x = i * segment_size
        end_x = min(start_x + segment_size, grid_size)
        
        for x in range(segment_size):
            for y in range(len(segment[x])):
                maze_x = start_x + x
                if maze_x < grid_size:
                    maze[maze_x][y] = segment[x][y]
                else:
                    print(f"Index out of bounds: start_x={start_x}, x={x}, grid_size={grid_size}")

    return maze

def generate_maze(grid_size):
    num_processes = mp.cpu_count()
    pool = mp.Pool(num_processes)
    segment_size = (grid_size + num_processes - 1) // num_processes
    tasks = [(i * segment_size, min((i + 1) * segment_size, grid_size), grid_size) for i in range(num_processes)]
    results = pool.starmap(generate_maze_segment, tasks)
    pool.close()
    pool.join()
    maze = combine_segments(results, grid_size)
    return maze

def get_neighbors(position, grid_size):
    x, y = position
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]
    neighbors = []

    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < grid_size and 0 <= ny < grid_size:
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
        
        neighbors = get_neighbors(current_node.position, len(grid))
        
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
    cell_size = min(screen.get_width(), screen.get_height()) // GRID_SIZE
    for x in range(len(grid)):
        for y in range(len(grid[0])):
            rect = pygame.Rect(x * cell_size, y * cell_size, cell_size, cell_size)
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
    
    pygame.draw.circle(screen, GREEN, (start[1] * cell_size + cell_size // 2, start[0] * cell_size + cell_size // 2), cell_size // 4)
    pygame.draw.circle(screen, RED, (goal[1] * cell_size + cell_size // 2, goal[0] * cell_size + cell_size // 2), cell_size // 4)

def main():
    global WIDTH, HEIGHT, GRID_SIZE
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.RESIZABLE)
    pygame.display.set_caption("A* Pathfinding")
    clock = pygame.time.Clock()

    grid_size = GRID_SIZE
    grid = generate_maze(grid_size)
    start = (0, 0)
    goal = (grid_size - 2, grid_size - 2)
    path = []
    path_index = 0
    show_path_animation = False

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_k:
                    grid = generate_maze(grid_size)
                    start = (0, 0)
                    goal = (grid_size - 1, grid_size - 1)
                    path = []
                    path_index = 0
                    show_path_animation = False
                elif event.key == pygame.K_r:
                    path = a_star_algorithm(start, goal, grid)
                    show_path_animation = True
            elif event.type == pygame.MOUSEBUTTONDOWN:
                x, y = pygame.mouse.get_pos()
                x, y = x // (min(screen.get_width(), screen.get_height()) // GRID_SIZE), y // (min(screen.get_width(), screen.get_height()) // GRID_SIZE)
                if event.button == 1:
                    if (0 <= x < grid_size) and (0 <= y < grid_size):
                        start = (x, y)
                        path = a_star_algorithm(start, goal, grid)
                        path_index = 0
                        show_path_animation = True
                elif event.button == 3:
                    if (0 <= x < grid_size) and (0 <= y < grid_size):
                        goal = (x, y)
                        path = a_star_algorithm(start, goal, grid)
                        path_index = 0
                        show_path_animation = True

        screen.fill(GRAY)

        if show_path_animation:
            path_index = min(path_index + ANIMATION_SPEED, len(path) - 1)
            if path_index >= len(path) - 1:
                show_path_animation = False

        draw_grid(screen, grid, start, goal, path, path_index)
        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()

if __name__ == "__main__":
    main()
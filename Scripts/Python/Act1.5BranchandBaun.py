import heapq

class Partial_sol:
    def __init__(self, x, y, path, collected_coins, bound):
        self.x = x  
        self.y = y 
        self.path = path  
        self.collected_coins = collected_coins  
        self.bound = bound  

    def __lt__(self, other):
        return self.bound > other.bound

def calculate_upper_bound(grid, x, y, collected_coins):

    n = len(grid)
    m = len(grid[0])
    max_remaining_coins = 0

    # upper bound son las monedas en el lado derecho y abajo del nodo actual o el final
    
    for i in range(x, n):
        for j in range(y, m):
            max_remaining_coins += grid[i][j]

    return collected_coins + max_remaining_coins

def branch_and_bound_coin_collecting(grid):

    n = len(grid)
    m = len(grid[0])
    pq = []
    start_node = Partial_sol(0, 0, [(0, 0, 'start', grid[0][0])], grid[0][0], calculate_upper_bound(grid, 0, 0, grid[0][0]))
    heapq.heappush(pq, start_node)

    best_solution = None
    best_coins = -1
    
    while pq:
        current = heapq.heappop(pq)

        if current.x == n - 1 and current.y == m - 1:
            if current.collected_coins > best_coins:
                best_coins = current.collected_coins
                best_solution = current.path
            continue
        
        if current.x + 1 < n:
            new_x = current.x + 1
            new_y = current.y
            new_path = current.path + [(new_x, new_y, 'abajo', grid[new_x][new_y])]
            new_collected_coins = current.collected_coins + grid[new_x][new_y]
            new_bound = calculate_upper_bound(grid, new_x, new_y, new_collected_coins)
            if new_bound > best_coins:  # Poda basada en el upper bound
                heapq.heappush(pq, Partial_sol(new_x, new_y, new_path, new_collected_coins, new_bound))
        
        if current.y + 1 < m:
            new_x = current.x
            new_y = current.y + 1
            new_path = current.path + [(new_x, new_y, 'derecha', grid[new_x][new_y])]
            new_collected_coins = current.collected_coins + grid[new_x][new_y]
            new_bound = calculate_upper_bound(grid, new_x, new_y, new_collected_coins)
            if new_bound > best_coins:  # Poda basada en el upper bound
                heapq.heappush(pq, Partial_sol(new_x, new_y, new_path, new_collected_coins, new_bound))
    
    
    if best_solution:
        path_directions = [f"{move[2]} ({move[3]})" for move in best_solution[1:]] 
        print(f"Mejor camino: {' -> '.join(path_directions)}. Total= {best_coins}")


def leer_instancias_archivo(filename):
    grid = []
    with open(filename, 'r') as f:
        for line in f:
            grid.append(list(map(int, line.strip().split())))
    return grid

filename = 'txt/entrada.txt'
grid = leer_instancias_archivo(filename)
branch_and_bound_coin_collecting(grid)

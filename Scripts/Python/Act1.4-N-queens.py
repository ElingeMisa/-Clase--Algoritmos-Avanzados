import queue
import copy

# Clase para representar soluciones parciales
class Partial_Sol:
    def __init__(self, lista, indef_index):
        self.lista = lista
        self.indef_index = indef_index

# Función para generar las soluciones hijas
def instantiate(parent, index, n):
    children = []

    for i in range(n):
        child = copy.deepcopy(parent)
        child.lista[index] = i
        child.indef_index += 1
        children.append(child)
    return children

# Función para verificar si una reina se puede colocar en una posición específica
def is_valid(sol, index):
    for i in range(index):
        if sol.lista[i] == sol.lista[index] or \
           abs(sol.lista[i] - sol.lista[index]) == abs(i - index):
            return False
    return True

# Función principal de backtracking para el problema de n-reinas
def n_queens(n):
    accepted = []
    fila = queue.Queue()

    root_sol = Partial_Sol([-1] * n, 0)
    fila.put(root_sol)

   
    while not fila.empty():
        solucion = fila.get()
        next_index = solucion.indef_index

        # Generar soluciones hijas
        hijas = instantiate(solucion, next_index, n)

        for hija in hijas:
            if is_valid(hija, next_index):
                if next_index == n - 1:
                    accepted.append(hija)
                else:
                    fila.put(hija)

    # Mostrar soluciones y cantidad total
    print(f"Se encontraron {len(accepted)} soluciones para {n}-queens.")
    for sol in accepted:
        for row in sol.lista:
            line = ['-'] * n
            line[row] = 'R'
            print('  '.join(line))
        print()

# Ejecutar el algoritmo para n = 4
n_queens(1)

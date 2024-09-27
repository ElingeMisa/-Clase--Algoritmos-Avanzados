# 1. Determina cuales son los dos puntos mas cercanos dadas sus coordenadas x, y


import math
# Leemos desde un archivo la primera linea para saber cuantos puntos hay y el resto del archivo lo asignamos a la variable coor
with open("Scripts/Python/filename2.txt") as file:
    n = int(file.readline().strip())
    # ciclo para leer los puntos
    coor = []
    for i in range(n):
        # se leen los puntos y se guardan en una lista de tuplas <- el mapa es para convertir los valores a flotantes
        x, y = map(float, file.readline().split())
        coor.append((x, y))

print("Buscando los puntos mas cercanos ...")

#distancia 
def distancia(p1, p2):
    return math.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

#punto con los demas
def matriz_distancias(coor):
    matriz = []

    for i in range(len(coor)):
        fila = []
        for j in range(len(coor)):
            fila.append(distancia(coor[i], coor[j]))
        matriz.append(fila)
    return matriz


matriz = matriz_distancias(coor)

distancias = []
for i in range(len(matriz)):

    distancias.append(min([matriz[i][j] for j in range(len(matriz)) if i != j]))

# salida

# inicia con un minimo infinito
minimo = float('inf')
for i in range(len(matriz)):
    for j in range(len(matriz)):
        if i != j and matriz[i][j] < minimo:
            punto1 = i
            punto2 = j
            minimo = matriz[i][j]

print("Puntos mas cercanos: ", punto1+1, "y", punto2+1, "con distancia de", minimo)



# complejidad del algoritmo O(n^2) donde n es la cantidad de puntos


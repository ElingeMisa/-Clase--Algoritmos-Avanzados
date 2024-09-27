# 1. Determina cuales son los dos puntos mas cercanos dadas sus coordenadas x, y


import math
# sin entrada
coor = [[-2.423, -8.469],
[5.721,	9.354],
[6.766,	-3.823],
[4.129,	6.744],
[5.371,	-5.404]]

# con entrada
#n = int(input("Cuantos puntos desea ingresar? "))
#coor = []
#for i in range(n):
#    x = float(input())
#    y = float(input())
#    coor.append([x, y])

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


minimo = float('inf')
for i in range(len(matriz)):
    for j in range(len(matriz)):
        if i != j and matriz[i][j] < minimo:
            punto1 = i
            punto2 = j
            minimo = matriz[i][j]

print("Puntos mas cercanos: ", punto1+1, "y", punto2+1, "con distancia de", minimo)


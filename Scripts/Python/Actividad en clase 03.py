def quicksort(arr) :

    # Caso base
    if len(arr) <= 1:
        return arr
    
    # Caso recursivo
    pivot = arr[len(arr) // 2]

    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]

    return quicksort(left) + middle + quicksort(right)

# Prueba

array = [3,6,8,10,1,2,1]   
sorted_array = quicksort(array)

print(sorted_array)

# Output: [1, 1, 2, 3, 6, 8, 10]

# la actividad de la clase 
# Utiliza la técnica de programación de divide y vencerás para resolver: El calculo de a^n

# Complejidad: O(log n)
def potencia(a, n):
    if n == 0:
        return 1
    elif n == 1:
        return a
    else:


        if n % 2 == 0:
            aux = potencia(a, n//2)
            return aux * aux
        else:
            aux = potencia(a, (n-1)/2)
            return a * aux * aux
    
# Prueba
# se pide al usuario una base y un exponente
# y se calcula la potencia

# a = int(input("Ingrese la base: "))
# n = int(input("Ingrese el exponente: "))

# print("El resultado de ", a, "^", n, " es: ", potencia(a, n))

print("El resultado de 2^3 es: ", potencia(2, 3))

# Output: 8
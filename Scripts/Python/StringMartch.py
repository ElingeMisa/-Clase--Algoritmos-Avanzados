# 1. Determina cuales son los indices donde aparece patron en cadena 
#    usando comparaciones entre caracteres unitarios. 
#    La salida correcta deberia ser 10 y 15. Tu codigo debe averiguarlo. 
# 2. Que complejidad tiene el algoritmo? 

cadena = "this is a small example"
patron = "small"

print("Buscando: ", patron)
print("Dentro de: ", cadena)

# 1. Determina cuales son los indices donde aparece patron en cadena

# recorremos la cadena buscando el indicie inicial del patron 
for i in range(len(cadena)):
    if cadena[i] == patron[0]:

        # si el primer caracter coincide, comparamos los siguientes caracteres
        for j in range(len(patron)):
            if cadena[i+j] != patron[j]:
                break
        else:
            # si todos los caracteres coinciden, imprimimos el indice de inicio y final del patron
            print("patron encontrado entre las posiciones", i+1, "y", i+j+1)

# complejidad O(n*m) donde n es la longitud de la cadena y m la longitud del patron
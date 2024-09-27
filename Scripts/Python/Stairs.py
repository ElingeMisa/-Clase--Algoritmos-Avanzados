def stairs_tab(n) :

    steps = [0 for i in range(n+1)]

    steps[1] = 1
    steps[2] = 2

    for i in range(3, n+1) :
        steps[i] = steps[i - 1] + steps[i - 2]
    
    return steps[n]

pasos = int(input("Ingrese el número de escalones: "))

print(stairs_tab(pasos))
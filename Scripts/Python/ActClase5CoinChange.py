#Algoritmo para coin-change
#Autor: Victor Misael Escalante


def coin_change_memo(coins, n, K, memo):

    # Casos base
    if K == 0:
        return 1
    if K < 0 or n <= 0:
        return 0
    if (n, K) in memo:
        return memo[(n, K)]
    
    if n <= 0 and K >= 1:
        return 0
    
    #Consultar en memoria
    if memo.get((n, K)) is not None:
        return memo[(n, K)]
    
    # Guardar en memoria
    memo[(n, K)] = coin_change_memo(coins, n - 1, K, memo) + coin_change_memo(coins, n, K - coins[n - 1], memo)

    return memo[(n, K)]

def count_ways_memo(coins, K):
    memo = {}
    return coin_change_memo(coins, len(coins), K, memo)

# Pruebas
coins = [1, 2, 5,10]

K = 10
print("Para llegar a " + str(K) + " pesos con monedas de " + str(coins) + " existen " + str(count_ways_memo(coins,K)) + " formas")  # Salida: 11
K = 5
print("Para llegar a " + str(K) + " pesos con monedas de " + str(coins) + " existen " + str(count_ways_memo(coins,K)) + " formas")  # Salida: 4

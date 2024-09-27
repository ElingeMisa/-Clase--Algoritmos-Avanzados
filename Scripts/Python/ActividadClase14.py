import networkx as nx

def my_djikstra(G, inicio, objetivo):
    visitados = set()
    por_visitar = set(G.nodes)
    distancias = {nodo: float('infinity') for nodo in G.nodes}
    previos = {nodo: None for nodo in G.nodes}
    distancias[inicio] = 0
    
    while por_visitar:
        nodo_actual = min(por_visitar, key=lambda nodo: distancias[nodo])
        visitados.add(nodo_actual)
        por_visitar.remove(nodo_actual)
        
        for vecino in G.neighbors(nodo_actual):
            if vecino not in visitados:
                nueva_distancia = distancias[nodo_actual] + G[nodo_actual][vecino]['weight']
                
                if nueva_distancia < distancias[vecino]:
                    distancias[vecino] = nueva_distancia
                    previos[vecino] = nodo_actual
    
    camino = []
    nodo_actual = objetivo
    while previos[nodo_actual]:
        camino.insert(0, nodo_actual)
        nodo_actual = previos[nodo_actual]
    camino.insert(0, inicio)
    
    distancia_total = distancias[objetivo]
    return camino, distancia_total

# Leer las aristas desde el archivo y construir el grafo
def leer_aristas_y_construir_grafo(archivo):
    G = nx.Graph()  

    with open(archivo, 'r') as f:
        for linea in f:
            # Imprimir la línea que se está leyendo
            #print("Leyendo línea:", linea.strip())  
            try:
                # Formato de la línea: (x1, y1) (x2, y2) distancia
                x1, y1, x2, y2, distancia = linea.replace('(', '').replace(')', '').replace(',', ' ').split()
                G.add_edge((int(x1), int(y1)), (int(x2), int(y2)), weight=int(distancia))
            except ValueError as e:
                print(f"Error al procesar la línea: {linea.strip()}. Error: {e}")

    #print("Nodos en el grafo:", G.nodes)  # Verifica los nodos en el grafo
    return G

grafo = leer_aristas_y_construir_grafo('/Users/misa_v/Library/CloudStorage/OneDrive-InstitutoTecnologicoydeEstudiosSuperioresdeMonterrey/Sem 5/Algoritmos_/Scripts/Python/txt/aristas.txt')

# amigos 
nombres_amigos = ['Carlos', 'Ana', 'Marcela', 'Katia', 'Marcos']
posiciones_amigos = [(7, 4), (0, 19), (8, 12), (5, 17), (17, 15)]
speeds_amigos = [30, 40, 25, 32, 20]
casa_de_luis = (2, 3)

# Funcion de Dijkstra para conocer el camino más corto
def camino(grafo, inicio,nombre, objetivo):
    try:
        #camino_corto = nx.shortest_path(grafo, source=inicio, target=objetivo, weight='weight')
        #distancia_corta = nx.shortest_path_length(grafo, source=inicio, target=objetivo, weight='weight')
        camino_corto,distancia_corta = my_djikstra(grafo, inicio, objetivo)
        return f"\nEl camino más corto desde {inicio} hasta {objetivo} (casa de {nombre}) es:\n\n\t{camino_corto} \n\tcon una distancia de [{distancia_corta}] tardando aproximadamente [{distancia_corta/speeds_amigos[nombres_amigos.index(nombre)]}] minutos"
    except nx.NetworkXNoPath:
        return f"No hay camino desde {inicio} hasta {objetivo}"
    except nx.NodeNotFound as e:
        return str(e)  # Para manejar el error de nodos no encontrados

# Calcular la ruta más corta desde la casa de cada amigo hasta la casa de Luis
for amigo in posiciones_amigos:
    nombre = nombres_amigos[posiciones_amigos.index(amigo)]
    print(camino(grafo, amigo,nombre, casa_de_luis))

# Clase Nodo que es común tanto para Trie como Suffix Trie
class Nodo:
    def __init__(self, caracter, final):
        self.caracter = caracter
        self.indices = []
        self.es_final = final
        self.hijos = []
        self.level = 0

# Clase Trie con funcionalidad de autocompletado
class Trie:
    def __init__(self):
        self.raiz = Nodo("#", False)

    def insertar_iter(self, nodo, cadena, og_i):
        i = 0
        matches = 1
        while matches != 0 and i < len(cadena):
            matches = 0
            for hijo in nodo.hijos:
                if hijo.caracter == cadena[i]:
                    hijo.indices.append(i+og_i)
                    matches = 1
                    i += 1
                    nodo = hijo
                    break

        while i < len(cadena) and matches == 0:
            nuevo_hijo = Nodo(cadena[i], i == len(cadena)-1)
            nuevo_hijo.indices.append(i+og_i)
            nuevo_hijo.level = nodo.level + 1
            nodo.hijos.append(nuevo_hijo)
            nodo = nuevo_hijo
            i += 1

    def show_inorder(self, nodo):
        if nodo.es_final:
            print("Palabra completa encontrada.")
        for hijo in nodo.hijos:
            self.show_inorder(hijo)

    # Función de autocompletado
    def autocompletar(self, nodo, prefijo):
        resultados = []
        self._buscar_prefijo(nodo, prefijo, "", resultados)
        return resultados

    def _buscar_prefijo(self, nodo, prefijo, acumulado, resultados):
        if not prefijo:
            if nodo.es_final:
                resultados.append(acumulado)
            for hijo in nodo.hijos:
                self._buscar_prefijo(hijo, "", acumulado + hijo.caracter, resultados)
        else:
            for hijo in nodo.hijos:
                if hijo.caracter == prefijo[0]:
                    self._buscar_prefijo(hijo, prefijo[1:], acumulado + hijo.caracter, resultados)

    def buscar(self, prefijo):
        nodo = self.raiz
        acumulado = ""
        for char in prefijo:
            encontrado = False
            for hijo in nodo.hijos:
                if hijo.caracter == char:
                    nodo = hijo
                    acumulado += char
                    encontrado = True
                    break
            if not encontrado:
                print(f"La cadena '{prefijo}' no existe en el Trie.")
                return
        # Si encontramos el prefijo
        if nodo.es_final and not nodo.hijos:
            print(f"La cadena '{prefijo}' existe completa.")
        else:
            opciones = self.autocompletar(nodo, "")
            print(f"Opciones para autocompletar '{prefijo}':", [prefijo + opcion for opcion in opciones])

# Clase Suffix Trie con funcionalidad de búsqueda de patrones
class SuffixTrie:
    def __init__(self):
        self.raiz = Nodo("#", False)

    def insertar(self, nodo, cadena, og_i):
        i = 0
        while i < len(cadena):
            encontrado = False
            for hijo in nodo.hijos:
                if hijo.caracter == cadena[i]:
                    hijo.indices.append(i+og_i)
                    nodo = hijo
                    i += 1
                    encontrado = True
                    break

            if not encontrado:
                while i < len(cadena):
                    nuevo_hijo = Nodo(cadena[i], i == len(cadena)-1)
                    nuevo_hijo.indices.append(i+og_i)
                    nodo.hijos.append(nuevo_hijo)
                    nodo = nuevo_hijo
                    i += 1

    def buscar_patron(self, patron):
        nodo = self.raiz
        for char in patron:
            encontrado = False
            for hijo in nodo.hijos:
                if hijo.caracter == char:
                    nodo = hijo
                    encontrado = True
                    break
            if not encontrado:
                print(f"Patron '{patron}' no encontrado.")
                return
        print(f"Patron '{patron}' encontrado en indices: {nodo.indices}")

# Ejemplo de uso del Trie para autocompletar
print("=== Trie con autocompletado ===")
trie = Trie()
palabras = ["casi", "casa", "cama", "camisa", "camara", "camion", "ave", "alce"]
for palabra in palabras:
    trie.insertar_iter(trie.raiz, palabra, 0)

# Buscar autocompletado para una cadena dada
cadena_buscar = "cam"
trie.buscar(cadena_buscar)

# Ejemplo de uso del Suffix Trie para buscar patrones
print("\n=== Suffix Trie con búsqueda de patrones ===")
palabra = "anabanana"
n = len(palabra)
suffix_trie = SuffixTrie()

# Insertar sufijos en el Suffix Trie
sufijos = [palabra[i:] for i in range(n)]
for i in range(n):
    suffix_trie.insertar(suffix_trie.raiz, sufijos[i], i)

# Buscar un patrón en el Suffix Trie
patron = "ana"
suffix_trie.buscar_patron(patron)

#! /usr/bin/python
# -*- coding: utf-8 -*-

# 3ra Practica Laboratorio
# Complementos Matematicos I
# Consigna: Implementar los siguientes metodos

'''
Recordatorio:
- Un camino/ciclo es Euleriano si contiene exactamente 1 vez
a cada arista del grafo
- Un camino/ciclo es Hamiltoniano si contiene exactamente 1 vez
a cada vértice del grafo
'''


def check_is_hamiltonian_trail(graph, path):
    """Comprueba si una lista de aristas constituye un camino hamiltoniano
    en un grafo.

    Args:
        graph (grafo): Grafo en formato de listas.
                       Ej: (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])

        path (lista de aristas): posible camino
                                 Ej: [('a', 'b), ('b', 'c')]

    Returns:
        boolean: path es camino hamiltoniano en graph

    Raises:
        TypeError: Cuando el tipo de un argumento es inválido
    """
    vertices,edges=graph#parseo
    lastVertix= None
    visitedVertices= set()
    visitedEdges= set()

    for edge in path:
        if edge not in edges or edge in visitedEdges:   return False
        if lastVertix!=None and lastVertix!=edge[0]: return False
        if lastVertix==None: visitedVertices.add(edge[0])
        if edge[1] in visitedVertices: return False
        lastVertix=edge[1]
        visitedVertices.add(edge[1])
        visitedEdges.add(edge)
    return visitedVertices==set(vertices)


def check_is_hamiltonian_circuit(graph, path):
    """Comprueba si una lista de aristas constituye un ciclo hamiltoniano
    en un grafo.

    Args:
        graph (grafo): Grafo en formato de listas.
                       Ej: (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])

        path (lista de aristas): posible ciclo
                                 Ej: [('a', 'b), ('b', 'c')]

    Returns:
        boolean: path es ciclo hamiltoniano en graph

    Raises:
        TypeError: Cuando el tipo de un argumento es inválido
    """
    vertices,edges=graph
    lastVertix= None
    visitedVertices= set()
    visitedEdges= set()

    if path==[]:
        if graph==([],[]):
            return True
        else: return False
    #no es necesario este else
    if(path[0][0]!=path[-1][1]): return False

    for edge in path:
        if edge not in edges or edge in visitedEdges:   return False
        if lastVertix!=None and lastVertix!=edge[0]: return False
        if lastVertix==None:  visitedVertices.add(edge[0])

        if path[-1]!=edge:
            if edge[1] in visitedVertices: return False
        lastVertix=edge[1]
        visitedVertices.add(edge[1])
        visitedEdges.add(edge)

    return visitedVertices==set(vertices)


def check_is_eulerian_trail(graph, path):
    """Comprueba si una lista de aristas constituye un camino euleriano
    en un grafo.

    Args:
        graph (grafo): Grafo en formato de listas.
                       Ej: (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])

        path (lista de aristas): posible camino
                                 Ej: [('a', 'b), ('b', 'c')]

    Returns:
        boolean: path es camino euleriano en graph

    Raises:
        TypeError: Cuando el tipo de un argumento es inválido
    """
    vertices,edges=graph#parseo
    lastVertix= None
    visitedVertices= set()
    visitedEdges= set()

    for edge in path:
        if edge not in edges or edge in visitedEdges:   return False
        if lastVertix!=None and lastVertix!=edge[0]: return False
        if lastVertix==None: visitedVertices.add(edge[0])
        if edge[1] in visitedVertices: return False
        lastVertix=edge[1]
        visitedVertices.add(edge[1])
        visitedEdges.add(edge)
    return visitedVertices==set(vertices)


def check_is_eulerian_circuit(graph, path):
    """Comprueba si una lista de aristas constituye un ciclo euleriano
    en un grafo.

    Args:
        graph (grafo): Grafo en formato de listas.
                       Ej: (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])

        path (lista de aristas): posible ciclo
                                 Ej: [('a', 'b), ('b', 'c')]

    Returns:
        boolean: path es ciclo euleriano en graph

    Raises:
        TypeError: Cuando el tipo de un argumento es inválido
    """
    pass


def graph_has_eulerian_trail(graph):
    """Comprueba si un grafo no dirigido tiene un camino euleriano.

    Args:
        graph (grafo): Grafo en formato de listas.
                       Ej: (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])

    Returns:
        boolean: graph tiene un camino euleriano

    Raises:
        TypeError: Cuando el tipo del argumento es inválido
    """
    pass


def find_eulerian_circuit(graph):
    """Obtiene un ciclo euleriano en un grafo no dirigido, si es posible

    Args:
        graph (grafo): Grafo en formato de listas.
                       Ej: (['a', 'b', 'c'], [('a', 'b'), ('b', 'c')])

    Returns:
        path (lista de aristas): ciclo euleriano, si existe
        None: si no existe un camino euleriano

    Raises:
        TypeError: Cuando el tipo del argumento es inválido
    """

    # Sugerencia: Usar el Algoritmo de Fleury
    # Recursos:
    # http://caminoseuler.blogspot.com.ar/p/algoritmo-leury.html
    # http://www.geeksforgeeks.org/fleurys-algorithm-for-printing-eulerian-path/
    pass


def main():
    pass

if __name__ == '__main__':
    main()

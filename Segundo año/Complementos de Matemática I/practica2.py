#! /usr/bin/python

# 2da Practica Laboratorio
# Complementos Matematicos I
# Consigna: Implementar los siguientes metodos

# Un disjointSet lo representaremos como un diccionario.
# Ejemplo: {'A':1, 'B':2, 'C':1} (Nodos A y C pertenecen al conjunto
# identificado con 1, B al identificado on 2)

def make_set(lista):
    '''
    Inicializa un conjunto (Lista) de modo de que todos sus elementos pasen
    a ser conjuntos unitarios.
    Retorna un disjointSet
    '''
    d={}
    for i in enumerate(lista):#paso la lista de los nodos
        #print i
        d[i[1]]=i[0]
    return d


def find(elem, disjoint_set):
    '''
    Obtiene el identificador correspondiente al conjunto al que pertenece
    el elemento 'elem'
    '''
    return disjoint_set[elem]


def union(id_1, id_2, disjoint_set):
    '''
    Une los conjuntos con identificadores id_1, id_2.
    Retorna la estructura actualizada
    '''
    for i in disjoint_set.iteritems():
        if i[1]==id_2: disjoint_set[i[0]]=id_1
    return disjoint_set


def componentes_conexas(grafo_lista):
    '''
    Dado un grafo en representacion de lista, obtiene sus componentes conexas.
    Ejemplo formato salida:
        [['a, 'b'], ['c'], ['d']]
    '''
    l=make_set(grafo_lista[0])
    for i in l.iteritems():
        i[1]
        for j in grafo_lista[1]:
            if j[0]==i[0]:
                d[j[0]]=i[1]
            else if j[1]==i[0]:
                d[j[0]]=i[1]
    pass



def main():
    temp=(['A','B','C'],[('A','B'),('B','C'),('C','B')])
    d=make_set(temp[0])
    print d
    print find('B',d)
    print union(0,1,d)

if __name__ == '__main__':
    main()

#! /usr/bin/python

# 4ta Practica Laboratorio
# Complementos Matematicos I
# Consigna: Implementar los siguientes metodos


def dijkstra(grafo, vertice):
    '''
    Dado un grafo (en formato de listas con pesos), aplica el algoritmo de
    Dijkstra para hallar el COSTO del camino mas corto desde el vertice de origen
    al resto de los vertices.
    Formato resultado: {'a': 10, 'b': 5, 'c': 0}
    (Nodos que no son claves significa que no hay camino a ellos)
    '''
    #Inicializar vertice en 0 y el resto en "infinito"
    #Actualizar los valores de los vecinos de vertice
    #Pasar el de menor peso como "procesado" y hacer el algoritmo a partir de este

    vertices,edges=grafo#parseo
    res={}#el resultado
    vNoProcesados=[]#vertices que me faltan procesar
    for i in vertices:
        res[i]=float('inf')#Decimal('Infinity')
        vNoProcesados.append(i)
    res[vertice]=0
    while vNoProcesados!=[]:
        temp=''
        for i in vNoProcesados:
            if temp=='' or res[i]<res[temp]:
                temp=i
        for arista in edges:
            if temp in arista:#si la arista incluye al vertice que estoy iterando
                if arista[0]!=temp:#que arista[0] sea el otro vertice de la arista
                    if arista[2]+res[temp]<res[arista[0]]:
                        res[arista[0]]=arista[2]+res[temp]#guardo el valor de la arista
                else:
                    if arista[2]+res[temp]<res[arista[1]]:
                        res[arista[1]]=arista[2]+res[temp]#guardo el valor de la arista

        vNoProcesados.remove(temp)
    for v in vertices:
        if res[v]==float('inf'):
            del res[v]
    return res


def dijkstra_2(grafo, vertice):
    '''
    Dado un grafo (en formato de listas con pesos), aplica el algoritmo de
    Dijkstra para hallar el CAMINO mas corto desde el vertice de origen
    a cada uno del resto de los vertices.
    Formato resultado: {'a': ['a'], 'b': ['a', 'b'], 'c': ['a', 'c']}
    (Nodos que no son claves significa que no hay camino a ellos)
    '''
    vertices,edges=grafo#parseo
    res={}#el resultado
    vNoProcesados=[]#vertices que me faltan procesar
    for i in vertices:
        res[i]=float('inf')#Decimal('Infinity')
        vNoProcesados.append(i)
    res[vertice]=[[vertice],0]
    while vNoProcesados!=[]:
        temp=''
        for i in vNoProcesados:
            if temp=='' or res[i][1]<res[temp][1]:
                temp=i
        for arista in edges:
            if temp in arista:#si la arista incluye al vertice que estoy iterando
                if arista[0]!=temp:#que arista[0] sea el otro vertice de la arista
                    if arista[2]+res[temp][1]<res[arista[0]][1]:
                        res[arista[0]][1]=arista[2]+res[temp][1]#guardo el valor de la arista
                        res[arista[0]][0]
                else:
                    if arista[2]+res[temp][1]<res[arista[1]][1]:
                        res[arista[1]][1]=arista[2]+res[temp][1]#guardo el valor de la arista

        vNoProcesados.remove(temp)
    for v in vertices:
        if res[v]==float('inf'):
            del res[v]
    return res


def main():
    pass

if __name__ == "__main__":
    main()

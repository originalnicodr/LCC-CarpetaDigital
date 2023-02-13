#! /usr/bin/python

# 1ra Practica Laboratorio
# Complementos Matematicos I
# Consigna: Implementar los siguientes metodos

import sys

def lee_grafo_stdin():
    '''
    Lee un grafo desde entrada estandar y devuelve su representacion como lista.
    Ejemplo Entrada:
        3
        A
        B
        C
        A B
        B C
        C B
    Ejemplo retorno:
        (['A','B','C'],[('A','B'),('B','C'),('C','B')])
    '''
    temp=lee_entrada_3()
    #print temp
    nodos=[]
    aristas=[]
    for i in range(1,int(temp[0])+1):#copia nodos
        nodos.append(temp[i])
    for j in temp[int(temp[0])+1:]:#formatea las ariastas
        a1=''
        a2=''
        k=0
        print j
        while(j[k]!=' '):#copia en el primer elemento de la arista el nombre del nodo
            a1=a1+j[k]
            k=k+1
        for i in j[k+1:]:#copia el segundo nodo de la arista
            a2=a2+i
        aristas.append((a1,a2))#lista de aristas
    print (nodos,aristas)
    return (nodos,aristas)


def lee_grafo_archivo(file_path):
    '''
    Lee un grafo desde un archivo y devuelve su representacion como lista.
    Ejemplo Entrada:
        3
        A
        B
        C
        A B
        B C
        C B
    Ejemplo retorno:
        (['A','B','C'],[('A','B'),('B','C'),('C','B')])
    '''
    temp=lee_archivo2(file_path)
    #print temp
    nodos=[]
    aristas=[]
    for i in range(1,int(temp[0])+1):#copia nodos
        nodos.append(temp[i])
    for j in temp[int(temp[0])+1:]:#formatea las ariastas
        a1=''
        a2=''
        k=0
        print j
        while(j[k]!=' '):#copia en el primer elemento de la arista el nombre del nodo
            a1=a1+j[k]
            k=k+1
        for i in j[k+1:]:#copia el segundo nodo de la arista
            a2=a2+i
        aristas.append((a1,a2))#lista de aristas
    print (nodos,aristas)
    return (nodos,aristas)


def imprime_grafo_lista(grafo):
    '''
    Muestra por pantalla un grafo. El argumento esta en formato de lista.
    '''
    pass


def lista_a_incidencia(grafo_lista):
    '''
    Transforma un grafo representado por listas a su representacion
    en matriz de incidencia.
    '''
    aristas=[]
    for a in grafo_lista[1]:#itero en las aristas
        atemp=[]
        for n in grafo_lista[0]:#itero en los nodos para ver si encuentra un 1
            if n==a[0] or n==a[1]:#el nodo forma parte de la arista?
                if a[0]==a[1]:#por si es un lazo
                    atemp.append(2)
                else:
                    atemp.append(1)
            else:
                atemp.append(0)
        aristas.append(tuple(atemp))
    return (grafo_lista[0],aristas)


def incidencia_a_lista(grafo_incidencia):
    '''
    Transforma un grafo representado una matriz de incidencia a su
    representacion por listas.
    '''
    temp=0 #variable auxiliar que me dice si ya encontro la primer arista
    aristas=[]
    for a in grafo_incidencia[1]:#itero en las ariastas
        arista=[]
        #print len(grafo_incidencia[0])
        #print a
        for i in range(0,len(grafo_incidencia[0])):#itero en los nodos
            if a[i]==2:
                arista=(grafo_incidencia[0][i],grafo_incidencia[0][i])
                break#sale del for
            if a[i]==1:
                arista.append(grafo_incidencia[0][i])
                if temp:#si fue el primero que guardo
                    break
                else:
                    temp=1
        aristas.append(tuple(arista))
        temp=0 #reseteo
    return (grafo_incidencia[0],aristas)



def imprime_grafo_incidencia(grafo_incidencia):
    '''
    Muestra por pantalla un grafo.
    El argumento esta en formato de matriz de incidencia.
    '''
    pass


def lista_a_adyacencia(grafo_lista):#muchas iteraciones, probablemente se pueda optimizar
    '''
    Transforma un grafo representado por listas a su representacion
    en matriz de adyacencia.
    '''
    aristas=[]
    for n1 in grafo_lista[0]:#iteracion de nodos
        arista=[]
        for n2 in grafo_lista[0]:#iteracion de nodos
            temp=0#si encontro la arista buscada
            for a in grafo_lista[1]:#iteracion de aristas
                if (a[0]==n1 and a[1]==n2) or (a[0]==n2 and a[1]==n1):
                    temp=1
                #print n1 + n2 + ' == ' + a[0] + a[1]#+ ' == ' + arista(len(arista))#imprimo cada arista
            if temp:
                arista.append(1)
            else:
                arista.append(0)
        aristas.append(tuple(arista))
    return (grafo_lista[0],aristas)






def adyacencia_a_lista(grafo_adyacencia):
    '''
    Transforma un grafo representado una matriz de adyacencia a su
    representacion por listas.
    '''
    aristas=[]
    for n1 in range(0,len(grafo_adyacencia[0])):#iteracion de nodos
        arista=[]
        for n2 in range(n1,len(grafo_adyacencia[0])):#iteracion de nodos (arranco de n1 por que al ser simetrico ya tengo la informacion guardada debajo de la diagonal, ademas no copio dos veces la misma arista)
            if grafo_adyacencia[1][n1][n2]:
                arista=(grafo_adyacencia[0][n1],grafo_adyacencia[0][n2])
        if arista!= []:#no se guardo nada
            aristas.append(arista)
    return (grafo_adyacencia[0],aristas)


def imprime_grafo_adyacencia(grafo_adyacencia):
    '''
    Muestra por pantalla un grafo.
    El argumento esta en formato de matriz de adyacencia.
    '''
    pass


#################### FIN EJERCICIO PRACTICA ####################
grafo_adyacencia1 = (
    [[0, 1, 0, 0], [0, 0, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0],],
    ['A', 'B', 'C', 'D']
)

grafo_adyacencia2 = (
    [[0, 2, 0, 0], [0, 0, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0],],
    ['A', 'B', 'C', 'D']
)

def lee_entrada_1():
    count = 0
    for line in sys.stdin:
        count = count + 1
        print 'Linea: [{0}]'.format(line)
    print 'leidas {0} lineas'.format(count)


def lee_entrada_2():
    count = 0
    try:
        while True:
            line = raw_input()
            count = count + 1
            print 'Linea: [{0}]'.format(line)
    except EOFError:
        pass

    print 'leidas {0} lineas'.format(count)

def lee_entrada_3():
    lista=[]
    try:
        while True:
            line = raw_input()
            lista.append(line)
    except EOFError:
        pass
    return lista


def lee_archivo(file_path):
    print 'leyendo archivo: {0}'.format(file_path)
    count = 0

    with open(file_path, 'r') as f:
        first_line = f.readline()
        print 'primer linea: [{}]'.format(first_line)
        for line in f:
            count = count + 1
            #print 'Linea: [{0}]'.format(line)
    print 'leidas {0} lineas'.format(count)

def lee_archivo2(file_path):
    print 'leyendo archivo: {0}'.format(file_path)
    lista=[]
    with open(file_path, 'r') as f:
        for line in f:
            if line[-1]=='\n':
                lista.append(line[:-1])
            else:
                lista.append(line)
    return lista


def main():
    #lee_entrada_2()
        temp=(['A','B','C'],[('A','B'),('B','C')])
        print "Matriz: ", temp
        temp1=lista_a_incidencia(temp)
        temp2=lista_a_adyacencia(temp)
        print "Incidencia: ",temp1
        print "Adyacencia: ",temp2
        print "Vuelta de incidencia: ",incidencia_a_lista(temp1)
        print "Vuelta de adyacencia: ",adyacencia_a_lista(temp2)
        #print adyacencia_a_lista(grafo_adyacencia1)
        #print adyacencia_a_lista(grafo_adyacencia2)
        #print lista_a_adyacencia((['A','B','C'],[('A','B'),('B','C')]))
     #Para leer desde un archivo
        '''if (len(sys.argv) < 2):
            print 'ERROR. Argumento (file) faltante'
            return
        lee_grafo_archivo(sys.argv[1])'''
    #test=(['A','B','C'],[('A','B'),('B','C')])

        print lista_a_incidencia((['A','B','C'],[('A','B'),('B','C'),('A','B')]))



if __name__ == '__main__':
    main()

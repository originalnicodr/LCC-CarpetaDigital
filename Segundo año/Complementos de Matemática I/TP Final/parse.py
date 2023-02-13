#-*- coding: utf-8 -*-
import argparse
import sys

'''
argparse: none -> {}
Devuelve un diccionario con los argumentos pasados por consola
'''
def parser():
    parser=argparse.ArgumentParser() #Analizador de argumentos

    #Argumento para modo verbose
    parser.add_argument( '-v','-verbose', action='store_true', help='Activa el modo verbose')

    #Argumento de archivo
    parser.add_argument('file',type=argparse.FileType('r'),help='Archivo de donde se lee el grafo')

    #Argumento para iteraciones
    parser.add_argument('-it',nargs='?',type=int,
    help='Permina asignar la cantidad de iteraciones para el algoritmo, ejemplo -it 100, en caso de no declarar un valor iterara de acuerdo a la temperatura')

    #Argumento para temperatura
    parser.add_argument('-T',nargs='?',type=int,default=100,help='Permite al usuario dar una temperatura inicial, ejemplo -T 150 en caso de no dar asigna una por defecto')

    #Argumento para el modo fullscreen
    parser.add_argument('-fs','-fullscreen', action='store_true',help='Activa el modo FullScreen')

    #Argumento para constante C
    parser.add_argument('-C',nargs='?',type=float,default=0.5,help='Permite al usuario dar la constante C que varia la distancia optima entre vértices')

    #Argumento para modo optimizado (utilizado para grafos grandes)
    parser.add_argument('-op',action='store_true',help='Activa el modo optimizado')

    #Argumento para agregar cuadricula
    parser.add_argument('-grid',action='store_true',help='Dibuja la cuadricula')

    #Argumento para graficar los pasos
    parser.add_argument('-ds',action='store_false',help='Evita que se dibuja cada paso')

    #Argumento para tiempo
    parser.add_argument('-time',action='store_true',help='Muestra el tiempo de ejecucion')

    args = parser.parse_args()
    args=vars(args)
    assert(args['it']==None or args['it']>=0)
    assert(args['C']==None or args['C']>=0)
    return args

'''
lee_grafo_archivo: file -> tupla
Dado un archivo, que contenga un grafo, abierto en modo lectura,
interpreta el texto y guarda los vertices y las aristas formando un grafo
'''
def lee_grafo_archivo(file_path):
    with file_path as f:
        a=0
        E=[]
        V=[]
        for i,line in enumerate(f):
            if i==0:
                a=line
            else:
                if i<=int(a):
                    if line[-2]=='\r':
                        V.append(line[:-2])
                    else:
                        V.append(line[:-1])
                else:
                    b=''
                    j=0
                    while line[j]!=' ':
                        b=b+line[j]
                        j+=1
                    if line[-1]=='\n':
                        if line[-2]=='\r':
                            e=(b,line[j+1:-2])
                        else:
                            e=(b,line[j+1:-1])
                    else:
                        if line[-1]=='\r':
                            e=(b,line[j+1:-1])
                        else:
                            e=(b,line[j+1:])
                    E.append(e)

    return (V,E)

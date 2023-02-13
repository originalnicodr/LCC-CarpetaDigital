#-*- coding: utf-8 -*-

import pygame
from random import randint
import parse
args=parse.parser()

'''
Macros de dibujo
'''
radion=5#radio del nodo
margen=10#offset
if(args['fs']):
	screen = pygame.display.set_mode((0,0))
	plantillaX=pygame.Surface.get_width(screen)-40 #width's surface
	plantillaY=pygame.Surface.get_height(screen)-50 #height's surface
else:
    plantillaX=500 #width's surface
    plantillaY=500 #height's surface
    screen = pygame.display.set_mode((plantillaX,plantillaY))

'''
inicializar_casillas: int int int -> dicc
Devuelve un diccionario de casillas
'''
def inicializar_casillas(k,X,Y):
    casillas={}
    for i in range(X+1):
        for j in range(Y+1):
            casillas[(i,j)]=[]
    return casillas

'''
randomize_positions:list list int int int -> dicc
Inicializa los vértices en posiciones pseudoaleatoreas de forma 
tal que las casillas tengan una diferencia de nodos <=1
actualizando los componentes de la casillas de forma acorde
'''

def randomize_positions_op(N,C,k,X,Y):
    n=int(len(N)/len(C))
    V={}
    for i,v in enumerate(N):
        V[v]=[randint(0, plantillaX),randint(0, plantillaY),(0,0)]
        c=calcular_casilla(V,v,k)
        if i<=(n*len(c)):
            while len(C[c])>n:
                V[v]=[randint(0, plantillaX),randint(0, plantillaY),(0,0)]
                c=calcular_casilla(V,v,k)
        V[v][2]=c
        C[c].append(v)
    return V


'''
Cuadr: int -> void
Dibuja la cuadrilla en pantalla
'''
def cuadr(step):
    for i in range(0,plantillaY,step):
        pygame.draw.line(screen,(255,255,255),(0,i),(plantillaX,i),1)
    for i in range(0,plantillaX,step):
        pygame.draw.line(screen,(255,255,255),(i,0),(i,plantillaY),1)


'''
calcular_casilla: dicc, str, int -> tupla
Calcula la casilla donde esta ubicado el vértice
'''
def calcular_casilla(V,v,k):
    posx=V[v][0]
    posy=V[v][1]
    x=int(posx/(2*k))
    y=int(posy/(2*k))
    return (x,y)


'''
randomize_positions:list -> dicc
Inicializa los vértices en posiciones aleatoreas
'''
def randomize_positions(N):
	V={}
	for v in N:
		V[v]=[randint(0, plantillaX),randint(0, plantillaY)]
	return V

'''
redibujar: dic list -> void
Dibuja los vertices en su posición
'''
def dibujar(N,E):
	screen.fill((0,0,0))
	for n in N:
		pygame.draw.circle(screen, (255,0,0), (int(N[n][0]),int(N[n][1])), radion, 0)
	for e in E:
		pygame.draw.line(screen, (0,0,255), (int(N[e[0]][0]),int(N[e[0]][1])) , (int(N[e[1]][0]),int(N[e[1]][1])), 1)
	return

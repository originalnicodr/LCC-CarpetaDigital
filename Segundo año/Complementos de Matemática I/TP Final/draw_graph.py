#-*- coding: utf-8 -*-
'''
Dibujador de grafo
Versión 1.2
Blanco Fernando, Navall Nicolas
'''
import fruchterman
import time

def main():
	# Inicializaciones

	fruchterman.draw.pygame.init()
	grafo1=fruchterman.draw.parse.lee_grafo_archivo(fruchterman.draw.args['file']) # Lectura del grafo desde archivo
	N, E= grafo1
	k=fruchterman.C*fruchterman.math.sqrt(fruchterman.draw.plantillaX*fruchterman.draw.plantillaY/len(N)) # Distancia optima k

	if fruchterman.draw.args['op']:
		X=int(fruchterman.draw.plantillaX/(2*k))# Cantidad de casillas por fila
		Y=int(fruchterman.draw.plantillaY/(2*k))# Cantidad de casillas por columna
		casillas=fruchterman.draw.inicializar_casillas(k,X,Y)
		N=fruchterman.draw.randomize_positions_op(N,casillas,k,X,Y)
		if fruchterman.draw.args['grid']:
			ko=k
		k=k*4 # La forma optimizada queda más chico el dibujo con el mismo k

	else:
		if fruchterman.draw.args['grid']:
			ko=k
		X=0
		Y=0
		casillas={}
		N= fruchterman.draw.randomize_positions(N)

	T=fruchterman.draw.args['T']
	fruchterman.draw.dibujar(N,E)
	if fruchterman.draw.args['grid']:
		fruchterman.draw.cuadr(int(2*ko))
	fruchterman.draw.pygame.display.update()

	# Algoritmo
	if fruchterman.draw.args['time']:
		ti=time.time() # Tiempo inicial
	if fruchterman.draw.args['it']==None: # No le pasamos argumento de iteraciones
		i=0
		while T>0.1:
			if fruchterman.draw.args['v']:
				print ('Paso ', i)
			T=fruchterman.step(N,E,k,T,casillas,X,Y)

			if fruchterman.draw.args['time']:
				if(i==0):
					tf=time.time() # Tiempo de un paso
					print ('TIEMPO Step:', tf-ti)
			i+=1
	else:
		for i in range(fruchterman.draw.args['it']):
			if fruchterman.draw.args['v']:
				print('Paso ', i)
			T=fruchterman.step(N,E,k,T,casillas,X,Y)

	if fruchterman.draw.args['time']:
		tf=time.time() # Tiempo final
		print ('TIEMPO:', tf-ti)

	# Actualización de imagén
	fruchterman.draw.dibujar(N,E)
	if fruchterman.draw.args['grid']:
		fruchterman.draw.cuadr(int(2*ko))
	fruchterman.draw.pygame.display.update()

	if fruchterman.draw.args['v']:
		print(grafo1)


	run = True
	while run:
		for event in fruchterman.draw.pygame.event.get():
			if event.type == fruchterman.draw.pygame.QUIT:
				run = False


if __name__ == "__main__":
	main()

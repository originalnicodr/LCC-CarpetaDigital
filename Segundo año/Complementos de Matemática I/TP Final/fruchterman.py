#-*- coding: utf-8 -*-
import math
import draw

'''
Macros del algoritmo
'''
Ce=0.95 # CD
C=draw.args['C'] # Constante C para el calculo de k
gravity_center=(draw.plantillaX/2,draw.plantillaY/2) # Centro de gravedad
mod_g=(draw.plantillaX+draw.plantillaY)/4 # Modulo de la fuerza de gravedad


'''
inicialize_acummulators: list -> tupla
Crea diccionarios con todos sus elementocon valor 0
'''
def inicialize_acummulators(N):
	acumm_x={node: 0 for node in N} 
	acumm_y={node: 0 for node in N}
	return (acumm_x,acumm_y)

'''
fa: int int -> int
Calcula del modulo de la fuerza de atraccion
'''
def fa(d,k):
	r=(math.pow(d,2))/k 
	return r

'''
fr: int int -> int
Calcula el modulo de la fuerza de repulsion
'''
def fr(d,k):
	r=(k**2)/d 
	return r

'''
compute_attraction_force: list, list, dic, int -> tupla
Calcula la fuerza de atraccion que aplican las aristas sobre los vertices
'''
def compute_attraction_force(E,V,k):
	acumm_xtemp,acumm_ytemp=inicialize_acummulators(V)
	for n1,n2 in E: 
		dist=math.sqrt((V[n1][0]-V[n2][0])**2+(V[n1][1]-V[n2][1])**2) # Distancia entre 2 puntos (modulo)
		if dist!=0:
			mod_fa=fa(dist,k) # Modulo de la fuerza
			fx=mod_fa*(V[n2][0]-V[n1][0])/dist # Componente x de la fuerza
			fy=mod_fa*(V[n2][1]-V[n1][1])/dist # Componente y de la fuerza

			# Actualizar acumuladores
			acumm_xtemp[n1]=acumm_xtemp[n1]+fx
			acumm_ytemp[n1]=acumm_ytemp[n1]+fy
			acumm_xtemp[n2]=acumm_xtemp[n2]-fx
			acumm_ytemp[n2]=acumm_ytemp[n2]-fy
	
	if draw.args['v']:
		print("Atraction force")
		print (acumm_xtemp,acumm_ytemp)
	return (acumm_xtemp,acumm_ytemp)


'''
compute_repulsion_force: list, dic, int -> tupla
Calcula la fuerza de repulsion que aplican los vertices entre si
'''
def compute_repulsion_force(V,k):
	acumm_xtemp,acumm_ytemp=inicialize_acummulators(V)
	for v in V:
		for u in V:
			if (u!=v):
				dist=math.sqrt((V[v][0]-V[u][0])**2+(V[v][1]-V[u][1])**2) # Distancia entre 2 puntos (modulo)
				if dist!=0:
					mod_fr=fr(dist,k) # Modulo de la fuerza
					fx=mod_fr*(V[v][0]-V[u][0])/dist # Componente x de la fuerza
					fy=mod_fr*(V[v][1]-V[u][1])/dist # Componente y de la fuerza

					# Actualizar acumuladores
					acumm_xtemp[v]=acumm_xtemp[v]+fx
					acumm_ytemp[v]=acumm_ytemp[v]+fy
	
	if draw.args['v']:
	   print("Repulsion force")
	   print(acumm_xtemp, acumm_ytemp)

	
	return (acumm_xtemp,acumm_ytemp)

'''
compute_repulsion_op: list list -> tupla
Calcula la fuerza de repulsion que aplican los vertices entre si
Algoritmo optimizado
'''

def compute_repulsion_op(V,casillas,k,X,Y):
	acumm_xtemp,acumm_ytemp=inicialize_acummulators(V)
	for v in V:
		p=V[v][2]
		if v in casillas[p]:
			casillas[p].remove(v) 
		for i in range(max(p[0]-1,0),min(p[0]+2,X)):
			for j in range(max(p[1]-1,0),min(p[1]+2,Y)):
				for u in casillas[(i,j)]:
					if (u!=v):
						dist=math.sqrt((V[v][0]-V[u][0])**2+(V[v][1]-V[u][1])**2) # Distancia entre 2 puntos (modulo)
						if  dist<(2*k) and dist!=0:
							mod_fr=fr(dist,k) # Modulo de la fuerza
							fx=mod_fr*(V[v][0]-V[u][0])/dist # Componente x de la fuerza
							fy=mod_fr*(V[v][1]-V[u][1])/dist # Componente y de la fuerza

							# Actualizar acumuladores
							acumm_xtemp[v]=acumm_xtemp[v]+fx
							acumm_ytemp[v]=acumm_ytemp[v]+fy
							acumm_xtemp[u]=acumm_xtemp[u]-fx
							acumm_ytemp[u]=acumm_ytemp[u]-fy
					
	if draw.args['v']:
	   print("Repulsion force")
	   print(acumm_xtemp, acumm_ytemp)
	return (acumm_xtemp,acumm_ytemp)


'''
compute_gravity_force: list, dic -> tupla
Calcula la fuerza de atraccion que aplican la gravedad sobre los vertices y la suma
'''
def compute_gravity_force(V):
	acumm_xtemp,acumm_ytemp=inicialize_acummulators(V,)
	for v in V:
		dist=math.sqrt((gravity_center[0]-V[v][0])**2+(gravity_center[1]-V[v][1])**2) # Distancia de un nodo al centro de gravedad (modulo)
		
		if dist!=0:
			fx=mod_g*(gravity_center[0]-V[v][0])/dist #Componente x de la fuerza
			fy=mod_g*(gravity_center[1]-V[v][1])/dist #Componente y de la fuerza

			# Actualizar acumuladores
			acumm_xtemp[v]=acumm_xtemp[v]+fx
			acumm_ytemp[v]=acumm_ytemp[v]+fy
	
	if draw.args['v']:
	   print("Gravity force")
	   print(acumm_xtemp, acumm_ytemp)

	return (acumm_xtemp,acumm_ytemp)

'''
update_position: list, dic, dic, dic, int -> dic
Actualiza las posiciones de acuerdo a la fuerza aplicada considerand temperatura y bordes
'''
def update_position(V,acumm_x,acumm_y,T):
	for v in V:
		# Modulo de la fuerza total
		mod_f=math.sqrt(acumm_x[v]**2+acumm_y[v]**2)

		# Ajuste de temperatura
		d=min(mod_f,T)
		acumm_x[v]=acumm_x[v]/mod_f*d
		acumm_y[v]=acumm_y[v]/mod_f*d

		# Actualizar posición
		V[v][0]=V[v][0]+acumm_x[v] 
		V[v][1]=V[v][1]+acumm_y[v] 

		# Mantenemos el grafo en la pantalla
		V[v][0]=min(draw.plantillaX-draw.margen,max(draw.margen,V[v][0]))
		V[v][1]=min(draw.plantillaY-draw.margen,max(draw.margen,V[v][1]))

	if draw.args['v']:
		print('Fuerza total')
		print (acumm_x,acumm_y)
	return V

'''
update_position_op: Dic, list, dic, dic, int -> dicc
Actualiza las posiciones de acuerdo a la fuerza aplicada considerand temperatura y bordes
Actualiza las casillas
'''
def update_position_op(V,casillas,acumm_x,acumm_y,T,k):
	for v in V:
		# Modulo de la fuerza total
		mod_f=math.sqrt(acumm_x[v]**2+acumm_y[v]**2)
		if mod_f!=0:
			# Ajuste de temperatura
			d=min(mod_f,T)
			acumm_x[v]=acumm_x[v]/mod_f*d
			acumm_y[v]=acumm_y[v]/mod_f*d

			# Actualizar posición
			V[v][0]=V[v][0]+acumm_x[v] 
			V[v][1]=V[v][1]+acumm_y[v] 

			# Mantenemos el grafo en la pantalla
			V[v][0]=min(draw.plantillaX-draw.margen,max(draw.margen,V[v][0]))
			V[v][1]=min(draw.plantillaY-draw.margen,max(draw.margen,V[v][1]))
			Co=V[v][2]
			Cn=draw.calcular_casilla(V,v,k)
			
			# Actualizar casillas
			if Co!=Cn:
				if v in casillas[Co]:
					 casillas[Co].remove(v)
				casillas[Cn].append(v)
				V[v][2]=Cn
			
	if draw.args['v']:
		print('Fuerza total')
		print (acumm_x,acumm_y)
	return V



'''
update_temperature: int -> int
Actualiza la temperatura
'''
def update_temperature(T):
	T=Ce*T
	return T

'''
step: list list dic int int -> int
Secuencia a seguir en cada paso del algoritmo
'''
def step(N,E,k,T,casillas,X,Y):
	# Inicializar acumuladores
	acumm_x, acumm_y=inicialize_acummulators(N)

	# Compute forces
	acumm_xa, acumm_ya=compute_attraction_force(E,N,k)
	if draw.args['op']:
		acumm_xr, acumm_yr=compute_repulsion_op(N,casillas,k,X,Y)
	else:
		acumm_xr, acumm_yr=compute_repulsion_force(N,k)
	acumm_xg, acumm_yg=compute_gravity_force(N)

	# Update
	for v in N:
		acumm_x[v]+=(acumm_xa[v]+acumm_xr[v]+acumm_xg[v])
		acumm_y[v]+=(acumm_ya[v]+acumm_yr[v]+acumm_yg[v])
	if draw.args['op']:
		update_position_op(N,casillas,acumm_x,acumm_y,T,k)
	else:
		update_position(N,acumm_x,acumm_y,T)
	T=update_temperature(T)

	xM=max(acumm_x)
	xm=min(acumm_x)
	yM=max(acumm_y)
	ym=min(acumm_y)

	# Equilibrado
	if math.sqrt(acumm_x[xM]**2+acumm_y[xM]**2)<1 and math.sqrt(acumm_x[yM]**2+acumm_y[yM]**2)<1 and math.sqrt(acumm_x[xm]**2+acumm_y[xm]**2)<1 and math.sqrt(acumm_x[ym]**2+acumm_y[ym]**2)<1:
		T=0

	# Update screen
	if draw.args['ds']:
		draw.dibujar(N,E)
		if draw.args['grid']:
			draw.cuadr(int(2*k))
		draw.pygame.display.update()
	
	
	if draw.args['v']:
		print('Temperatura:',T)
	return T

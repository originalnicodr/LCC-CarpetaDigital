from random import *
#tuttifrutti: Nan -> Nan
#La funcion pedira que se ingrese el numero de jugadores que van a participar, que sera entre 2 y 5. Luego, se generara una letra aleatoria la cual iniciara la ronda, una vez que los jugadores
#ingresen todos los datos luego que la ronda haya finalizado; se hara el recuento de puntos conforme la siguiente reglas establecidas por las hermanas Polgar:
#*Para las palabras válidas escritas en una categoría y escritas solamente por un jugador se asignarán 10 puntos.
#*Para las palabras repetidas se asignarán 5 puntos.
#*Para las palabras no válidas o categorías no completadas con una palabra, los participantes no obtendrán ninguna puntuación.
#*También, en caso de ser únicamente un jugador quien pudo encontrar una palabra con la letra de dicho turno, se le asignarán 20 puntos
#Cuando el limite de 200 puntos es alcanzado, el juego concluye y el jugador con mayor cantidad de puntos gana el juego.
def tuttifrutti():
    abecedario=['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    puntajes=[0, 0, 0, 0, 0]
    puntajeaux=[0, 0, 0, 0, 0]
    palabras=[(),(),(),(),()]
    letrap=0
    letra=''
    n=int(input("Ingrese la cantidada de jugadores (de 2 a 5 jugadores)\n"))
    while ((n>5)and(n<2)):
        n=int(input("Ingrese una cantidada de jugadores correcta\n"))
    while noes200(puntajes):
        letrap=randrange(len(abecedario))
        letra=abecedario[letrap]
        print("La letra escogida es ",letra,"\n")
        abecedario=abecedario[:letrap]+abecedario[letrap+1:]                                              #Se debe restartear la variable del abecedario cuando nos quedamos sin letras??
        for i in range (0,n):
            palabras[i]=ingresodedatos()
        puntajeaux=puntaje(palabras,letra,n)
        for indice in range (0, n):
            puntajes[indice]+=puntajeaux[indice]
            print("Jugador nº ", indice+1, ", puntaje de la ronda: ", puntajes[indice])                  #PUNTAJE DE LA RONDA O PUNTAJE ACUMULADO!? KESTION MARQ
    print("Ha ganado el jugador nº " , maximof(puntajes)+1)
    
            
        
        
#categorias(Personas, Colores, Animales, Comidas, Flores, Frutas, Paises)
#Se representan numeros por medio de numeros
#noes200: List -> Boolean
#Recibe una lista, si uno de los elementos de la lista es mayor igual a 200, retornara falso, caso contrario, retornara verdadero.

#cosas de pytest

def noes200(lista):
    for i in lista:
        if (i>=200):
            return False
    return True

#Se representan categorias del tuttifruti por medio de una Tupla
#ingresodedatos: Nan -> Tuple
#se le pedira al usuario que ingrese series de palabras que se correspondan con las categorias indicadas
#en caso de que no se haya ingresado palabra alguna, se considerara que se ingreso el caracter " " (espacio).

#cosas de pytest
def ingresodedatos():
    lista=()
    persona=(input("Ingrese el nombre de una persona\n"))
    color=(input("Ingrese el nombre de un color\n"))
    animal=(input("Ingrese el nombre de un animal\n"))
    comida=(input("Ingrese el nombre de una comida\n"))
    flores=(input("Ingrese el nombre de una flor\n"))
    fruta=(input("Ingrese el nombre de una fruta\n"))
    pais=(input("Ingrese el nombre de una país\n"))
    lista=[persona, color, animal, comida, flores, fruta, pais]
    for indice in range (0,7):
        if (lista[indice]==''):
            lista[indice]=' '
    return(lista[0],lista[1], lista[2],lista[3],lista[4],lista[5],lista[6])

# Se representan las palabras escritas por los jugadores por medio de tuplas de strings, cada jugador con sus respuestas se representa por una lista, la letra escogida para
# la ronda se representa por medio de character y la cantidad de jugadores por medio de un numero
#puntaje: List String Integer -> List
#Dada una lista con las respuestas de cada uno de los jugadores, la letra de inicio de ronda y la cantidad de jugadores, esta funcion calculara los puntajes individuales de cada uno
#de los jugadores con respecto a las leyes previamente explicadas en la funcion tuttifruti

#casos de pytest
def puntaje(lista, letra, n):
    puntaje=[0, 0, 0, 0, 0]
    for ct in range (0,7): #pasamos por categorias ct= contadortuplas cl= contadorlistas
        for cl in range (0, n): #pasamos por personas
            indice=0
            indice2=0
            if (lista[cl][ct][0]==letra):#el and puede estar de mas
                  while(indice<n):#pasa por las personas para comparar con las otras palabras
                   if((lista[cl][ct]==lista[indice][ct])and(cl!=indice)): #cl!=indice para que no analice con la misma palabra
                        indice=n
                        print("sumo 5")
                        puntaje[cl]+=5#Asigno 5 puntos al jugador CL y continuo con la prox categoria
                   indice+=1
                  if (indice==n): #si entra aca es porque no hubo palabras repetidas en la categoria
                      while (indice2<n):
                          if ((lista[indice2][ct][0]==letra)and(cl!=indice2)):
                              print("sumo 10")
                              puntaje[cl]+=10#Asigno 10 puntos al jugador CL y continuo con la prox categoria
                              indice2=n
                          indice2+=1
                      if(indice2==n):
                          print("sumo 20")
                          puntaje[cl]+=20#Asigno 20 puntos al jugador CL y continuo con la prox categoria
    return puntaje

# Se representan numeros por medio de una lista
#maximof: Lista -> Number
# Dada una lista de numeros, se determina cual de estos es el mayor de todos y retorna su posicion en la lista

#CASOS PYTEST
def maximof(lista):                       #que pasa si dos jugadores tienen el mismo puntaje?
    maximo=0
    for indice in range (0, len(lista)):
        if (lista[maximo]<=lista[indice]):
            maximo=indice
    return maximo
                    
tuttifrutti()

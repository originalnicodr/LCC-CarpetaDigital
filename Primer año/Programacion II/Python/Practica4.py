#Representamos posiciones mediante números
#posicionesMultiplo: List Int -> List
#El parámetro List representa una lista de números, el parametro es el numero
#a partir del cual filtra los elementos de las listas, y se retorna la lista, con los
#elementos cuya posición es multiplo de n
# entrada: ([1,2,3,4,5,6,7],2)  salida: [1, 3, 5, 7] 
# entrada: ([1,2,3,4,5,6,7],3), salida: [1, 4, 7]

def posicionesMultiplo(li,n):
    i=0
    n=0
    subli=[li[0]]
    for i in li:
        if(i%n==0):
            subli=subli+[li[n]]
        n+=1
    return subli
            
#Representamos numeros por medio de una lista de números
#sumcum: List -> List
#dada una lista de números, devuelva le suma acumulada.
#entrada: [1,2,3] salida: [1,3,6]

def sumcum(lis):
    sublis=[]
    n=0
    for i in lis:
        if(n==0):
            sublis+=[i]
        else:
            sublis=sublis+[i+sublis[n-1]]
        n+=1
    return sublis

#Representamos conjuntos de elementos por medio de listas
#elimina: Lista -> Lista
#dada una lista de elementos, se devuelve dicha lista, la cual no
#posee el primer y el último elemento
#entrada: [1,2,3] salida: [2]
#entrada: [999,99,1,99] salida: [99,1]

def elimina(lista):
    liste=lista[1:(len(lista)-1)]
    return liste

#ordenada: List -> Boolean
#dada una lista, verifico que todos sus elementos esten ordenados en orden
#ascendente, de serlo devuelvo true, de lo contrario False
#entrada: [1,2,3] salida: True
#entrada: ['b','a'] salida: False

def ordenada(lister):
    for i in range(0,len(lister)):
        if ((lister[i]<lister[i-1])and(i!=0)):
            return False
    return True

#duplicado: List -> Boolean
#dada una lista devuelvo False si no posee elementos duplicados
#,y devuelvo True en caso de tenerlos
#entrada: [1,2,2]  salida: True
#entrada: [1,3,2] salida: False

def duplicado (lis):
    n=0
    for i in lis:
        print (i)
        if (i in lis[n+1:]):
            return True
        n+=1
    return False

#autistlist: List -> List
#dada una lista retorno una nueva lista con los elementos únicos de la lista original
#entrada: ([1,1,111,1,3,3,4,5,6,2]) salida: [111, 1, 3, 4, 5, 6, 2]

def autistlist(lista):
    listaux=[]
    for i in range (0,len(lista)):
        if not((duplicado(listaux+[lista[i]]))):
            listaux+=[lista[i]]
    return listaux

#elementdif: List -> Int
#dada una lista, se retorna la cantidad de elementos distintos que esta lista posee
#entrada: ([1,1,111,1,3,3,4,5,6,2]) salida: 7
#entrada: ([111, 1, 3, 4, 5, 6, 2]) salida: 7

def elementdif(lista):
    return len(autistlist(lista))

#buscaDicotomica: List String-> Boolean
#dada una lista de palabras ordenadas alfabeticamente y una palabra a buscar, se retorna si
#la palabra esta en la lista o no

def buscaDicotomia(lista, p):
    n=int(len(lista)/2) #Trunca la divison
    if (len(lista)==1): #Significa que encontro la palabra
        print ("entro en len=1")
        if (p==lista[0]):
            print (True)
            return True
        else:
            print (False)
            return False
    if (p < lista[n]):
        buscaDicotomia(lista[:n],p)
    if (p > lista[n]): 
        buscaDicotomia(lista[n:],p)
    if (p==lista[n]):
        print (True)
        return True


#La cadena representa un texto y los caracteres representa las letras de esta
#cadena: String -> Nan                        imprime nomas, no devuelve nada
#Se ingresa una cadena y se devuelve cada caracter desde el ultimo hasta el primero
def cadena(c):
    n=len(c)-1
    while (n>=0):
        print (c[n])
        n-=1
#el caracter representa una letra y la lista un texto
#contar: Character String -> Number
#Cuenta cuántas veces aparece un carácter dado en una cadena.
def contar(l,lista):
    n=0
    for i in range (0,len(lista)):
        if (l==lista[i]):
            n+=1
    return n
#La cadena representa un texto
#vocales: String -> List
#Cuenta cuantas veces aparece cada vocal individualmente en el string
def vocales (lista): #no cuenta vocales con acentos
    vocales=[0, 0, 0, 0, 0]
    for i in lista:
        if ((i=='a')or(i=='A')):
            vocales[0]+=1
        if ((i=='e')or(i=='E')):
            vocales[1]+=1
        if ((i=='i')or(i=='I')):
            vocales[2]+=1
        if ((i=='o')or(i=='O')):
            vocales[3]+=1
        if ((i=='u')or(i=='U')):
            vocales[4]+=1
    return vocales
#La cadena representa un texto
#contarpalabras: String -> Number
#Cuenta la cantidad de palabras mayores a 5 caracteres que se encuentran en el string
def contarpalabras(lista):
    n=0
    p=0
    for i in range (0, len(lista)):
       if ((lista[i]==' ')or(i==(len(lista)-1))):
           if (n>5):
               p+=1
           n=-1 #por que le suma 1 inmediatamente despues
       n+=1
    return p

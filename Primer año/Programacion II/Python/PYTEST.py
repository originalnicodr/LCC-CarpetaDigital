from random import *
#El objetivo del programa es imprimir un string de numeros que va desde el numero dado hasta 20 incluyendolo, con saltos de 5 de mayor a menor.

def ejercicio1 (n = 100):
    h =''
    while n >= 20: #En cada ciclo se agrega un numero a la string de h
        h +=' '+ str(n)
        n -= 5
    return h

assert ejercicio1(5)==''
assert ejercicio1(100)== ' 100 95 90 85 80 75 70 65 60 55 50 45 40 35 30 25 20'

#Si la division a/b es menor igual a 30 devolvera 4960.
#EN caso de que el cociente de a/b > 30, se devuelve el a/c * (b*b*b)

def ejercicio2 (a, b, c):
    n = 2
    suma = 0
    sumas = 0
    if a/b > 30:        
        suma = a/c*b**3
        return suma
    if a/b <= 30:
        while n <= 30:
            sumas += n**2
            n += 2
        return sumas

assert ejercicio2(3,2,1)==4960
assert ejercicio2(30000000,40000000,1)==4960
assert ejercicio2(31,1,2)==15.5

#Si el n ingresado es mayor a 20 y resulta en un numero par, entonces se realizara la sumatoria de todos los numeros pares entre n y 20
#En caso de que el n sea impar, se hace el mismo proceso pero con los impares
def ejercicio3(n = 50):
    h = 0
    while n >= 20:
        h += n
        n -= 2
    return h

assert ejercicio3(50)== 560
assert ejercicio3(51)== 576
assert ejercicio3(10)== 0

#Mientras el numero ingresado sea inferior a 100, entonces se realizara la suma de todos los numeros pares e impares por separado
# de todos los numeros encontrados en el intervalo cerrado (n,100)
def ejercicio4(n = 1):
    p = 0
    i = 0
    while n <= 100:
        if n%2 == 0:
            p += n
        else:
            i += n
        n += 1
    return'Pares='+ str(p) +' e Impares:'+ str(i)

assert ejercicio4(1000)=='Pares=' + str(0) + ' e Impares:' + str(0)
assert ejercicio4()=='Pares=' + str(2550) + ' e Impares:' + str(2500)


def ejercicio5(s):
    for x in s:
        for z in x:
            print(z)
        print('***************')
#Como la funcion "ejercicio5" no retorna valor alguno, no se podria aplicar la funcion pytest"

#Random1
def random1():
    n=0
    s=0
    while (n!=7):
        n=randint(1,7)
        s+=1
        print (n)
        return s
def da2(n):
    i=0
    c=0
    while (i<=n):
        if (randint(1,6)==randint(1,6)):
            c+=1
        i+=1
    return c
def juego(n):
    i=0
    plata=0
    while (i<=n):
        a=randint(1,6)
        print(a)
        if (a==1):
            i-=1
        if (a==6):
           plata+=4
        if (a==3):
            plata+=1
        if((a==2)or(a==4)or(a==5)):
            plata-=2
        i+=1
    return "Ganaste/Debes "+str(plata)
            

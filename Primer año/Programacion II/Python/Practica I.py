##1) arrancamos de 0 por que si

def naturales(n):
    if (n<=50):
        print (n)
        m=n+2
        naturales(m)

def naturales1 ():
    naturales(0)


##for i in range(1,10,1):
##    print("xd")

##naturales1()

#--------------------------------------------------------------------------------------------------------------------

##2)

def naturales100(m):
    if (m<=200):
        print (m)
        y=m+2
        naturales100(y)

def naturales101 ():
    naturales100(0)

##naturales101()

##Forma general

def naturalesg(n,m):
    if (n<=m*2):
        print (n)
        n=n+2
        naturalesg(n,m)

def naturalesgg(m):
    naturalesg(0,m)
#--------------------------------------------------------------------------------------------------------------------

##3) Creado en punto 2) la funcion naturalesg xd

#--------------------------------------------------------------------------------------------------------------------
##4)
def sumana (n,m):
    if(n<m):
        return n+sumana(n+1,m)
    else:
        return m

def suman50 ():
    sumana(0,50)
#--------------------------------------------------------------------------------------------------------------------
#5)

def sumann (m):
    return sumana (0,m)
#--------------------------------------------------------------------------------------------------------------------
#6) funcion definida en 4): sumana
#--------------------------------------------------------------------------------------------------------------------
#7)
def duplica (a):
    return a+a
#--------------------------------------------------------------------------------------------------------------------
#8)
def duplica2 (a, n):
    return duplaux(a,0,n)

def duplaux(a,n,m):
    if(n<m):
        return a+duplaux(a,n+1,m)
    else:
        return a
#--------------------------------------------------------------------------------------------------------------------
#9)a)
def suma3 ():
    i=int(input("ingrese el 1er n a sumar \n"))
    q=int(input("ingrese el 2do n a sumar \n"))
    print(i+q)
##suma3()
def mult ():
    i=int(input("ingrese el 1er n a mult \n"))
    q=int(input("ingrese el 2do n a mult \n"))
    print(i*q)

def rest():
    i=int(input("ingrese el numero que va a ser restado \n"))
    q=int(input("ingrese el numero que resta\n"))
    print(i-q)

def div ():
    i=int(input("ingrese el numerador \n"))
    q=int(input("ingrese el denominador\n"))
    print(i/q)

def operacion():
    o=(int(input("Ingrese un numero para elegir la operacion: \n 1-suma\n 2-resta \n 3-multiplicacion \n 4-division\n 5-Salir\n\t")))
    if(o==1):
        suma3()
        return operacion()
    if(o==2):
        mult()
        return operacion()
    if(o==3):
        rest()
        return operacion()
    if(o==4):
        div()
        return operacion()
    if(o==5):
        print("Bueno chau")
        return   
    print("NO se ha ingresado una opcion valida")
    operacion()

operacion()
       
       

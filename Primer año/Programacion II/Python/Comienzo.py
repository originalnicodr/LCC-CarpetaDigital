#HOLA SOY COMENTARIO XDDDDDD#

def suma(a, b):
    return a+b



def Factorial(a):
    if((a==0)or(a==1)):
        return 1
    else:
        return a * Factorial(a-1)

def Negatividad():
    n = int(input("Ingrese un numero\n\7"))
    if(n<0):
            print("El numero ingresado:",n," es negativo y por ende no puede realizarse la operacion")
    else:
            print("El resultado es: ",Factorial(n))
    


#Negatividad()

def impsuma ():
    a= int( input("ingrese el primer numero a sumar\n"))
    b= int( input("ingrese el segundo numero a sumar\n"))
    m= suma(a, b)
    print(m)
    return m
    #print(a+b)

impsuma ()


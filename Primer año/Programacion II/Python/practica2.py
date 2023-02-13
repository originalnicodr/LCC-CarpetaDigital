#ej 1)--------------------------------------------------------------------------
#Los numeros se representan con numeros
#buclenumeros: Nan -> numeros impresos por pantalla
#Imprime los numeros del 10 al 20
def buclenumeros():
    for i in range (10,21):
        print(i)
#buclenumeros()

#ej 2)--------------------------------------------------------------------------
#Las fichas de domino se representan por pares de numeros
#fichasdomino: Nan -> numeros impresos por pantalla
#Imprime todas las fichas de domino posibles
def fichasdomino():
    for i in range (0,7):
        for j in range (i,7):
            print(i, ", ", j)
#fichasdomino()
#ej 3)--------------------------------------------------------------------------
#Las fichas de domino se representan por pares de numeros
#fichasdomino: numeros -> numeros impresos por pantalla
#Imprime todas las fichas de domino posibles
def fichasdominon(n):
    for i in range (0,n+1):
        for j in range (i,n+1):
            print(i, ", ", j)
#fichasdominon(3)
#ej 4)--------------------------------------------------------------------------
#El factorial de un numero se representa con un numero
#factorial: numero -> numero
#Ingrese la cantidad de numeros a los que calculara el factorial

def factorial(m):
    for i in range (0, m+1):
        a=(int(input("Ingrese el numero a calcular el factorial\n")))
        print(factaux(a))


def factaux(n):
    m=1
    for i in range (1, n+1):
        m=m*i
    return m
#ej 5)--------------------------------------------------------------------------
#Representamos temperaturas mediante números enteros
#farCel: Int -> Int
#El parámetro representa una temperatura en Fahrenheit y,
# se retorna su equivalente en Celsius.
# entrada: 32, salida: 0
# entrada: 212, salida: 100
# entrada: -40, salida: -40
def farCel(f):
    return (f-32)*5/9

def tablat():
    for i in range (0, 130, 10):
        print (farCel(i))
#tablat()
#ej 6)--------------------------------------------------------------------------
#Se representa un monto en pesos, la tasa de interes y la cantidad de años por medio de numeros
#interes: Numero Numero Numero -> Numero
#Ingresa un monto de dinero, una cantidad de años y una tasa de interes y devuelve el monto a cobrar
def interes (c, n, x):
    cn=c
    for i in range(0,n):
        cn=cn*(1+x/100)
    return cn
#ej 7)--------------------------------------------------------------------------
#Se representan numeros con numeros
#triangular: Numero -> Numeros impresos por pantalla
#Recibe un numero n e imprima los primeros n números triangulares, junto con su índice
def triangular (n):
    a=0
    for i in range (1, n+1):
        a=a+i
        print(i, " - ", a)
#ej 8)--------------------------------------------------------------------------
#Representa un numeros a ingresar con un numero y un mensaje en pantalla con un string
#positivo?: -> Imprime por pantalla un mensaje
#Ingresamos un numero, en caso de ser negativo se muestra un mensaje de error y se pide que lo vuelva a ingresar
def espositivo_signodepregunta():
    n=(int(input("Ingrese un numero positivo\n")))
    while (n<=0):
        n=(int(input("Idiota, ingrese un numero positivo como corresponde. Denunciado al fbi rufian\n")))
    print ("Muy bien!")
#espositivo_signodepregunta()
#ej 9)--------------------------------------------------------------------------
#Representa notas con numeros y un promedio con un numero
#promedio: Nan -> Nan (no nos mostraba nada si usabamos return)
#Ingresamos noras y cuando hayamos terminado, escribiremos "no" y nos dara el promedio
def promedio():
    n=(int(input("Ingrese una nota a promediar\n")))
    a=1
    s='si'
    while ((s=='si')or(s=='Si')or(s=='yes')):
           n=n+(int(input("Ingrese una nota a promediar\n")))
           a=a+1
           s=(input("¿Desea seguir ingresando notas?\n"))
    print (n/a) #(no nos mostraba nada si usabamos return)
#promedio()
#ej 10)--------------------------------------------------------------------------
#Representa numeros con numeros
#mayor: Numero Numero -> Imprime por pantalla los numeros ingresados
#Recibe dos numeros, si el primero es mayor al segundo, vuelve a pedir el ingreso de este hasta que el primero sea menor al segundo, imprimendo el primer numero y el ultimo
#numero ingresado correctamente

def mayor(n,m):
    while(n>=m):
        m=(int(input("Volve a ingresar el numero bien man\n")))
    print(n, "<", m)
#ej 11)--------------------------------------------------------------------------
#muliplos: Numero Numero -> Numero
#recibe dos números como parámetros, y devuelve cuántos múltiplos del primero hay, que sean menores que el segundo.

def multiplos(n,m):
    c=n
    i=0
    while(c<m):
        c=n*i
        if (c<m):
            i=i+1
    return i

#muliplosf: Numero Numero -> Numero
#recibe dos números como parámetros, y devuelve cuántos múltiplos del primero hay, que sean menores que el segundo.

def multiplosf(n,m):
    c=0
    for i in range(0,m,n):
        c=c+1
    return c
#LA FORMA DE HACERLO CON WHILE ES MAS COMPRENSIBLE Y TE OCUPA MAS MEMORIA, POR ENDE SOS IMPUTABLE CON 256MB DE RAM, PERO EN CAMBIO SI LO HACES CON FOR Y SOS HABIL PROGRAMADOR
#LA MEMORIA TE BANCA TODO Y SOS INIMPUTABLE HERMANO, EN 10 DIAS TE HACKEAS LA NASA

#ej 12)--------------------------------------------------------------------------
#Se representa una contraseña con un string
#contraseña: Nan -> Mensaje en pantalla
#Pide que se ingrese una contraseña, y si no se ingresa la correcta, pide que la vuelvas a ingresar

def contraseña():
    s=(input("Ingrese la contraseña\n"))
    while (s!='crippling_depression'):
        s=(input('Acceso denegado, contraseña erronea. Vuelva a ingresarla\n'))
    print('Access granted')
#contraseña()

#b)
#Se representa una contraseña con un string
#contraseña2: Nan -> Mensaje en pantalla
#Pide que se ingrese una contraseña, y si no se ingresa la correcta, pide que la vuelvas a ingresar

def contraseña2():
    o=0
    for i in range (0,3):
        s=(input("Ingrese la contraseña\n"))
        if (s=='crippling_depression'):
           print("Contraseña correcta xd")
           o=1
           return "xD"
    if(o==0):
        print("Te quedaste sin intentos hermano, llamando al fbi")

#contraseña2()

#c)
#Se representa una contraseña con un string
#contraseña3: Nan -> Mensaje en pantalla
#Pide que se ingrese una contraseña, y si no se ingresa la correcta, pide que la vuelvas a ingresar

def contraseña3():
    o=False
    for i in range (0,3):
        s=(input("Ingrese la contraseña\n"))
        if (s=='crippling_depression'):
           print("Contraseña correcta xd")
           o=True
           return "xD"
    if(o==False):
        print("Te quedaste sin intentos hermano, llamando al fbi")

#contraseña3()

#ej 13)--------------------------------------------------------------------------

#Se representa un numero con un numero
#es_primo: Numero -> Boolean
#Se ingresa un numero y se devuelve un true si es primo y un false si no lo es
def es_primo(n):
    a=0
    for i in range (2,n):
       if (n%i==0):
           a=a+1
    if (a==0):
        return True
    else:
        return False

#Se represta un numero con un numero
#primos: Numero -> imprime por pantalla numeros
#Se recibe un número natural e imprime todos los números primos que hay hasta ese número
def primos(n):
    c=1
    while (c<n):
        if(es_primo(c)):
            print(c)
        c=c+1
#ej 14)--------------------------------------------------------------------------
#a)
#Se representa un numero con un numero
#es_potencia_de_dos: Numero -> Boolean
#Se ingresa un numero, y si este es potencia de 2 se devuelve True, de lo contrario, False.
def es_potencia_de_dos(n):
    i=0
    while (2**i<=n):
        if(2**i==n):
            return True
        i=i+1
    return False
#b)
#Se representan numeros con numeros
#jojorefference: Numero Numero -> Numero
#Se ingresan dos numeros y se devuelve la suma de las las potencias de dos encontradas en el intervalo entre los dos numeros
#Suponemos que n<m

def jojorefference(n,m):
    a=n
    b=0
    while (a<=m):
       if(es_potencia_de_dos(a)):
           b=b+a
       a=a+1
    return b
        
        

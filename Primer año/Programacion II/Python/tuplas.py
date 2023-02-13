# ♥  ♣ ♦ ♠
#cartadepoker=(numero, palo)

def ingresarcartas():
    numero=(input("Ingrese el numero de la carta"))
    palo=(input("Ingrese el palo de la carta"))
    return (numero, palo)
def duplicadov2 (lis):
    n=0
    c=0
    for i in lis:
        print (i)
        if (i in lis[n+1:]):
            c+=1
        n+=1
    return (c==4)

def pokerpregunta():
    lista=[]
    ns=[]
    for i in range (0,5):
        lista+=[ingresarcartas()]
        ns+=[lista[i][0]]
    return duplicadov2(ns)

#tiempo(horas, minutos, segundos)
def sumaTiempo (t1, t2):
    s=0
    m=0
    h=0
    s=t1[2]+t2[2]
    if (s>=60):
        m=1
        s-=60
    m+=t1[1]+t2[1]
    if (m>=60):
        h=1
        m-=60
    h+=t1[0]+t2[0]
    return (h,m,s)

def bisiesto(a):
    if ((a%4==0)and(a%100!=0)or(a%400==0)):
        return True
    return False

#dia(Dia, Mes, Año)
def diaSiguiente(d):
    dia=d[0]
    mes=d[1]
    año=d[2]
    dias=[31,28,31,30,31,30,31,31,30,31,30,31]
    if bisiesto(año):
        dias[1]=29
    if (dia==dias[(mes-1)]):
        dia=1
        mes+=1   
    else:
        dia=d[0]+1
    if (mes>12):
        mes=1
        año+=1
    return (dia, mes, año)

#dia(Dia, Mes (string), Año)
def diaSiguienteT(d):
    meses=["Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"]
    m=0
    for i in range(0,len(meses)):
        if (d[1]==meses[i]):
            m=i+1
    dd=diaSiguiente((d[0],m,d[2]))
    return (dd[0], meses[dd[1]-1], dd[2])

def domino(a,b):
    for i in range(0,2):
        for j in range(0,2):
            if(a[i]==b[j]):
                return True
    return False

def adaptardomino(a):
    b=a[0].split('-', 1 )
    c=a[1].split('-', 1 )
    return domino((b[0],b[1]),(c[0],c[1]))
        
        

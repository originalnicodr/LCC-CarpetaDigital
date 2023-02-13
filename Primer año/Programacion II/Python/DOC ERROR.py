# -*- encoding: utf-8 -*-
import random

def activar_rayo():    
    modo=(input("Desea jugar en singleplayer o multiplayer? ingrese s o m para el modo de juego\n"))
    
    if(modo=='m'):
        codigo_secreto=(input("Ingrese el codigo super mega secreto."))
        j=int(codigo_secreto)
        
        while ((len(codigo_secreto)!=4)and(j<=999)and(j>=10000)):
            codigo_secreto=(input("MOZALBETE akso kieres k el max poder nos gane? xdxd."))

        print("\n"*1000)
        print("TE OQLTO EL KDIGO PRRO XDDDD NISMAN VIVE")
        return j
    else:
        j=random.choice (range(1000,10000))
        return j

def good_luck_max(codigo_secreto, numero_oportunidades):
    intento=int(input("INTENTA SALVAR LA UROPA XDDDDD\n"))
    i=1
    while(i<=numero_oportunidades):
        x=numero_oportunidades-i
        if(intento==codigo_secreto):
            print("Oie no, me as bencido xddddd")
            return
        if(intento<codigo_secreto):
            print("El numero que metiste es mainor\n")
            print("Intentos restantes:",x)
        else:
            print("el namber es meior\n")
            print("Intentos restantes:",x)
        i=i+1
        intento=int(input("hintenta nuebament\n"))
        if((numero_oportunidades-i)==3):
            u=codigo_secreto-(int(codigo_secreto/10) *10)
            print("Ers muy bruto, aki te paso el ultimo digito: _ _ _",u)
    print ("jaja peruano uropa a splotado el numero es:",codigo_secreto)

"# La siguiente línea indica la acción que se realizará"
"# al llamar el archivo desde la terminal."
codigo_secreto = activar_rayo()
good_luck_max(codigo_secreto, 10)

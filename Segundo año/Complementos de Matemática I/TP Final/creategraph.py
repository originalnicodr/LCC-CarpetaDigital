import random

def creategraph(n):
    #f= open("grafotest.txt","w+")
    V=[]
    for i in range(n):
        #f.write(i + " ")
        V.append(i)
    m=random.randint(n,int((n-1)*(n-2)/2))#(n-1)*(n-2)/2 es de grafo completo
    E=[]#lista de aristas
    for j in range(m):
        e=(random.randint(0,n-1),random.randint(0,n-1))#aristas
        if(not((e in E)and((e[1], e[0]) in E)) and (e[0]!=e[1])):
            E.append(e)
        else:
            #j=j-1
			pass
    for v in V:#si me faltan aristas para vertices
        tiene=0
        for e in E:
            if (v in e):
                tiene=1
        if (tiene==0):
            print("Hay un vertice sin arista")
            vt=E.append((v,random.randint(0,n-1)))
            while(e==vt(1)):
                vt=E.append((v,random.randint(0,n-1)))
    return (V,E)#grafo
def savegraph(g):
    f= open("grafotest.txt","w+")
    V,E=g
    f.write("%d\n" % len(g[0]))
    #vertices=""
    for v in V:
        #vertices+=" "+'v'
        f.write("%d\n"% v)
    #f.write(vertices"\n")
    #f.write("\n")
    for e in E:
        f.write("%d %d\n" % (e[0], e[1]))
    f.close()

if __name__=="__main__":
    g=creategraph(100)
    savegraph(g)

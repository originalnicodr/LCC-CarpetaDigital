//Ejercicio 1

function y=f1(x)//la funcion a graficar
    y=cos(x).*(exp(x)+exp(-x))/2+1
endfunction

function y=nula(x)
    y=zeros(1,length(x))
endfunction

//Grafica ej1
//x=[0:0.1:10]
//plot(x,f1(x))
//plot(x,nula(x))

//Ejercicio 2

function y=biyeccionaux(f,a,b,e)//metodo de la biseccion
    c=(a+b)/2
    if (b-c<=e) then
        y=c
        return 
    else
        if f(b)*f(c)<=0 then
            y = biyeccionaux(f,c,b,e)
        else
            y = biyeccionaux(f,a,c,e)
        end
    end
endfunction

//ecuaciones a las que les aplicas biseccion

function y=f2(x)
    y=sin(x)-(x**2/2)
endfunction

function y=f3(x)
    y=exp(-x)-x**4
endfunction

function y=f4(x)
    y=log(x)-x+1
endfunction


//Ejercicio 3

function y=Msecante(f,a,b,e)//b es Xn+1 y a es Xn //metodo de la secante
    
    while abs(f(b))>e//es decir si esta cerca de la raiz
        x=b
        b=(b-f(b)*((b-a)/(f(b)-f(a))))
        a=x
    end
    y=b
endfunction

function y=f5(x)//raices en 0 y en 1.9338445
    y=((x**2)/4)-sin(x)
endfunction

//Ejercicio 4
//neeh scilab no se banca los while grandes
//la funcion va a converger a un numero en particular
function y=cosB(n)
    x=%pi
    i=0
    while i<n
        x=cos(x) 
    end
    y=x
endfunction


//Ejercicio 5 //que estoy usando?

function y=E5(f,a,e)
    while abs(f(a))>e
        a=2**(a-1)
    end
    y=a
endfunction

function y=f6(x)
    y=2*x-2**x
endfunction

//La iteracion converge cuando x0<2, en 2 converge a 2, y en un numero menor a 2 es 1

//Ejercicio 6

function y=PuntoFijo(g,x,e)//g funcion, x inicial, e tolerancia
   a=e+1//iniciamos
   while (%T)
      a=x//a es x anterior
      x=g(x)
      if (abs(a-x)<e) then
          break
      end
   end
   y=x
          
endfunction
//calculo de c en papel= (5)**(1/2)/10
function y=ConvergePF(g,a,b)//?
     if a<=x<=b then
        if a<=g(a)&g(b)<=b then
            f=derivat(g)
            x=a:1:b
            if f(x)<1 then y=1
            else y=0
            end
        else y=0
        end
     else y=0
     end
endfunction

//function y=Convergencia(g,a,b) //problema de la parada?
//     if a<=x<=b then
//        if a<=g(a)&g(b)<=b then
//            f=derivat(g)
//            x=a:1:b
//            if f(x)<1 then y=1
//            else y=0
//            end
//        else y=0
//        end
//     else y=0
//     end
//endfunction

function y=f7(x)
    y=x+((-1*(5**1/2))/10)*(x**2-5)
endfunction


//Ejercicio 7

//Prundidad h=4m
//Periodo T
//Longitud de onda l
//Dispersion w^2=gdtanh(hd)
//Una pulsación w=2pi/T
//Aceleracion de la graveda g=9,8m/s^2
//Número de onda d=2pi/l
//Longitud de onda de T=5s???
//l=2pi/d


//d=1
function y=l(d)
    y=2*%pi/d
endfunction

function y=wreal(T)
    y=2*%pi/T
endfunction

function y=w2(g,d,h)
    y=g*d*tanh(h*d)
endfunction

function y=w(g,d,h)
    y=sqrt(w2(g,d,h))
endfunction

function y=F7(g,d,h,T)
    y=g*d*tanh(h*d)-(2*%pi/T)**2
endfunction

g1=9.8
h1=4
T1=5

function y=test(d)
    y=F7(g1,d,h1,T1)
endfunction

function y=pf(d)
    y=w2(g1,d,h1)/((9.8)*tanh(4*d))
endfunction

function y=pfm(d)
    y=w2(g1,d,h1)/((9.8)*tanh(4*d))-d
endfunction

//PuntoFijo(pf,1,10**(-5))
//PuntoFijo(test,1,10**(-5))
//lleva a infinito

function y=Newton(f,x,tol)//x inicial //Metodo de Newton
    x0=x
    while(%T)
        if(numderivative(f,x0)==0) then
            printf('Error, derivada evaluada en x0 dio 0')//ver si sale bien el print
            break
        end  
        y=x0-f(x0)/numderivative(f,x0)
        if(abs(y-x0)<tol) then
            break
        end
        x0=y
    end
endfunction
//resultado 7)b) 0.1958630
//que deberiamos haber obtenido en a)?

//Ej 8

function y=g8_1(x)
    y=exp(x)/3
endfunction
function y=g8_2(x)
    y=(exp(x)-x)/2
endfunction
function y=g8_3(x)
    y=log(3*x)
endfunction
function y=g8_4(x)
    y=exp(x)-2*x
endfunction

//Control + D para comentar
//Control + Shift + D para descomentar

//function y=Newtonmulti(f1,f2,f1dx,f1dy,f2dx,f2dy,x,tol)//x tiene dim 2 las d son las derivadas
//    y=x
//    J=zeros(2,2)
//    while (%T)
//        x0=y
//        //J(1,1)=numderivative(f1,x(1))
//        //J(1,2)=numderivative(f1,x(2))
//        //J(2,1)=numderivative(f2,x(1))
//        //J(2,2)=numderivative(f2,x(2))
//        J(1,1)=f1dx(x(1))
//        J(1,2)=f1dy(x(2))
//        J(2,1)=f2dx(x(1))
//        J(2,2)=f2dy(x(2))
//        if(det(J)==0) then
//            printf('Error, matriz jacobiana es singular')//ver si sale bien el print
//            break
//        end
//        y=x0-inv(J)*[f1(x0(1)),f2(x0(2))]//transpuesta?
//        if sqrt(abs(x0-y)*(abs(x0-y)'))<tol then
//            break
//        end
//    end
//endfunction
//
//function a=f1(x,y)
//    a=x**2+x*y**3-9
//endfunction
//function a=f2(x,y)
//    a=2*x*y +exp(x)*sin(y)
//endfunction
//
//function a=f1x(x,y)
//    a=2*x+y**3
//endfunction
//function a=f1y(x,y)
//    a=3*x*y**2
//endfunction
//function a=f2x(x,y)
//    a=2*y+exp(x)*sin(y)
//endfunction
//function a=f2y(x,y)
//    a=2*x+exp(x)*cos(y)
//endfunction
//Newtonmulti(f1,f2,f1x,f1y,f2x,f2y,[1.2,2.5],10**(-3))


//Ej 9 Voy a usar varias funciones para calcular la jacobiana, por que varian las derivadas que tengo que usar en la matriz
function x= newtonJaclimitado(f1, f2, x0, tol)//5 iteraciones es lo que pide el ejercicio
    jacob = zeros(2,2)
    x=x0//inicializo por si no me alcanza a iterar por que la jacobiana es singular y devuelva algo
    for i=1:5
        jacob(1,1) = 2*x0(1)+exp(x0(1))*cos(x0(2))
        jacob(1,2) = -2*x0(2)-exp(x0(1))*sin(x0(2))
        jacob(2,1) = 2*x0(2)+exp(x0(1))*sin(x0(2))
        jacob(2,2) = 2*x0(1)+exp(x0(1))*cos(x0(2))
        vector=[f1(x0); f2(x0)]
//        if(det(jacob)==0) then
//            printf('Error, matriz jacobiana es singular')
//            break
//        end
        x=x0-(inv(jacob)*vector)
        if abs(x0-x)<tol then//no me dejaba usar la norma
            break
        end
        x0=x
    end
endfunction

deff('y=f9_1(x)','y=1+x(1)**2-x(2)**2+exp(x(1))*cos(x(2))')
deff('y=f9_2(x)','y=2*x(1)*x(2)+exp(x(1))*sin(x(2))')

//Resultado:   [-0.2931627;1.1726598]

//function x= newtonJac1(f1, f2, x0, tol)
//    jacob = zeros(2,2)
//    x=x0//inicializo por si no me alcanza a iterar por que la jacobiana es singular y devuelva algo
//    while (%T)
//        jacob(1,1) = 2*x0(1)+exp(x0(1))*cos(x0(2))
//        jacob(1,2) = -2*x0(2)-exp(x0(1))*sin(x0(2))
//        jacob(2,1) = 2*x0(2)+exp(x0(1))*sin(x0(2))
//        jacob(2,2) = 2*x0(1)+exp(x0(1))*cos(x0(2))
//        vector=[f1(x0); f2(x0)]
////        if(det(jacob)==0) then
////            printf('Error, matriz jacobiana es singular')
////            break
////        end
//        x=x0-(inv(jacob)*vector)
//        if abs(x0-x)<tol then//no me dejaba usar la norma
//            break
//        end
//        x0=x
//    end
//endfunction

//Ej 10

function x= newtonJac_10(f1, f2, x0, tol)
    jacob = zeros(2,2)
    while (%T)
        jacob(1,1) = 2*x0(1)+x0(2)**3
        jacob(1,2) = x0(1)*3*(x0(2)**2)
        jacob(2,1) = 6*x0(1)*x0(2)
        jacob(2,2) = 3*(x0(1)**2)-3*(x0(2)**2)
        vector=[f1(x0); f2(x0)]
        if(det(jacob)==0) then
            printf('Error, matriz jacobiana es singular')
            break
        end
        x=x0-(inv(jacob)*vector)
        if abs(x0-x)<tol then//no me dejaba usar la norma
            break
        end
        x0=x
    end
endfunction


deff('y=f10_1(x)','y=(x(1)**2)+x(1)*(x(2)**3)-9')
deff('y=f10_2(x)','y=3*(x(1)**2)*x(2)-4-(x(2)**3)')


xa=[1.2; 2.5]
xb=[-2; 2.5]
xc=[-1.2; -2.5]
xd=[2 ;-2.5]

//resultado con xa:    [1.3363554;1.7542352]
//resultado con xb:    [  -0.9012662;-2.0865876]
//resultado con xc:    [  -0.9012662;-2.0865876]
//resultado con xd:    [  -3.0016249;0.148108]

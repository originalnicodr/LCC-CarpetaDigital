//Ejercicio 1

function linealPol()
endfunction

function y = TrapecioSimple(a,b,fn)
    h = b-a
    y = h * ((fn(a)+fn(b))/2)
endfunction

function y = SimpsonSimple(a,b,fn)
    h = b-a
    y = (h/6) * (fn(a)+4*fn((a+b)/2) + fn(b))
endfunction

// a) TrapecioSimple(1,2,log)
//    SimpsonSimple(1,2,log)
a1 = TrapecioSimple(1,2,log)
a2 = SimpsonSimple(1,2,log)

function y = TrapecioCompuesto(a,b,f,n)
    h = (b-a)/n
    for j=1:n-1
        X(j) = a+j*h
    end
    resultado = 0
    for j=1:n-1
        resultado = resultado + f(X(j))
    end
    y = h* (resultado + f(a)/2 + f(b)/2)
    
endfunction

function y = SimpsonCompuesto(a,b,f,n)
    h = (b-a)/n
    
    for j=1:n-1
        X(j)= a+j*h
    end
    
    resultado = 0
    
    for j=1:n-1
        if modulo(j,2) == 0 then
            resultado = resultado + 2*f(X(j))
        else
            resultado = resultado + 4*f(X(j))
        end
    end
    
    y = (h/3) * (f(a) + resultado + f(b))
    
endfunction

deff("y=f1(x)","y=(1/x)")
deff("y=f2(x)","y=x**3")
deff("y=f3(x)","y=x*sqrt(1+x**2)")
deff("y=f4(x)","y=sin(%pi*x)")
deff("y=f5(x)","y=x*sin(x)")
deff("y=f6(x)","y=(x**2)*exp(x)")

//EJ 2
disp(TrapecioCompuesto(1,3,f1,4),"TRAP N=4",integrate('f1(x)','x',1,3),"INTEGRATE F1")
disp(TrapecioCompuesto(0,2,f2,4),"TRAP N=4",integrate('f2(x)','x',0,2),"INTEGRATE F2")
disp(TrapecioCompuesto(0,3,f3,6),"TRAP N=6",integrate('f3(x)','x',0,3),"INTEGRATE F3")
disp(TrapecioCompuesto(0,1,f4,8),"TRAP N=8",integrate('f4(x)','x',0,1),"INTEGRATE F4")
disp(TrapecioCompuesto(0,2*%pi,f5,8),"TRAP N=8",integrate('f5(x)','x',0,2*%pi),"INTEGRATE F5")
disp(TrapecioCompuesto(0,1,f6,8),"TRAP N=8",integrate('f6(x)','x',0,1),"INTEGRATE F6")

//EJ3

disp(SimpsonCompuesto(1,3,f1,4),"SIMP N=4",integrate('f1(x)','x',1,3),"INTEGRATE F1")
disp(SimpsonCompuesto(0,2,f2,4),"SIMP N=4",integrate('f2(x)','x',0,2),"INTEGRATE F2")
disp(SimpsonCompuesto(0,3,f3,6),"SIMP N=6",integrate('f3(x)','x',0,3),"INTEGRATE F3")
disp(SimpsonCompuesto(0,1,f4,8),"SIMP N=8",integrate('f4(x)','x',0,1),"INTEGRATE F4")
disp(SimpsonCompuesto(0,2*%pi,f5,8),"SIMP N=8",integrate('f5(x)','x',0,2*%pi),"INTEGRATE F5")
disp(SimpsonCompuesto(0,1,f6,8),"SIMP N=8",integrate('f6(x)','x',0,1),"INTEGRATE F6")

//EJ4

deff("y=f7(x)","y=1/(x+1)")
disp(TrapecioCompuesto(0,1.5,f7,10),"TRAP N=10",integrate('f7(x)','x',0,1.5),"INTEGRATE F7")
disp(SimpsonCompuesto(0,1.5,f7,10),"SIMP N=10",integrate('f7(x)','x',0,1.5),"INTEGRATE F7")

// Integracion bidimensional

function y = dosVariables(x1,x2)//Funcion del ejercicio
    y = sin(x1+x2)
endfunction

function y = c1(x)
    y = 0
endfunction

function y = d1(x)
    y = 1
endfunction

// 1.60965 VALOR APROX

// Toma una funcion, limites a,b, funciones c(x), d(x), n-intervalos de x y m-intevalos de y.

function y = intBidimensionalS(fn,a,b,cx,dx,n,m)//Aplico metodo de Simpson compuesto a una integral doble
    deff('z=aux1(y)','z=fn(a,y)')
    deff('z=aux2(y)','z=fn(b,y)')
    temp= SimpsonCompuesto(cx(a),dx(a),aux1,m) + SimpsonCompuesto(cx(b),dx(b),aux2,m)
    
    h = (b-a)/n
    for i=1:n-1
        xi = a+i*h
        deff('z=aux(y)','z=fn(xi,y)')
        if modulo(i,2) == 0 then
            temp = temp + 2*(SimpsonCompuesto(cx(xi),dx(xi),aux,m))
        else
            temp = temp + 4*(SimpsonCompuesto(cx(xi),dx(xi),aux,m))
        end
    end
    y = (h/3) * temp
endfunction

// Toma una funcion, limites a,b, funciones c(x), d(x), n-intervalos de x y m-intevalos de y.

function y = intBidimensionalT(fn,a,b,cx,dx,n,m)//Aplico metodo del Trapecio compuesto a una integral doble
    deff('z=aux1(y)','z=fn(a,y)')
    deff('z=aux2(y)','z=fn(b,y)')
    temp= (TrapecioCompuesto(cx(a),dx(a),aux1,m)/2) + (TrapecioCompuesto(cx(b),dx(b),aux2,m)/2)
    h = (b-a)/n
    for i=1:n-1
        xi = a+i*h
        deff('z=aux(y)','z=fn(xi,y)')
        temp = temp + (SimpsonCompuesto(cx(xi),dx(xi),aux,m))
    end
    y = h * temp
endfunction

function y=cx1(x)
    y=-sqrt(2*x-x**2)
endfunction

function y=dx1(x)
    y=sqrt(2*x-x**2)
endfunction

function y=uno(x,y)
    y=1
endfunction

disp(intBidimensionalS(uno,0,2,cx1,dx1,1000,1000))

//Ej 6

function y=cx1(x)
    y=-sqrt(2*x-x**2)
endfunction

function y=dx1(x)
    y=sqrt(2*x-x**2)
endfunction

function y=uno(x,y)
    y=1
endfunction

disp(intBidimensionalS(uno,0,2,cx1,dx1,1000,1000))

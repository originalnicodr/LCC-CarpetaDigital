//Metodo de la Bisección
//biseccion: función f, extremo a, extremo b [a b], error e -> una raíz c 
function c=biseccion(f,a,b,e)
    if f(a)*f(b)<0 then //Teorema de Bolzano
        c=(a+b)/2 //Inicializamos c
        while (b-c>e) or (f(c)~=0) //Mientras el intervalo sea mayor el error y c no sea raíz iteramos
            c=(a+b)/2 //Calculo de c
            if f(c)*f(b)<0 then // c tiene el signo de a
                a=c
            else //c tiene el signo de b
                b=c
            end
        end
    end
endfunction

//Método de Newton-Raphson
//Newton: función f, x0 inicial, error e -> una raíz x
//Convergencia garantizada para x0 cerca a alfa
function x=Newton(f,x,e)
    while abs(f(x))>e//Mientras f(x) sea mayor que el error iteramos
        x=x-(f(x)/numderivative(f,x)) //creo que así hace f'(x)
    end
endfunction

//Método de la secante
//secante: función f, a b inciales, error e -> una raíz x
function x=secante(f,a,b,e)
    while abs(f(b))>e
        x=b
        b=b-f(b)*((b-a)/(f(b)-f(a)))
        a=x
    end
endfunction

function y = cuadr(x)
    y = 1-x^2
endfunction

function y= g1(x)
    y = x - cuadr(x)
endfunction

//Método de la falsa posición 
//Combinación de los métodos de la secante y la bisección
//falsaposicion: función f,a b inciales [a,b], error e ->raíz c
function c=falsaposicion(f,a,b,e)
    c=b-f(b)*((b-a)/(f(b)-f(a)))//Inicializamos c
    while abs(f(c))>e
        if f(a)*f(c)<0 then //c tiene el mismo signo que b
            b=c
        else//c tiene el mismo signo que a
            a=c
        end
        c=b-f(b)*((b-a)/(f(b)-f(a))) //calculamos el nuevo valor de c
    end
endfunction


//Método de punto fijo
//puntofijo: función g, x0 incial, error e -> punto fijo x
//Para calcular raices de una función f tomar un g(x)=x-cf(x) c>0 
function x=puntofijo(g,x,e)
    while e~=0
        x=g(x)
        e=e-1
    end
endfunction

function b=horner2(a,x)//evaluar de forma eficiente funcionen polinomicas
    coef=degree(a)
    b=0
    for j=coef:-1:0
        b=coeff(a,j)+x*b
    end
endfunction

function [b,c]=hornerg(a,x)//calcula p(x0) y p'(x0)
    coef=degree(a)
    b=0
    c=0
    for j=coef:-1:0
        c=c+b*(x**j)
        b=coeff(a,j)+x*b
        
    end
endfunction

function b = hornerLista(p,x)
    cantCoef = degree(p) +1
    b = 0
    for j= cantCoef-1:-1:0
        b = coeff(p, j)+ x*b
    end
endfunction

function y=derivar(f,v,n,h)//funcion, v donde evaluas, n el numero de derivada, h muy chico
    i=1
    y= derivaraux(f,v,n,h,i)
endfunction

function a=derivaraux(f, v, n, h,i)
    if (i==n) then
        a=(f(v+h)-f(v))/h
    else a=(derivaraux(f, v+h, n, h,i+1)-derivaraux(f, v, n, h,i+1))/h
end
endfunction

function y=derivada(D0,n,x,h)//derivada fede
    for i=1:(n-1)
//        deff("y=D"+string(i)+"(x)","y=numderivative(D"+string(i)+",x,h)")
        deff("y=D"+string(i)+"(x)","y=(D"+string(i-1)+"(x+h)-D"+string(i-1)+"(x))/h")
    end
//    deff("y=Dn(x)","y=numderivative(D"+string(n-1)+",x,h)")
        deff("y=Dn(x)","y=(D"+string(n-1)+"(x+h)-D"+string(n-1)+"(x))/h")
    y = Dn(x)
endfunction

function t=taylor(f,x,a,n)//funcion, x donde evaluas, a donde es derivable, n grado de taylor
    t=f(a)
    for i=1:n
        t=t+derivar(f,x,i,10**(-3))*(x-a)**(i-1)/factorial(i-1)
    end
endfunction

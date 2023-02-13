function b=horner2(a,x)
    coef=degree(a)
    b=0
    for j=coef:-1:0
        b=coeff(a,j)+x*b
    end
endfunction

function [b,c]=hornerg(a,x)
    coef=degree(a)
    b=0
    c=0
    for j=coef:-1:0
        c=c+b*(x**j)
        b=coeff(a,j)+x*b
        
    end
endfunction

function y=derivar(f,v,n,h)
    i=1
    y= derivaraux(f,v,n,h,i)
endfunction

function a=derivaraux(f, v, n, h,i)
    if (i==n)
        a=(f(v+h)-f(v))/h
    then a=(derivaraux(f, v+h, n, h,i+1)-derivaraux(f, v, n, h,i+1))/h
end
if  then
    else
end
endfunction

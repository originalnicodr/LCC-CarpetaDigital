function n=norma(a)
    n=(a'*a)**(1/2)
endfunction

function x=Gauss_Seidel(A,b)//podriamos meter como argumento el x inicial
    m=size(A,1)
    x=zeros(m,1)
    xaux=x
    while %T//Do while
        xaux=x
        for i=1:m
            term=0
            for j=1:m
                if i~=j then//termino que voy a restar
                    term=term+A(i,j)*x(j)
                end
            end
            x(i)=(1/A(i,i))*(b(i)-term)
        end
        if norma(x-xaux)<10**(-6) then break; end
    end
endfunction
//gauss seidel tarda la mitad de iteraciones

function x=Gauss_Seidelerror(A,b,e)//Misma funcion de Gauss Seidel para resolver sistemas pero con tolerancia personalizada
    //tic()
    m=size(A,1)
    x=zeros(m,1)
    xaux=x
    while %T//Do while
        xaux=x
        for i=1:m
            term=0
            for j=1:m
                if i~=j then
                    term=term+A(i,j)*x(j)
                end
            end
            x(i)=(1/A(i,i))*(b(i)-term)
        end
        if norma(x-xaux)<e then break; end
    end
    //t=toc()
    //disp(t)
endfunction

//n=500 en gauss seidel tarda 10.298 segundos con e=10**(-6)
//n=500 en gauss seidel tarda 26.178 segundos con e=10**(-12)
//n=1000 en gauss seidel tarda 41.451 segundos con e=10**(-6)
//n=1000 en gauss seidel tarda 105.349 segundos con e=10**(-12)

//n=1000

//A = 8*eye(n,n) + 2*diag(ones(n-1,1),1) + 2*diag(ones(n-1,1),-1) + diag(ones(n-3,1),3) + diag(ones(n-3,1),-3)
//b = ones(n,1)

function x=sor(A,b,w,e)//A matriz, b matriz de resultado, w es w del metodo y e el error para determinar cuando terminarlo //Metodo de sobrerelajacion
    m=size(A,1)
    x=zeros(m,1)
    xaux=x
    while %T//Do while
        xaux=x
        for i=1:m
            term=0
            for j=1:m
                if i~=j then
                    term=term+A(i,j)*x(j)
                end
            end
            x(i)=(1-w)*x(i)+(w/A(i,i))*(b(i)-term)
        end
        if norma(x-xaux)<e then break; end
    end
endfunction

function a=RadioEspectral(A)
    x=spec(A)
    a=x(1)
    for i=1:size(A,1)
        if abs(a)<abs(x(i)) then
            a=x(i)
        end
    end
    
endfunction

function w=woptima(A)
    Tj=eye(size(A,1),size(A,1))-inv(diagon(A))*A
    w=2/(1+sqrt((1-(RadioEspectral(Tj))**2)))
endfunction

function w = eleccionW(A)
  D = diagon(A)
  I = eye(D)
  Tj = I - inv(D)*A
  radio_espectral = RadioEspectral(Tj)*RadioEspectral(Tj)
  w = 2/(1+sqrt(1-radio_espectral))
endfunction

function D=diagon(A)//Saca la diagonal de la matriz A= L + D + U
    D=eye(size(A))
    for i=1:size(A,1)
        D(i,i)=A(i,i)
    end
endfunction

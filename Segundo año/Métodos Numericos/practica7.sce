//Ej1
//Metodo de Lagrange
//Lagrange: vector X, función f, un valor x -> P(x)
//Dado un conjunto de puntos, una función devuelve el valor a
//proximados de la función evaluada en el valor x

function y=Lagrange(Y,X,x)//Y:vector de imagenes, X: vector de x (como columna creo), x: donde evaluas
    m=size(X,1)
    y=0;
    for i=1:m
        L=1;
        for j=1:m
            if j~=i then
                L=(x-X(j))/(X(i)-X(j))*L;
            end
        end
        y=y+L*Y(i)
    end
endfunction

X=0:0.2:0.6

function y=DDNewton(Y,X,x)//Y:vector de imagenes, X: vector de x (como columna creo), x: donde evaluas
     m=size(X,1);
     y=0
     D = DiferenciaDividida(Y,X)
     for i=1:m
         a = D(i)
         for j=1:i-1
             a = a*(x-X(j))
         end
         y = y+a
     end
endfunction
 
function Y=DiferenciaDividida(Y,X)//funcion y vector de puntos, devuelve un vector de diferencias divididas (f[x0], f[x0,x1],...)
    m = size(X,1)
    Z = zeros(m)
    Z=Y
    for i=2:m
        for j=i:m
            Z(j) = (Y(j)-Y(j-1))/(X(j)-X(j-i+1))
            //disp(Y)
        end 
        Y = Z
    end
endfunction

X=[0; 0.2; 0.4; 0.6]
Y=[1.0; 1.2214; 1.4918; 1.8221]

X1 = [0; 0.2]
Y1 = [1.0; 1.2214]

X2 = [0; 0.4]
Y2 = [1.0; 1.4918]

X3 = [0; 0.6]
Y3 = [1.0; 1.8221]

X4 = [0.2; 0.4]
Y4 = [1.2214; 1.4918]

X5 = [0.2; 0.6]
Y5 = [1.2214; 1.8221]

X6 = [0.4; 0.6]
Y6 = [1.4918; 1.8221]

X7 = [0; 0.2; 0.4]
Y7 = [1.0; 1.2214; 1.4918]

X8 = [0; 0.2; 0.6]
Y8 = [1.0; 1.2214; 1.4918]

X9 = [0; 0.4; 0.6]
Y9 = [1.0; 1.4918; 1.8221]

X10 = [0.2; 0.4; 0.6]
Y10 = [1.2214; 1.4918; 1.8221]

//y1=DDNewton(Y1,X1,1/3)
//y2=DDNewton(Y2,X2,1/3)
//y3=DDNewton(Y3,X3,1/3)
//y4=DDNewton(Y4,X4,1/3)
//y5=DDNewton(Y5,X5,1/3)
//y6=DDNewton(Y6,X6,1/3)
//y7=DDNewton(Y7,X7,1/3)
//y8=DDNewton(Y8,X8,1/3)
//y9=DDNewton(Y9,X9,1/3)
//y10=DDNewton(Y10,X10,1/3)
y=DDNewton(Y,X,1/3)

printf("Newton\n")
//disp(y1)
//disp(y2)
//disp(y3)
//disp(y4)
//disp(y5)
//disp(y6)
//disp(y7)
//disp(y8)
//disp(y9)
//disp(y10)
disp(y)

// resultados
//    1.4071333  
// 
//    1.4972667  
// 
//    1.6073667  
// 
//    1.4203067  
// 
//    1.4643467  
// 
//    1.3703267  
// 
//    1.4734356  
// 
//    1.4734356  
// 
//    1.4567756  
// 
//    1.4041102  
// 
//    1.4680367  
// 

printf("Lagrange\n")

//z1=Lagrange(Y1,X1,1/3)
//z2=Lagrange(Y2,X2,1/3)
//z3=Lagrange(Y3,X3,1/3)
//z4=Lagrange(Y4,X4,1/3)
//z5=Lagrange(Y5,X5,1/3)
//z6=Lagrange(Y6,X6,1/3)
//z7=Lagrange(Y7,X7,1/3)
//z8=Lagrange(Y8,X8,1/3)
//z9=Lagrange(Y9,X9,1/3)
//z10=Lagrange(Y10,X10,1/3)
z=Lagrange(Y,X,1/3)

//disp(z1)
//disp(z2)
//disp(z3)
//disp(z4)
//disp(z5)
//disp(z6)
//disp(z7)
//disp(z8)
//disp(z9)
//disp(z10)
disp(z)

// resultados
//    1.369  
// 
//    1.4098333  
// 
//    1.4567222  
// 
//    1.4016667  
// 
//    1.4216333  
// 
//    1.3817  
// 
//    1.3962222  
// 
//    1.3370741  
// 
//    1.3942037  
// 
//    1.3950111  
// 
//    1.3955494

printf("Ej4\n")

X_4=[2;2.1;2.2;2.3;2.4;2.5]
Y_4=[0.2239;0.1666;0.1104;0.0555;0.0025;-0.0484]

//Ej 7

//X = [0; 0.15; 0.31; 0.5; 0.6; 0.75]
//Y = [1; 1.004; 1.031; 1.117; 1.223; 1.422]

function m = MatrizM(X,grado)//Genera matriz de Vandermonde, se da el vector de valores de x en donde se evalua y el grado vendria a ser la cantidad de columnas de la matriz
    n = size(X,1)
    M = 0
    
    for i=1:grado+1
        for j=1:n
            M(j,i) = X(j)^(i-1)
        end
    end
    
    m = M
endfunction

function m = MatrizMgeneral(X,funciones)//Genera la matriz a utilizar en problemas de minimo cuadrado, se da el vector de valores y el vector de funciones (esta ultima como list(f1,f2,...)
    n = size(X,1)
    nF = size(funciones)

    M = 0

    for i=1:nF
        for j=1:n
            M(j,i) = funciones(i)(X(j))
        end
    end
    m = M
endfunction

function [Q,R]=QR(A)
    [m,n]=size(A)
    Q=zeros(m,n)
    R=zeros(n,n)
    J=zeros(n,1)
    Q(:,1) = A(:,1)
    J(1) = norm(A(:,1))
    Q(:,1) = Q(:,1)/J(1)
    for k=2:n
        suma=0
        for i=1:k-1
            R(i,k) = A(:,k)'*Q(:,i)
            suma = suma+R(i,k)*Q(:,i)
        end
        Q(:,k) = A(:,k)-suma
        J(k) = norm(Q(:,k))
        Q(:,k) = Q(:,k)/J(k)
    end
    R = R+diag(J)
endfunction

function s1 = remonte(A, b)
    n = size(A,1)
    X = zeros(n,1)
    for i = n:-1:1
        X(i) = (b(i) - A(i,i+1:n)*X(i+1:n)) / A(i,i)
    end
    s1 = X
endfunction

function P = polinomioAproxviejo(X,Y,grado)//Resolucion del problema de minimos cuadrados usando la matriz de Vandermonde
    M = MatrizM(X,grado)
    INV = inv(M'*M)
    bPrima = M'*Y
    P = poly((INV*bPrima)','x','coeff')
endfunction


function P = polinomioAprox(X,Y,grado)
    M=MatrizM(X,grado)
    [Q,R] = QR(M)
    y2 = Q'*Y
    a = remonte(R, y2)
    P = poly((a)','x','coeff')
endfunction

function P = polinomioAproxGeneralviejo(X,Y,funciones)//Resolucion del problema de minimos cuadrados usando una lista de funciones
    M = MatrizMgeneral(X,funciones)
    INV = inv(M'*M)
    bPrima = M'*Y
    P = poly((INV*bPrima)','x','coeff')
endfunction

function P = polinomioAproxGeneral(X,Y,grado)
    M=MatrizMgeneral(X,grado)
    [Q,R] = QR(M)
    y2 = Q'*Y
    a = remonte(R, y2)
    P = poly((a)','x','coeff')
endfunction

function ploty(fn,l,in,r) // Funcion, Limite Izq, Intervalo, Limite Der
    x = [l:in:r];
    y = fn(x);
    n = size(x);
    yy = zeros(1,n(2));
    plot(x,yy)
    plot(x,y)
    a = gca();
    a.auto_scale = "off"; 
endfunction

X = [0; 0.15; 0.31; 0.5; 0.6; 0.75]
Y = [1; 1.004; 1.031; 1.117; 1.223; 1.422]

M = MatrizPolinomios(X,3)
P1 = polinomioAprox0(X,Y,M)
P2 = polinomioAprox(X,Y,M)
disp(P1)
disp(P2)

// Para hallar los polinomios de aproximacion por minimos cuadrados se debe
// utilizar la funcion polinomioAprox al cual le pasamos los nodos X,Y y el 
// grado del polinomio deseado.
//
// El polinomio que mejor aproxima los puntos (de grado 1,2 y 3) es el de grado 3.

X = [0 0.25 0.5 0.75]
Y = [2 1 0 1]

//Ej 8

X = [4;4.2;4.5;4.7;5.1;5.5;5.9;6.3;6.8;7.1]
Y = [102.56;113.18;130.11;142.05;167.53;195.14;224.87;256.73;299.5;326.72]

P1 = polinomioAprox(X,Y,1)
P2 = polinomioAprox(X,Y,2)
P3 = polinomioAprox(X,Y,3)

R1 = horner(P1,X)
R2 = horner(P2,X)
R3 = horner(P3,X)

disp(abs(Y-R1),'Resultado error de P1 con Y')
disp(abs(Y-R2),'Resultado error de P2 con Y')
disp(abs(Y-R3),'Resultado error de P3 con Y')


// Falta armar tabla de comparacion resultados.
// Preguntar relacion entre grado de polinomio y error.

//Ej 9

// N es la cantidad de intervalos
function [X,Y] = nodosEquiespaciados(fn,li,ld,n)
    h = (ld-li)/(n)
    for i=0:n
        X(i+1) = li+h*i
        Y(i+1) = fn(X(i+1))
    end
endfunction

function y = ejercicio(x)
    y = 1/(1+x^2)
endfunction

// Calculamos los nodos equiespaciados.
[X_2,Y_2] = nodosEquiespaciados(ejercicio,-5,-5,2)
[X_4,Y_4] = nodosEquiespaciados(ejercicio,-5,-5,4)
[X_6,Y_6] = nodosEquiespaciados(ejercicio,-5,-5,6)
[X_10,Y_10] = nodosEquiespaciados(ejercicio,-5,-5,10)
[X_14,Y_14] = nodosEquiespaciados(ejercicio,-5,-5,14)

function y = calcError(x)
    y = ejercicio(x) - DDNewton(X_2,Y_2,x)
endfunction

///ploty(ejercicio,-5,0.1,5)

// Para todos los x_i nos dio igual la grafica. VER

//Ejercicio 9

// Polichef
function P = Tn(n)//Devuelve el polinomio de Chebyshev de grado n
    T0 = poly([1],'x','coeff')
    T1 = poly([0 1],'x','coeff')
    MULTIPLICADOR = poly([0 2],'x','coeff')
    if(n == 0) then 
        P = T0
        return
    end
    
    if (n==1) then
        P = T1
        return
    end
    
    Ti_1 = T0
    Ti =  T1
    for i=2:n    
        Tk = (MULTIPLICADOR*Ti) - Ti_1
        Ti_1 = Ti
        Ti = Tk
    end

    P = Tk
endfunction

// Calculamos 

X_interpolacion = roots(Tn(4))

for i=1:4
    Y_interpolacion(i) = exp(X_interpolacion(i))
end

function e=Error(x)
    e=exp(x)-Lagrange(Y_interpolacion,X_interpolacion,x)
endfunction

//ploty(Error,-1,0.1,1)

//Ejercicio 11

function y = rootsChebyshev(n)//Calcula las raices del polinomio de Chebyshev de grado n
    for i=1:n
        y(i) = cos(((2*i)-1)*%pi/(2*n))
    end
endfunction

// Calcula los nodos de interpolacion por Chebyshev 
// para un intervalo general para reducir el error
function t = nodosInterpolacion(a,b,n)
    y = rootsChebyshev(n)
    disp(y)
    for i=1:n
        t(i) = ((a+b)+ y(i)*(b-a))/2
    end
endfunction

function pol = poliDD(Y,X)//Calcula el polinomio de interpolacion de Newton (chequear si anda bien)
    n = size(X,2)
    DD = DiferenciaDividida(Y,X)//vector de diferencias divididas de newton
//    disp(DD)
    resultado = 0
    for i=n:-1:2
        p = poly([-X(i-1) 1],'x','coeff')
        resultado =  (resultado + DD(i))*p
    end
    pol = resultado + DD(1)
endfunction

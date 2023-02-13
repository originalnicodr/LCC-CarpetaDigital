//Ej1
//Metodo de Lagrange
//Lagrange: vector X, función f, un valor x -> P(x)
//Dado un conjunto de puntos, una función devuelve el valor a
//proximados de la función evaluada en el valor x
function y=Lagrange0(X,f,x)
    m=size(X,1)
    y=0;
    for i=1:m
        L=1;
        for j=1:m
            if j~=i then
                L=(x-X(j))/(X(i)-X(j))*L;
            end
        end
        y=y+L*f(X(i))
    end
endfunction

function y=Lagrange(Y,X,x)//Y:vector de imagenes, X: vector de x, x: donde evaluas
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
 
 
function y=DDNewton0(X,f,x)
     m=size(X,2);
     y=DiferenciaDividida(X(1:m))//Dn
     for i=m-1:-1:1//arrancala iteracion bien, fijarse la primera iteracion
         y=DiferenciaDividida(X(1:i))+(x-X(i))*y
     end
endfunction

function y=DDNewton(Y,X,x)//Y:vector de imagenes, X: vector de x, x: donde evaluas
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
 
function Y=DiferenciaDividida(Y,X)//funcion y vector de puntos
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



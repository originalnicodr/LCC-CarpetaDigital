function [L,U,P]=Gauss(A)//Gauss con pivoteo parcial (cambio en la diagonal el maximo de la columna)
    m=size(A,1)
    U=A
    L=eye(m,m)//suponemos que A es cuadrada
    P=eye(m,m)
    
    for k=1 : m-1
        a=k
        
        for i=k : m
            if abs(U(i,k))>abs(U(a,k)) then //busca cual es el elemento de la columna mas grande
                a=i 
            end
        end
        //cambiaso de filas No cambias la fila entera? solo desde la k? por que?
        temp=U(k,k:m)//Fila k a partir del elemento (k,k)
        U(k,k:m)=U(a,k:m)
        U(a,k:m)=temp
        
        if k==1 then//en lugar de negarlo usamos la parte de else
        else//No existe L(1,0)
            temp=L(k,1:k-1)
            L(k,1:k-1)=L(a,1:k-1)
            L(a,1:k-1)=temp
        end
        temp=P(k,:)
        P(k,:)=P(a,:)
        P(a,:)=temp
        
        for j=k+1 : m
            L(j,k)=U(j,k)/U(k,k)//termio de formar L con mik=aik(i)/akk(k)
            U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)
        end
    end
endfunction

function [L,U,P]=Gauss2(A)//Gauss con pivoteo parcial (cambio en la diagonal el maximo de la columna) //Gauss2 ignora el paso si el resto de la columna es 0
    m=size(A,1)
    U=A
    L=eye(m,m)//suponemos que A es cuadrada
    P=eye(m,m)
    
    for k=1 : m-1
        a=k
        
        for i=k : m
            if abs(U(i,k))>abs(U(a,k)) then //busca cual es el elemento de la columna mas grande
                a=i 
            end
        end
        //cambiaso de filas No cambias la fila entera? solo desde la k? por que?
        temp=U(k,k:m)//Fila k a partir del elemento (k,k)
        U(k,k:m)=U(a,k:m)
        U(a,k:m)=temp
        
        if k==1 then//en lugar de negarlo usamos la parte de else
        else//No existe L(1,0)
            temp=L(k,1:k-1)
            L(k,1:k-1)=L(a,1:k-1)
            L(a,1:k-1)=temp
        end
        temp=P(k,:)
        P(k,:)=P(a,:)
        P(a,:)=temp
        
        if U(k,k)~=0 then
            for j=k+1 : m
                L(j,k)=U(j,k)/U(k,k)//termio de formar L con mik=aik(i)/akk(k)
                U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)
            end
        end
    end
endfunction

function [L,U]=GaussSinPiv(A)//Gauss sin pivoteo (chear que ande)//USAR LA 2, NO USAR ESTA
    m=size(A,1)
    U=A
    L=eye(m,m)//suponemos que A es cuadrada
    
    for k=1 : m-1
        if U(k,k)~=0 then//esto es lo que no esta en la funcion 2
            for j=k+1 : m
                L(j,k)=U(j,k)/U(k,k)//termio de formar L con mik=aik(i)/akk(k)
                U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)
            end
        end
    end
endfunction

//SI A ES NO SINGULAR ESTRICTAMENTE DIAGONAL DOMINANTE(funcion en practica 5) ENTONCES SE PUEDE HACER ELIM DE GAUSS SIN PIVOTEO
function [L,U]=GaussSinPiv2(A)//Gauss sin pivoteo, sin saltear si divide por cero (si se rompe tenemos que usar pivoteo)
    m=size(A,1)
    U=A
    L=eye(m,m)//suponemos que A es cuadrada
    
    for k=1 : m-1
        for j=k+1 : m
            L(j,k)=U(j,k)/U(k,k)//termio de formar L con mik=aik(i)/akk(k)
            U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)
        end
    end
endfunction

A=[2 1 1 0; 4 3 3 1; 8 7 9 5; 6 7 9 8]
B = [1 0 3 4; 5 0 1 3; 6 0 1 2; 0 0 1 2]

function x=SustLow(A,b)//Resolucion de sistema de forma sustitucion hacia abajo: Ly=(Pb)=b'
    [L,U,P]=Gauss(A)
    m=size(A,1)
    r=P*b
    x=zeros(m,1);
    y=zeros(m,1)
    y(1,1)=r(1,1)/L(1,1)
    for i=2 : m//L*y=P*b// planteo producto y vas despejando y
        y(i,1)=r(i,1)/L(i,i)
       for j=1 : i-1
           y(i,1)=y(i,1)-L(i,j)*y(j,1)/L(i,i)//lo estaria dividiendo por 1?
           end
    end
    
    x(m,1)=y(m,1)/U(m,m)
    for i=m-1:-1:1//U*x=y //planteo producto y despejo x, e itero de abajo hacia arriba por que U es triang superior
        x(i,1)=y(i,1)/U(i,i)
       for j=i+1:m
           x(i,1)=x(i,1)-U(i,j)*x(j,1)/U(i,i)
           end
    end
endfunction

//A_=[1 1 0 3; 2 1 -1 1; 3 -1 -1 2; -1 2 3 -1]
//b_=[4;1;-3;4]

function s1 = sustHaciaArriba(U, b)//fausto-fede //OJO NO FUNCAN EN SCILAB 6?
    n = size(U,1)
    x = 0
    for i = n:-1:1
        x(i) = (b(i) - U(i,i+1:n)*x(i+1:n)) / U(i,i)
    end
    s1 = x
endfunction

function s2 = sustHaciaAbajo(L,y)
    n = size(L,1)
    x = 0
    for i = 1:n
        x(i) = (y(i) - L(i,1:i-1)*x(1:i-1)) / L(i,i)
    end
    for i=1: n
        if abs(x(i))< 1e-5 then x(i)=0
        end
    end
    s2 = x
endfunction

function [L,U,P,c]=GaussTri(A)//Gauss con pivoteo dosbanda //c?
    m=size(A,1)
    U=A
    L=eye(m,m)//suponemos que A es cuadrada
    P=eye(m,m)
    
    for k=1 : m-1
        
        
        if abs(U(k,k))>abs(U(k+1,k)) then
            a=k 
        else
            a=k+1
        end

        temp=U(k,k:m)
        U(k,k:m)=U(a,k:m)
        U(a,k:m)=temp
        if k==1 then
        else
            temp=L(k,1:k-1)
            L(k,1:k-1)=L(a,1:k-1)
            L(a,1:k-1)=temp
            end
        temp=P(k,:)
        P(k,:)=P(a,:)
        P(a,:)=temp
        
        for j=k+1 : m
            L(j,k)=U(j,k)/U(k,k)
            U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)
        end
    end
endfunction

function [L,U,P]=GaussBanda(A,n)//Gauss con pivoteo banda general (chequear que ande)//c?
    m=size(A,1)
    U=A
    L=eye(m,m)//suponemos que A es cuadrada
    P=eye(m,m)
    
    for k=1 : m-1
        a=k
        for i=1:n-1
            if k+i>m-1 then
                break
            end
            if abs(U(k,k))<abs(U(k+i,k)) then
                a=k+i-1
            end
        end
        temp=U(k,k:m)
        U(k,k:m)=U(a,k:m)
        U(a,k:m)=temp
        if k==1 then
        else
            temp=L(k,1:k-1)
            L(k,1:k-1)=L(a,1:k-1)
            L(a,1:k-1)=temp
            end
        temp=P(k,:)
        P(k,:)=P(a,:)
        P(a,:)=temp
        
        if U(k,k)~=0 then
            for j=k+1 : m
                L(j,k)=U(j,k)/U(k,k)//termio de formar L con mik=aik(i)/akk(k)
                U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)
            end
        end
    end
endfunction

A_TRI = [1 2 0 0; 4 3 2 0; 0 2 3 4; 0 0 1 3]

function U=Gaussnormal(A)//Gaus normal sin pivoteo parcial
    U(1,:)=A(1,:)/A(1,1)
    for i=2:size(A,1)
        A(i,:)=A(i,:)-U(i-1,:)*A(i,i-1)
        U(i,:)=A(i,:)/A(i,i)//si divide por cero significa que requiere pivoteo
    end
    
endfunction


C=[1 1 0 3; 2 1 -1 1; 3 -1 -1 2; -1 2 3 -1]


function [L,U] = doolittle (A) //factorizacion LU de Doolittle
//Reservar espacio para las matrices L y U
//Empezando con ceros hay sitios que ya no tendremos que tocar
  L = zeros(size(A));
  U = zeros(size(A));
  [nRows, nColumns] = size(A);
  
  for j=1:nColumns
    for i=1:nRows
   //Estamos por encima de la diagonal, hallamos elemento de U
     if i<=j
       U(i,j) = A(i,j);
       for k=1:i-1
         U(i,j) = U(i,j) - L(i,k)*U(k,j);
       end
     end    
     //Estamos por debajo de la diagonal, hallamos elemento de L
     if j<=i
       L(i,j) = A(i,j);
       for k=1:j-1
         L(i,j) = L(i,j) - L(i,k)*U(k,j);
       end
       L(i,j) = L(i,j)/U(j,j);
     end
   end
 end
endfunction

function [P,R] = pivoteoMatriz(A)
    P = eye(A)
    [n,m] = size(A)
    R = A
    for k=1 : m-1
        a=k
        for i=k : m //Selección del elemento |Uik| máximo
            if abs(R(i,k))>abs(R(a,k)) then 
                a=i 
            end
        end

        // Permuto las filas de A
        temp=R(k,k:m)
        R(k,k:m)=R(a,k:m)
        R(a,k:m)=temp

        //Permutamos las filas de P
        temp=P(k,:)
        P(k,:)=P(a,:)
        P(a,:)=temp
    end
endfunction

A_2 = [1 -1 2 -1; 2 -2 3 -3; 1 1 1 0; 1 -1 4 3]

function x=Sustdoo(A,b)//Resolucion de sistema sin pivoteo. Usa doolittle pero se podria ingresar la L y la U directamente
    //Basicamente lo mismo que SustLow pero sin pivoteo
    [L,U]=doolittle(A)
    m=size(A,1)
    //r=P*b
    x=zeros(m,1);
    y=zeros(m,1)
    y(1,1)=b(1,1)/L(1,1)
    for i=2 : m
        y(i,1)=b(i,1)/L(i,i)
       for j=1 : i-1
           y(i,1)=y(i,1)-L(i,j)*y(j,1)/L(i,i)
           end
    end
    
    x(m,1)=y(m,1)/U(m,m)
    for i=m-1:-1:1
        x(i,1)=y(i,1)/U(i,i)
       for j=i+1:m
           x(i,1)=x(i,1)-U(i,j)*x(j,1)/U(i,i)
           end
    end
endfunction

function U= cholesky(A)//HIP TIENE QUE SER DEF POSITIVAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    
    [n,m] = size(A) //n filas, m columnas
    U = eye(A)
     for i=1:n  // Recorremos las filas
       for j=i:n
           if i==j then // Caso diagonal
              term_diag = 0
              if i == 1 then // Caso a11
                  U(i,i) = (A(i,i)**(1/2))
              else // Demas
                for k=1:i-1//acumulo lo que voy a estar restando en la raiz
                    term_diag = term_diag + (U(k,i))**2
//                    disp(U,k,i)
                end
//                    disp(term_diag)
            U(i,i) = (A(i,i) - term_diag)**(1/2)
              end
           else     // Caso no diagonal
        termino = 0
        for k=1:j-1//lo que voy a estar restando
           termino = termino + (U(k,i)*U(k,j))
        end
//           disp(U,k,i)
        U(i,j)= (A(i,j)-termino)/U(i,i)
        end      
      end 
     end
endfunction

function Ainv = inversaCholesky(A)
    U = cholesky(A)//DEFINIDA POSITIVA
    n = size(A,1)
    I = eye(n,n)
    for i=1:n
        C(:,i) = sustHaciaAbajo(U',I(:,i))
    end
    for i=1:n
        Ainv(:,i) = sustHaciaArriba(U,C(:,i))
    end
endfunction

function [Q,R]=QR(A)//ES UNICA SI A TIENE COLUMNAS LI
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

//Existe una sol de minimos cuadrados unica <=> rango(A)=n, en cuyo caso x=(A'A)^(-1)*A'*b
//Si rang(A)=n => A'*A es no singular

function r = resuelveQR(A,b)
    [Q,R] = QR(A)
    bPrima = Q'*b
    r = sustHaciaArriba(R,bPrima)
endfunction


function y = resuelveSinF(A,b)//te resuelve la Ax=b, haciendote Ux=b'
    C = [A,b]
    [L,C] = GaussE(C)//El L no se usa
    [n,m] = size(C)
    for i=1:m-1
        Ares(:,i) = C(:,i)
    end
    b = C(:,m)
    y = sustHaciaArriba(Ares,b)
endfunction

function [L,U] = GaussE(A)//OJO, A AUMENTADA COMO [A b] //Vendria a ser el Gauss original sin pivoteo, usar la resuelveSinF
    [n,m]=size(A)
    L = eye(n,m)
    U = A
    for k=1:m-1
      if U(k,k) ~= 0 then
         for j=k+1 : n//Calculamos los terminos de L y U
            L(j,k)=U(j,k)/U(k,k)//Calculo la columna k de L
            U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)//Calculo las filas de U
         end
         else disp('saltee una operacion')
        end
    end
endfunction

//Definiciones equivalente para una matris simetrica diagonal positiva:
//x'*A*x>0 para todo x perteneciente a R^n, x!=0
//Todos los autovalores de A son positivos
//A=B'*B para alguna matriz B no singular
//Toda submatriz principal de A es def positiva

function DefinidaPositiva2(A)//hace lo de la M que dice fede //A tiene que ser simetrica tambien?
    M = (A+A')/2
    n = size(A,1)
    ConjuntoAutovalores = spec(M)
        for i=1:n
        if ~(isreal(ConjuntoAutovalores(i))) then
            disp("No es definida positiva tiene autovalor complejo");
            return;
            end
            if ConjuntoAutovalores(i) < 0 then
            disp("No es definida positiva tiene autovalor negativo");
            return;
            end
    end
    disp('Es definida positiva')
endfunction

// ----------------- ELIMINACION GAUSS SIN PIVOTEO -----------------
function [L,U,P]=GaussP(A)
    m=size(A,1)
    U=A
    L=eye(m,m)//suponemos que A es cuadrada
    P=eye(m,m)
    contador = 0
    for k=1 : m-1
        a=k
        for i=k : m //Selección del elemento |Uik| máximo
            if abs(U(i,k))>abs(U(a,k)) then 
                a=i 
            end
        end
        //Permutamos las filas de U
        temp=U(k,k:m)
        U(k,k:m)=U(a,k:m)
        U(a,k:m)=temp
        //Permutamos las filas de L
        if k~=1 then //No entramos en k=1 para no tener problemas de iteracion
            temp=L(k,1:k-1)
            L(k,1:k-1)=L(a,1:k-1)
            L(a,1:k-1)=temp
        end
        //Permutamos las filas de P
        temp=P(k,:)
        P(k,:)=P(a,:)
        P(a,:)=temp
        if U(k,k) ~= 0 then
            for j=k+1 : m //Calculamos los terminos de L y U
                L(j,k)=U(j,k)/U(k,k)//Calculo la columna k de L
                contador = contador + 1 
                U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)//Calculo las filas de U
                contador = contador + (m-k)*2
            end
            else disp('saltee una operacion')
        end
    end
    disp(contador,'La cantidad de operaciones que se realizaron fue: ')
endfunction

function Ainv = inversaPorGauss(A)
    [L,U,P] = GaussP(A)
    n = size(A,1)
    I = eye(n,n)
    for i=1:n
        C(:,i) = sustHaciaAbajo(L,I(:,i))
    end

    for i=1:n
        Ainv(:,i) = sustHaciaArriba(U,C(:,i))
    end
    Ainv = Ainv*P
endfunction

//|x1-x2|/|x1|<=||A||*||A^(-1)||*||b1-b2||/||b1||
//k(A)=||A||*||A^(-1)||
//k(A)>=1

//Para n grande la eliminacion de gauss requiere aprox (2/3)*n^3 operaciones mientras que los metodos iterativos requieren del orden n^2






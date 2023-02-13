//Eliminación Guassiana
//GaussE: matriz A -> matriz B
function A =GaussE(A)
    m=size(A,1)
    for k=1:m
        A(k,:)=A(k,:)/A(k,k)
        for j=k+1:m
            A(j,:)=A(j,:)-A(k,:)*A(j,k)
        end
    end
endfunction

//Sustitución regresiva 
//SustR: Matris A -> vector x
function x=SustR(A,b)
    [m,n]=size(A)
    A=[A,b]
    x(m)=A(m,n+1)/A(m,m)
    for k=m-1:-1:1
        x(k)=(A(k,n+1)-A(k,k+1:m)*x(k+1:m))/A(k,k)
    end
endfunction

//Sustitución progresiva
//SusrtP: Matriz A -> vector x
function x=SustP(A,b)
    [m,n]=size(A)
    A=[A,b]
    //x(m)=A(1,n+1)/A(1,1)
    for k=1:m
        x(k)=(A(k,n+1)-A(k,1:k-1)*x(1:k-1))/A(k,k)
    end
endfunction

//Método de Gauss
//Gauss: Matris A, Vector b -> Vector x
//Resuelve un sistema de ecucaciones lineales mediante el método de Gauss
function x=Gauss(A,b)
    [m,n]=size(A)
    A=[A,b]
    x=zeros(m,1)
    //Eliminación progresiva de incognita
    A=GaussE(A)
    //Sustitución regresiva
    x=SustR(A(:,1:n),A(:,n+1))
endfunction

//Eliminación de Gauss con pivoteo parcial
//GaussP: matriz A -> Factorización LU con una matriz de premutaciones P
function [L,U,P]=GaussP(A)
    m=size(A,1)
    U=A
    L=eye(m,m)//suponemos que A es cuadrada
    P=eye(m,m)
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
        if k~=1 then //No entramos en k=1 para no tener problemas de identación
            temp=L(k,1:k-1)
            L(k,1:k-1)=L(a,1:k-1)
            L(a,1:k-1)=temp
        end
        //Permutamos las filas de P
        temp=P(k,:)
        P(k,:)=P(a,:)
        P(a,:)=temp
        
        for j=k+1 : m //Calculamos los terminos de L y U
            L(j,k)=U(j,k)/U(k,k)//Calculo la columna k de L
            U(j,k:m)=U(j,k:m)-L(j,k)*U(k,k:m)//Calculo las filas de U
        end
    end
endfunction

//Método de Gauss-Jordan
//Gauss-Jordan: Matris A, Vector b -> Vector x
//Resuelve un sistema de ecucaciones lineales mediante el método de Gauss-Jordan
function x=GaussJordan(A,b)
    [m,n]=size(A)
    A=[A,b]
    x=zeros(m,1)
    //Eliminación progresiva del método gaussiano
    A=GaussE(A)
    //Eliminación progresiva del método Gauss-Jordan
    for k=m:-1:1
        for j=k-1:-1:1
            A(j,:)=A(j,:)-A(k,:)*A(j,k)
        end
    end
    x=A(:,n+1)
endfunction


//Método Doolittle
//Doolittle: Matriz A -> Factorización LU
function [L,U]=Doolittle(A)
    L = zeros(size(A));
    U = zeros(size(A)); 
    [m,n] = size(A);
 
    for j=1:n//Iteración sobre columnas
        for i=1:m//Iteración sobre filas
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

//Factorización QR
//QR: Matriz A -> Matriz Q, Matriz R
function [Q,R]=QR(A)
    m=size(A,2)
    Q=zeros(m,m)
    R=zeros(m,m)
    for i=1:m
        term=0;
        for j=1:i-1
            term=term+((A(:,i)'*Q(:,j))*Q(:,j));
        end
        Q(:,i)=A(:,i)-term;
        //Ortonormalización
        Q(:,i)=Q(:,i)/sqrt((Q(:,i)'*Q(:,i)));
    end
    R=Q'*A;
endfunction

//Cholesky
//Cholesky: Matriz A ->  Matriz L
//Factorización A=L*L'
//A matriz simetrica y definida positiva
function L=Cholesky(A)
    m=size(A,1);
    L=zeros(m,m);
    for i=1:m 
        term=0
        for j=1:i
            term=0;
            for k=1:j-1
                term=term+L(i,k)*L(j,k);
            end
            if j~=i then
                L(i,j)=(A(i,j)-term)/L(j,j)
            end
        end
        L(i,i)=sqrt(A(i,i)-term)
    end
endfunction

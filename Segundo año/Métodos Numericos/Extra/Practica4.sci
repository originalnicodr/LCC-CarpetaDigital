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

function s1 = sustHaciaArriba(U, b)//fausto-fede
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

function [L,U,P,c]=GaussTri(A)//Gauss con pivoteo tribanda //c?
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

function U=GaussTriU(A)//Gaus normal sin pivoteo parcial
    U(1,:)=A(1,:)/A(1,1)
    for i=2:size(A,1)
        A(i,:)=A(i,:)-U(i-1,:)*A(i,i-1)
        U(i,:)=A(i,:)/A(i,i)
    end
    
endfunction


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


function x=Sustdoo(A,b)//Resolucion de sistema sin pivoteo. Usa doolittle pero se podria ingresar la L y la U directamente
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

function [U, UT] = cholesky(A)
    
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









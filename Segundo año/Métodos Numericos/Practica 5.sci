//x^(k+1)=N^(-1)*[(N-A)*x^(k)+b]
//Si ||I-N^(-1)*A||<1 entonces {x_n} converge a la solucion del sistema Ax=b para cualquier estimacion inicial x^(0)
function n=norma(a)
    n=(a'*a)**(1/2)
endfunction

function x=Gauss_Seidel(A,b)//podriamos meter como argumento el x inicial
    m=size(A,1)
    x=zeros(m,1)
    xaux=x
    while %T//Do while //paso
        xaux=x
        for i=1:m//calculo de x(i)
            term=0
            for j=1:m//calculo de termo para x(i)
                if i~=j then//termino que voy a restar
                    term=term+A(i,j)*x(j)
                end
            end
            x(i)=(1/A(i,i))*(b(i)-term)
        end
        //if norma(x-xaux)<10**(-6) then break; end
        //disp(x)
        if norm(x-xaux,'fro')<10**(-6) then break; end
    end
endfunction
//gauss seidel tarda la mitad de iteraciones

A_1 = [1 1 0 3; 2 1 -1 1; 3 -1 -1 2; -1 2 3 -1]
b_1 = [4; 1; -3; 4]

A_3=[10 1 2 3 4;
1 9 -1 2 -3;
2 -1 7 3 -5;
3 2 3 12 -1;
4 -3 -5 -1 15]
b_3=[12; -27; 14; -17; 12]


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


//w=1 gauss seidel
//0<w<1 metodo de sub-relajacion
//w>1 metodo de sobre-relajacion
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

//Forma matricial
//(D+w*L)*x^(k+1)=[(1-w)*D-w*U]*x^(k)+w*b

function [R, k] =Jacobi(A,b,t,x,iteraciones)//Si es diagonal dominante converge. / 
    n = size(A,2)
    X_k = x
    X_k1 = zeros(n,1)
    k = 0
    while k<iteraciones
        for i=1:n
            sumatoria = 0
            for j=1:n
                if i~=j then
                  sumatoria = sumatoria + A(i,j)*X_k(j)
                end
            end
            X_k1(i) = (b(i) - sumatoria)/A(i,i)
        end
        if norm((X_k - X_k1),'fro') < t then
          R = X_k1
            return R;
        end
        X_k = X_k1
        k = k+1;
    end
endfunction

function R =Jacobi2(A,b,t,x)//Si es diagonal dominante converge. //Habria que probarla
    n = size(A,2)
    X_k = x
    X_k1 = zeros(n,1)
    while %T
        for i=1:n
            sumatoria = 0
            for j=1:n
                if i~=j then
                  sumatoria = sumatoria + A(i,j)*X_k(j)
                end
            end
            X_k1(i) = (b(i) - sumatoria)/A(i,i)
        end
        if norm((X_k - X_k1),'fro') < t then
          R = X_k1
          return R;
        end
        X_k = X_k1
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

function y = spec_radius(A)
    y = max(abs(spec(A)))
endfunction

function enough_condition(A)//Condicion necesaria y suficiente de convergencia para jacobi y gauss seidel
    [nFil,nCol] = size(A)
    [L,D,U] = LDUMatrix(A)
    Nj = D
    Ng = L+D
    I = eye(A)
    if spec_radius(I-(inv(Nj)*A)) < 1 then//Usar la inversa esta mal, pero esta funcion no es para profes c:
        disp('La matriz cumple la condicion para JACOBI')
    end
    if spec_radius(I-(inv(Ng)*A)) < 1 then
        disp('La matriz cumple la condicion para Gauss-Seidel')
    end
endfunction

function r = DefinidaPositiva(A)
    M = (A+A')/2
    n = size(A,1)
    ConjuntoAutovalores = spec(M)
        for i=1:n
        if ~(isreal(ConjuntoAutovalores(i))) then
            disp("Tiene autovalor complejo");
            r = 0
            return;
            end
            if ConjuntoAutovalores(i) <= 0 then
            disp("Tiene autovalor negativo");
            r = 0
            return;
            end
    end
    r = 1
    return;
endfunction

function y = diag_dominante(A)//converge para jacobi si es diag dominante (la funcion se fija si es diag dominante, no estrictamente diag dominante, osea |aii|>sum(|aij|) )
    [nFil,nCol] = size(A)
    sumResto = 0
    y = 1
    for i=1:nFil
        for j=1:nCol
            if i ~= j then
                sumResto = sumResto + abs(A(i,j))
            end
        end
        if abs(A(i,i))< sumResto then
            y = 0
            return y
        end
    end
endfunction


//woptima es lo que habia hecho yo, usar la otra funcion
//------------------------------------------------------
function w=woptima(A)//si es definida positiva
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
//-----------------------------------------------------

//Wo optimo de fd

function [L, D, U] = LDUMatrix(A)//te la separa de forma tal que te queda L+D+U=A
    [nFil,nCol] = size(A)

    L = zeros(A)
    D = zeros(A)
    U = zeros(A)

    for i=1:nFil
        for j=1:nCol
            if i==j then
                D(i,i) = A(i,i)
            end
            if i>j then
                U(i,j) = A(i,j) 
            end
            if i<j then
                L(i,j) = A(i,j)
            end
         end
     end
endfunction

function w = eleccionW(A)//SI A ES DEFINIDA POSITIVA Y TRIDIAGONAL (P-banda con P=2)
 [L,D,U] = LDUMatrix(A)
  I = eye(D)
  Tj = I - inv(D)*A
  radio_espectral = spec_radius(Tj)*spec_radius(Tj)
  w = 2/(1+sqrt(1-radio_espectral))
endfunction

function convergenciasor(A,b,w)//Condicion necesaria y suficiente
    [L,D,U] = LDUMatrix(A)
    Tw=inv(D+w*L)*((1-w)*D-w*U)
    disp(spec_radius(Tw))
    if spec_radius(Tw)<1 then
        disp('El metodo SOR converge a la solucion Ax=b para todo x inicial')
    else
        disp('El metodo SOR NO converge a la solucion Ax=b para cualquier x inicial')
    end
endfunction

A=[4 3 0; 3 4 -1; 0 -1 4]
b=[24;30;-24]

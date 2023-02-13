//Método de Jacobi
//Jacobi: Matriz A, Vector b, error e -> Vector x
function x=Jacobi(A,b,e)
    m=size(A,1)
    x=zeros(m,1)
    while %T
        xaux=x
    for i=1:m
        //Calculo el termino que voy a restar (sumatoria)
        for j=1:m
            if j~=i then
                term=term+A(i,j)*xaux(j)
            end
        end
        x(i)=(b(i)-term)/A(i,i)
    end
    if norma(x-xaux)<e then break; end
    end
endfunction

//Método de Gauss-Seidel
//GaussSeidel: Matriz A, Vector b, error e -> Vector x
function x=GaussSeidel(A,b,e)
    m=size(A,1)
    x=zeros(m,1)
    while %T
        xaux=x
    for i=1:m
        //Calculo el termino que voy a restar (sumatoria)
        for j=1:m
            if j~=i then
                term=term+A(i,j)*x(j)
            end
        end
        x(i)=(b(i)-term)/A(i,i)
    end
    if norma(x-xaux)<e then break; end
    end
endfunction

//Método de sobrerelajación
//Sor: Matriz A, Vector b, factor de escala w,error e -> Vector x
//w=1 Método de Gauss-Seidel
//0<w<1 Método de Sub-Relajación
//w>1 Método de Sobre-Relajación
function x=Sor(A,b,w,e)
    m=size(A,1)
    x=zeros(m,1)
    while %T
        xaux=x
    for i=1:m
        //Calculo el termino que voy a restar (sumatoria)
        for j=1:m
            if j~=i then
                term=term+A(i,j)*x(j)
            end
        end
        x(i)=(1-w)*x(i)+w/A(i,i)*(b(i)-term);
    end
    if norma(x-xaux)<e then break; end
    end
endfunction

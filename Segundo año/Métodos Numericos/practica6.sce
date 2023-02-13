//1)a) autovalores: 1, 1, 1
//b)autovalores: 1.9949874 0.0050126 1
//c)autovalores: 1.9682458 0.0317542 1
//d)autovalores: 4.618034 2.381966 5
//e)autovalores: 0.7639320 3 5.236068
//f)autovcalores: 2.0646374 4.9616991 7.2236635  

//Ejercicio 1

// 

function r = calcular_Ri(A,i)
    resultado = 0
    n = size(A,1)
    for j=1:n
        if i~=j then
        resultado = resultado + abs(A(i,j))
        end
    end
    r = resultado
endfunction

function y = pertenece_Ci(A,i,z)
    ri = calcular_Ri(A,i)
    y = 0
    if abs(z-A(i,i)) <= ri then
        y = 1
    end
endfunction

function y = autovalor_en_Ci(A,lambda)
    n = size(A,1)
    y = 0
    for i=1:n
        ri = calcular_Ri(A,i)
        if abs(lambda-A(i,i)) <= ri then
            y = i
            //disp(i,'Pertenece al circulo:')
            return;
        end
    end
endfunction

function x = autovalores_Ci(A)
    n = size(A,1)
    lambda = spec(A)
    x = 0
    for i=1:n
        x(i) = autovalor_en_Ci(A, lambda(i))
        disp(x(i),'pertenece al circulo',lambda(i),'El autovalor')
    end
endfunction

//function y = dibujarGerschgorin()
//endfunction

A = [1 0 0; -1 0 1; -1 -1 2]
B = [1 0 0; -0.1 0 0.1; -0.1 -0.1 2]
C = [1 0 0; -0.25 0 0.25; -0.25 -0.25 2]
D = [4 -1 0; -1 4 -1; -1 -1 4]
E = [3 2 1; 2 3 0; 1 0 3]
F = [4.75 2.25 -0.25; 2.25 4.75 1.25; -0.25 1.25 4.75]



// Ejercicio 3
function A=Matrize(x)
    A=[1, -1, 0; -2, 4 ,-2; 0, -1, 1+x*0.1]
endfunction

p=poly(Matrize(10),'x')
disp(roots(p))

disp(spec(Matrize(10)))

//x=1

//    5.0102088  
//    1.0518401  
//    0.0379511  
// 
//    5.0102088  
//    0.0379511  
//    1.0518401  

//x=2

//    5.0208508  
//    1.1071946  
//    0.0719546  
// 
//    5.0208508  
//    0.0719546  
//    1.1071946  

//x=3

//    5.0319506  
//    1.1657664  
//    0.1022830  
// 
//    5.0319506  
//    0.1022830  
//    1.1657664  

//x=4

//    5.0435344  
//    1.2272145  
//    0.1292512  
// 
//    5.0435344  
//    0.1292512  
//    1.2272145  

//x=5

//    5.0556299  
//    1.2911771  
//    0.1531930  
// 
//    5.0556299  
//    0.1531930  
//    1.2911771  

//x=6

//    5.0682668  
//    1.3572923  
//    0.1744409  
// 
//    5.0682668  
//    0.1744409  
//    1.3572923

//x=7
//    5.0814764  
//    1.4252116  
//    0.1933120  
// 
//    5.0814764  
//    0.1933120  
//    1.4252116  

//x=8

//    5.0952921  
//    1.4946092  
//    0.2100986  
// 
//    5.0952921  
//    0.2100986  
//    1.4946092  

//x=9

//    5.1097493  
//    1.5651862  
//    0.2250644  
// 
//    5.1097493  
//    0.2250644  
//    1.5651862  

//x=10

//    5.1248854  
//    1.6366718  
//    0.2384428  
// 
//    5.1248854  
//    0.2384428  
//    1.6366718  

//Ejercicio 4

A_1 = [6 4 4 1; 4 6 1 4; 4 1 6 4; 1 4 4 6]
A_2 = [12 1 3 4; 1 -3 1 5; 3 1 6 -2; 4 5 -2 -1]
Z0 = [1;1;1;1]
// Metodo de las potencias.

function [v,l] = MetodoPotencias(A,z0,t)//Metodo de las Potencias, A matriz SIMETRICA, z0 aproximacion inicial del autovector, t la diferencia para tomar a z como autovector. Devuelve autovector y autovalor
    n = size(z0,2)
    // W inicial. 
    Wn = A*z0
    // W y Z iterados.
    Z_ant = z0
    Zi = Wn/norm(Wn,['inf'])

    // Iteramos.
    while %T
    //printf("en el while\n")
    Wn = A*Zi
    //disp(Wn)
    Z_ant = Zi
    //disp(Z_ant)
    Zi = Wn/norm(Wn,['inf'])
    //disp(Zi)
        // Condicion salida.
        if abs(Z_ant - Zi)<t then
            break
        end
    end
    
    // Buscamos el K no nulo.
    k = 1
    if norm(Z_ant,['inf']) == 0 then
        disp('Z_ant tiene todas sus entradas nulas.')
        return;
    end
    
    // Calculamos el autovalor.
    for i=1:n
        if Z_ant(i) ~= 0 then
           k = i
           break
        end
    end
    
    // Retornamos.
    l = Wn(k)/Z_ant(k)
    v = Zi
endfunction

function y=diferencia(A)
    y=norm(spec(A),['inf'])
    [v,l] = MetodoPotencias(A,ones(size(A,1),1),10**(-6))
    y=abs(y-l)
endfunction

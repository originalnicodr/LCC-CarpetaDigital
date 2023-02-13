function b = hornerLista(p,x)
    cantCoef = degree(p) +1
    b = 0
    for j= cantCoef-1:-1:0
        b = coeff(p, j)+ x*b
    end
endfunction

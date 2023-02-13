
function x= newtonJac(f1, f2, x0, tol)
    ea=100
    jacob = zeros(2,2)
    while abs(ea)>=tol 
        jacob(1,1) = 2*x0(1)+x0(2)**3
        jacob(1,2) = x0(1)*3*(x0(2)**2)
        jacob(2,1) = 6*x0(1)*x0(2)
        jacob(2,2) = 3*(x0(1)**2)-3*(x0(2)**2)
        vector=[f1(x0); f2(x0)]
        x=x0-(inv(jacob)*vector)
        ea=abs(x-x0) 
        x0=x
    end  
endfunction


deff('y=f1(x)','y=(x(1)**2)+x(1)*(x(2)**3)-9')
deff('y=f2(x)','y=3*(x(1)**2)*x(2)-4-(x(2)**3)')


xa=[1.2; 2.5]
xb=[-2; 2.5]
xc=[-1.2; -2.5]
xd=[2 ;-2.5]


x=newtonJac(f1, f2, xc, 0.01)

function y = raices(p)
	c = coeff(p,0)
	b = coeff(p,1)
	a = coeff(p,2)
	if b<0 
		y(1) = (2*c)/(-b+sqrt(b**2 - 4*a*c))
		y(2) = (-b + sqrt(b**2 - 4*a*c))/ (2*a)
	else
		y(1) = (-b - sqrt(b**2 - 4*a*c))/ (2*a)
		y(2) = (2*c)/(-b-sqrt(b**2 - 4*a*c))
	end
endfunction

poli = poly([2 3],"x","r")

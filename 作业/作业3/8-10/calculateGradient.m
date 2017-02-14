function  G = calculateGradient(u,v)

G(1,1) = exp(u) + v*exp(u*v) + 2*u -2*v -3;
G(2,1) = 2*exp(2*v) + u*exp(u*v) - 2*u +4*v -2;

end
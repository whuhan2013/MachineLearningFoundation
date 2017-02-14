function E = calculateE(u,v)

E = exp(u) + exp(2*v) + exp(u*v) + u^2 - 2*u*v + 2*v^2 - 3*u - 2*v;

end
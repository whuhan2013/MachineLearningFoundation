function H = calculateHessian(u,v)

H(1,1) = exp(u) + v*v*exp(u*v) + 2;
H(1,2) = exp(u*v) + u*v*exp(u*v) - 2;
H(2,1) = H(1,2);
H(2,2) = 4*exp(2*v) + u*u*exp(u*v) + 4;

end
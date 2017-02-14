function N = NewtonDerection(u,v)

H = calculateHessian(u,v);
H2 = inv(H)
N = H2 * calculateGradient(u,v)

end
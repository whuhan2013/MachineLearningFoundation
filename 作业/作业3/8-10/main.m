clc;
u = 0;
v = 0;
for i = 1:5,
    N = NewtonDerection(u,v);
    u = u - N(1,1)
    v = v - N(2,1)
    calculateE(u,v)
end
function S = sign(x)  %º∆À„sign
[m,n] = size(x);
for i = 1:m,
    for j = 1:n;

        if x(i,j) <= 0,
            S = 1;
        else
            S = -1;
        end
    end
end
end
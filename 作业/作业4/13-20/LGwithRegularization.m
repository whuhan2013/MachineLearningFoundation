function Wreg = LGwithRegularization(X,y,lambda)
[m,n] = size(X);
Wreg = inv(X' * X + lambda * eye(n)) * X' * y;%正则化的线性回归求解
end
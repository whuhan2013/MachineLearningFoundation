function Wreg = LGwithRegularization(X,y,lambda)
[m,n] = size(X);
Wreg = inv(X' * X + lambda * eye(n)) * X' * y;%���򻯵����Իع����
end
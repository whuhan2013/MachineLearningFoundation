function E = Error01(X,y,Wreg)
[m,n] = size(X);
E = 1 - sum(sign(X * Wreg) == y) / m;%¼ÆËã´íÎóÂÊ
end
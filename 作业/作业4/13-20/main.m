clc
trainingData = load('trainingData.txt');
Xtrain = trainingData(:, [1, 2]); ytrain = trainingData(:, 3);
testData = load('testData.txt');
Xtest = testData(:,[1,2]);ytest = testData(:,3);
[m,n] = size(Xtrain);
Xtrain = [ones(m,1), Xtrain];
[a,b] = size(Xtest);
Xtest = [ones(a,1), Xtest];

%13-15
%lambda = 10^-3;
%Wreg = LGwithRegularization(Xtrain,ytrain,lambda);
%Ein = Error01(Xtrain,ytrain,Wreg)
%Eout = Error01(Xtest,ytest,Wreg)

%16-17
%lambda = 10^-3;
%Wreg = LGwithRegularization(Xtrain(1:120,:),ytrain(1:120,:),lambda);
%Etrain = Error01(Xtrain(1:120,:),ytrain(1:120,:),Wreg)
%Eval = Error01(Xtrain(121:200,:),ytrain(121:200,:),Wreg)
%Eout = Error01(Xtest,ytest,Wreg)

%18
%lambda = 10^0;
%Wreg = LGwithRegularization(Xtrain,ytrain,lambda);
%Ein = Error01(Xtrain,ytrain,Wreg)
%Eout = Error01(Xtest,ytest,Wreg)

%19
%lambda = 10^-6
%Ecv = 0;
%v = 5;
%per = m / v;
%for i = 1:v,
%    Xtemp = Xtrain;
%    ytemp = ytrain;
%    Xtemp(1+(i-1)*per:i*per,:) = [];%出去用于求交叉验证的样本
%    ytemp(1+(i-1)*per:i*per,:) = [];
%    Wreg = LGwithRegularization(Xtemp,ytemp,lambda);
%    Error01(Xtrain(1+(i-1)*per:i*per,:),ytrain(1+(i-1)*per:i*per,:),Wreg)%利用交叉验证的样本求Ecv
%    Ecv = Ecv + Error01(Xtrain(1+(i-1)*per:i*per,:),ytrain(1+(i-1)*per:i*per,:),Wreg);
%end
%Ecv = Ecv / v

%20
%lambda = 10^-8;
%Wreg = LGwithRegularization(Xtrain,ytrain,lambda);
%Ein = Error01(Xtrain,ytrain,Wreg)
%Eout = Error01(Xtest,ytest,Wreg)








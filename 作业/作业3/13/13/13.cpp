
#include "stdafx.h"
#include<iostream>
#include<Eigen/Eigen>//C++下的一个常用的矩阵运算库
using namespace Eigen;
using namespace std;

#define X1min  -1 //定义第一维度的最大最小值
#define X1max  1
#define X2min  -1//定义第二维度的最大最小值
#define X2max 1
#define N 1000//定义样本数


int sign(double x){
	if(x <= 0)return -1;
	else return 1;
}

void getRandData(Matrix<double,N,3> &X,Matrix<double,N,1> &y){ //在（X1min,X1max）x（X2min,X2max）区间初始化点
	for(int i = 0; i < N; i++){
		X(i,0) = 1.0;
		X(i,1) = double(X1max - X1min) * rand()/RAND_MAX - (X1max - X1min)/2.0;
		X(i,2) = double(X2max - X2min) * rand()/RAND_MAX - (X2max - X2min)/2.0;
		y(i,0) = sign(X(i,1)*X(i,1) + X(i,2)*X(i,2) - 0.6);
	}
}

void getNoise(Matrix<double,N,3> &X,Matrix<double,N,1> &y){//加入噪声
	for(int i =0; i < N; i++)
		if(rand()/RAND_MAX < 0.1)
			y(i,0) = - y(i,0);
}

void linearRegression(Matrix<double,N,3> &X,Matrix<double,N,1> &y,Matrix<double,3,1> &weight){//逻辑回归计算，得参数weight
	weight = (X.transpose() *X).inverse() * X.transpose() * y;
}

double calcuE_in(Matrix<double,N,3> &X,Matrix<double,N,1> &y,Matrix<double,3,1> &weight){//计算E_in
	double E_in = 0.0;
	Matrix<double,N,1> temp = X * weight;
	for(int i = 0; i < N; i++)
		if((double)sign(temp(i,0)) != y(i,0))
			E_in++;
	return double(E_in/N);
}


void main(){
	int seed[1000];//种子
	double total_Ein = 0.0;
	Matrix<double,N,3> X;//X组成的矩阵
	Matrix<double,N,1> y;//y组成的向量
	Matrix<double,3,1> weight;//参数weight

	for(int i = 0; i < N; i++)//进行1000次，每次需要一个种子，所以先利用rand初始化种子
		seed[i] = rand();
	for(int k =0; k < N; k++){
		srand(seed[k]);//每次取一个种子进行试验
		getRandData(X,y);//得到随机样本
		getNoise(X,y);//添加噪声
		linearRegression(X,y,weight);//线性回归计算参数weight
		total_Ein += calcuE_in(X,y,weight);//计算每次E_in错误和
	}
	cout<<"Average E_in:"<<total_Ein / 1000.0<<endl;

}
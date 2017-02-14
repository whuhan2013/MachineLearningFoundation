// 14.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include "stdafx.h"
#include<iostream>
#include<Eigen/Eigen>//C++�µ�һ�����õľ��������
using namespace Eigen;
using namespace std;

#define X1min  -1 //�����һά�ȵ������Сֵ
#define X1max  1
#define X2min  -1//����ڶ�ά�ȵ������Сֵ
#define X2max 1
#define N 1000//����������


int sign(double x){

	if(x <= 0)return -1;
	else return 1;
}

void getRandData(Matrix<double,N,3> &X,Matrix<double,N,1> &y){ //�ڣ�X1min,X1max��x��X2min,X2max�������ʼ����
	for(int i = 0; i < N; i++){
		X(i,0) = 1.0;
		X(i,1) = double(X1max - X1min) * rand()/RAND_MAX - (X1max - X1min)/2.0;
		X(i,2) = double(X2max - X2min) * rand()/RAND_MAX - (X2max - X2min)/2.0;
		y(i,0) = sign(X(i,1)*X(i,1) + X(i,2)*X(i,2) - 0.6);
	}
}

void getNoise(Matrix<double,N,3> &X,Matrix<double,N,1> &y){//��������
	for(int i =0; i < N; i++)
		if(rand()/RAND_MAX < 0.1)
			y(i,0) = - y(i,0);
}

void transform(Matrix<double,N,3> &X,Matrix<double,N,6> &Z){//��X�ռ�ת��ΪZ�ռ�
	for(int i = 0; i < N; i++){
		Z(i,0) = 1;
		Z(i,1) = X(i,1);
		Z(i,2) = X(i,2);
		Z(i,3) = X(i,1) * X(i,2);
		Z(i,4) = X(i,1) * X(i,1);
		Z(i,5) = X(i,2) * X(i,2);
	}
}

void linearRegression(Matrix<double,N,6> &Z,Matrix<double,N,1> &y,Matrix<double,6,1> &weight){//�߼��ع���㣬�ò���weight
	weight = (Z.transpose() *Z).inverse() * Z.transpose() * y;
}

double calcuE(Matrix<double,N,6> &Z,Matrix<double,N,1> &y,Matrix<double,6,1> &weight){//����E_in
	double E_in = 0.0;
	Matrix<double,N,1> temp = Z * weight;
	for(int i = 0; i < N; i++)
		if((double)sign(temp(i,0)) != y(i,0))
			E_in++;
	return double(E_in/N);
}


void main(){
	int seed[1000];//����
	double total_Ein = 0.0;
	double total_Eout = 0.0;
	Matrix<double,N,3> X;//X��ɵľ���
	Matrix<double,N,3> Xtest;//��������
	Matrix<double,N,6> Z;//Z��ɾ���
	Matrix<double,N,6> Ztest;//��������
	Matrix<double,N,1> y;//y��ɵ�����
	Matrix<double,N,1> ytest;//��������
	Matrix<double,6,1> weight;//����weight
	Matrix<double,6,1> totalWeight;
	totalWeight<<0,0,0,0,0,0;

	for(int i = 0; i < N; i++)//����1000�Σ�ÿ����Ҫ1�����ӣ�����������rand��ʼ������
		seed[i] = rand();
	for(int k =0; k < N; k++){
		srand(seed[k]);//ÿ��ȡһ�����ӽ�������
		getRandData(X,y);//�õ��������
		getNoise(X,y);//�������
		getRandData(Xtest,ytest);
		getNoise(Xtest,ytest);
		transform(X,Z);
		transform(Xtest,Ztest);
		linearRegression(Z,y,weight);//���Իع�������weight
		total_Ein += calcuE(Z,y,weight);//����ÿ��E_in�����
		total_Eout += calcuE(Ztest,ytest,weight);
		totalWeight += weight;
		cout<<"k="<<k<<",Ein = "<<calcuE(Z,y,weight)<<",Eout = "<<calcuE(Ztest,ytest,weight)<<endl;
	}
	cout<<"Average E_in:"<<total_Ein / 1000.0<<endl;
	cout<<"Average E_out:"<<total_Eout / 1000.0<<endl;
	cout<<totalWeight/1000;
	

}
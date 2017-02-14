#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<math.h>
#include<Eigen/Eigen>

using namespace Eigen;
using namespace std;

#define Ntrain 200
#define Ntest 1000

double sign(double x){
	if(x <= 0) return -1;
	else return 1;
}

void getdata(fstream &trainingData,fstream &testData,Matrix<double,Ntrain,3> &Xtrain,Matrix<double,Ntrain,1> &ytrain,Matrix<double,Ntest,3> &Xtest,Matrix<double,Ntest,1> &ytest){
	if(!trainingData.eof()){
		for(int i = 0; i < Ntrain; i++){
			Xtrain(i,0) = 1;
			trainingData>>Xtrain(i,1)>>Xtrain(i,2)>>ytrain(i,0);
		}
	}
	trainingData.close();

	if(!testData.eof()){
		for(int i = 0; i < Ntest; i++){
			Xtest(i,0) = 1;
			testData>>Xtest(i,1)>>Xtest(i,2)>>ytest(i,0);
	    }
	}
	testData.close();
}

void LGwithRegularization(Matrix<double,Ntrain,3>  &Xtrain,Matrix<double,Ntrain,1> &ytrain,Matrix<double,3,1> &Wreg,double lambda){
	Matrix<double,3,3> I;
	I<<1.0,0,0,0,1.0,0,0,0,1.0;
	Wreg = (Xtrain.transpose() * Xtrain + lambda * I).inverse() * Xtrain.transpose() * ytrain;
}

double calculateEin(Matrix<double,Ntrain,3> &Xtrain,Matrix<double,Ntrain,1> &ytrain,Matrix<double,3,1> Wreg){
	double error = 0.0;
	Matrix<double,Ntrain,1> temp = Xtrain * Wreg;
	for(int i = 0; i < Ntrain; i++)
		if(sign(temp(i,0)) != ytrain(i,0))error++;
	return double(error / Ntrain);
}

double calculateEout(Matrix<double,Ntest,3> &Xtest,Matrix<double,Ntest,1> &ytest,Matrix<double,3,1> Wreg){
	double error = 0.0;
	Matrix<double,Ntest,1> temp = Xtest * Wreg;
	for(int i = 0; i < Ntest; i++)
		if(sign(temp(i,0)) != ytest(i,0))error++;
	return double(error / Ntest);
}




void main(){
	fstream trainingData("trainingData.txt");
	fstream testData("testData.txt");
	Matrix<double,Ntrain,3> Xtrain;
	Matrix<double,Ntrain,1> ytrain;
	Matrix<double,Ntest,3> Xtest;
	Matrix<double,Ntest,1> ytest;
	Matrix<double,3,1> Wreg;
	double lambda = pow(10.0,-3);
	getdata(trainingData,testData,Xtrain,ytrain,Xtest,ytest);
	LGwithRegularization(Xtrain,ytrain,Wreg,lambda);
	cout<<"Ein = "<<calculateEin(Xtrain,ytrain,Wreg)<<endl;
	cout<<"Eout = "<<calculateEout(Xtest,ytest,Wreg)<<endl;
}
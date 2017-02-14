#include<iostream>
#include<math.h>
using namespace std;

struct Point{
	double u;
	double v;
};

struct Gradient{
	double grad_U;
	double grad_V;
};

void gradient(Point p,Gradient &grad){
	grad.grad_U = exp(p.u) + p.v*exp(p.u*p.v) + 2*p.u - 2*p.v -3.0;
	grad.grad_V = 2*exp(2*p.v) + p.u*exp(p.u*p.v) - 2*p.u + 4*p.v - 2.0;
}

void updateGrad(Point &p,Gradient grad,double ita){
	p.u -= ita * grad.grad_U;
	p.v -= ita * grad.grad_V;
}

double calculateE(Point p){
	return exp(p.u) + exp(2*p.v) + exp(p.u*p.v) + p.u*p.u - 2*p.u*p.v + 2*p.v*p.v - 3*p.u - 2*p.v;
}


void main(){
	Point p = {0,0};
	Gradient grad = {0,0};
	double ita = 0.01;
	gradient(p,grad);
	cout<<"gradient at (0,0) is : ("<<grad.grad_U<<","<<grad.grad_V<<")"<<endl;
	
	int i;
	for(i = 0; i < 5; i++){
		gradient(p,grad);
		updateGrad(p,grad,ita);
		cout<<"第"<<i+1<<"次迭代，梯度为：("<<grad.grad_U<<","<<grad.grad_V<<");更新后坐标为：("<<p.u<<","<<p.v<<");更新后E的值为："<<calculateE(p)<<endl;
	}

	
}
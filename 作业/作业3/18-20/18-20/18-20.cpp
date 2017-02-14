#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

#define DEMENSION 20//����ά��

struct Record{  //���ݸ�ʽ
	double x[DEMENSION+1];
	int y;
};

struct Weight{  //������ʽ
	double w[DEMENSION+1];
};

int sign(double x){  //sign
	if(x > 0)return 1;
	else return -1;
}

void getData(fstream &datafile,vector<Record> &data){  //��ȡ����
	while(!datafile.eof()){
		Record temp;
		temp.x[0] = 1;
		for(int i = 1; i <= DEMENSION; i++)
			datafile>>temp.x[i];
		datafile>>temp.y;
		data.push_back(temp);
	}
	datafile.close();
}

double sigmoid(double x){  //sigmoid�������߼�������s�κ���
	return 1.0 / (1.0 + exp(-x));
}

double vectorMul(double *a,double *b,int demension){ //����������˷����ڻ�
	double temp = 0.0;
	for(int i = 0; i <demension; i++)
		temp += a[i] * b[i];
	return temp;
}

void calcuBatchGradient(vector<Record> &data,Weight weight,int N,double *grad){  //�����ݶ��½���
	for(int i = 0; i < N; i++){
		double temp = sigmoid(-1 * vectorMul(weight.w,data[i].x,DEMENSION+1) * (double)data[i].y);
		for(int j = 0; j <= DEMENSION; j++)
			grad[j] += -1.0 * temp * data[i].x[j] * data[i].y; 
	}
	for(int i = 0; i <= DEMENSION; i++)
		grad[i] = grad[i] / N;
}

void calcuStochasticGradient(Record data,Weight weight,double *grad){  //����ݶ��½���
	double temp = sigmoid(-1 * vectorMul(weight.w,data.x,DEMENSION+1) * (double)data.y);
	for(int j = 0; j <= DEMENSION; j++)
		grad[j] += -1.0 * temp * data.x[j] * data.y;

}

void updateW(Weight &weight,double ita,double *grad){  //���õõ����ݶȸ��²���weight
	for(int i = 0; i <= DEMENSION; i++){
		weight.w[i] = weight.w[i] - (ita * grad[i]);
	}
}

double calcuLGError(vector<Record> &data,Weight weight,int N){ //�����߼��ع�Ĵ�����㷽���������
	double error = 0.0;
	for(int i = 0; i < N; i++){
		error += log(1 + exp(-data[i].y * vectorMul(weight.w,data[i].x,DEMENSION+1)));
	}
	return double(error / N);
}

void logisticRegression(vector<Record> &data,Weight &weight,int N,double ita,int iteration){  //�߼��ع�
    /*for(int i = 0; i < iteration; i++){     //����batch�ݶ��½��������߼��ع�
		double grad[DEMENSION+1] = {0.0};
		calcuBatchGradient(data,weight,N,grad);
		updateW(weight,ita,grad);
		cout<<"iter = "<<i<<",ѵ���������߼��ع����Ein = "<<calcuLGError(data,weight,N)<<endl;
	}*/
	int i = 0;   //����Stochastic�ݶ��½��������߼��ع�
	while(i < iteration){
		double grad[DEMENSION+1] = {0.0};
		calcuStochasticGradient(data[i%N],weight,grad);
		updateW(weight,ita,grad);
		cout<<"iter = "<<i<<",ѵ���������߼��ع����Ein = "<<calcuLGError(data,weight,N)<<endl;
		i++;
	}
}

double calcuError(vector<Record> &data,Weight weight,int N){  //�����߼��ع�����Ԫ���࣬����0/1����
	double error = 0.0;
	for(int i = 0; i < N; i++){
		if(sign(vectorMul(data[i].x,weight.w,DEMENSION+1)) != data[i].y)
			error++;
	}
	return double(error / N);
}

void main(){
	vector<Record> trainingData;  //ѵ������
	vector<Record> testData;      //��������
	fstream file1("trainingData.txt");//��ȡѵ����������
	fstream file2("testData.txt");//��ȡ������������
	if(file1.is_open() && file2.is_open()){
		getData(file1,trainingData);
		getData(file2,testData);
	}
	else{
		cout<<"can not open file!"<<endl;
		exit(1);
	}
	int train_N = trainingData.size();//ѵ����������
	int test_N = testData.size();//������������
	double ita = 0.001;//����ita
	int interation = 2000;//��������
	Weight weight;//�߼��ع����
	for(int i = 0; i <= DEMENSION; i++)//������ʼ��Ϊ0��ע�⣬����Ҫ��ȫΪ1����2000���ǵò�������ģ���Ϊ���Ž���0������Ҫ��õ����iteration�����ڼ���δ�����
		weight.w[i] = 1;
	logisticRegression(trainingData,weight,train_N,ita,interation);
	cout<<"ѵ��������0/1����Ein = "<<calcuError(trainingData,weight,train_N)<<endl;
    cout<<"����������0/1����Eout = "<<calcuError(testData,weight,test_N)<<endl;
}
#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define DEMENSION 5  //����ά��

//�����ṹ��
struct record{
	double x[DEMENSION];
	int y;
};

//��ȡ�ļ�����
void getData(fstream &datafile,vector<record> &dataset){
	while(!datafile.eof()){
		record curRecord;
		curRecord.x[0] = 1;
		int i;
		for(i=1 ; i<DEMENSION ; i++)datafile>>curRecord.x[i];
		datafile>>curRecord.y;
		dataset.push_back(curRecord);
	}
	datafile.close();
}

//����signֵ
int sign(double x){
	if(x <= 0)return -1;
	else return 1;
}

//�������������ڻ����ж��Ƿ���Ҫ����
double multiply(double *v1, double *v2){
	int i;
	double temp = 0.0;
	for(i = 0; i < DEMENSION; i++)temp += v1[i] * v2[i];
	return temp;
}

//�������أ���������v������num�Ļ������ڼ���y*x��yΪ+1��-1��xΪ������
void multiply(double *result,double *v,int num){
	int i;
	for(i = 0; i < DEMENSION; i++)result[i] =  num * v[i];
}

//�����������ĺͷ���result�У����ڼ���w(i+1)=w(i)+y*x
void add(double *result,double *v1,double *v2){
	int i;
	for(i = 0; i < DEMENSION; i++)result[i] = v1[i] + v2[i];
}

//���������
double getErrorRate(double *weight,vector<record> dataset){
	int n = dataset.size();
	double errorRate= 0.0;
	int i;
	for(i=0;i<n;i++)
		if(sign(multiply(weight,dataset[i].x)) != dataset[i].y)errorRate++;
	return errorRate/n;
}

//�ڴ�PLA�㷨
void pocketPLA(double *pocketWeights,double *weights,vector<record> trainingSet,int iteration){
	int index = 0;
	int iter= 1;
	int n = trainingSet.size();
	while(iter < iteration){
		if(sign(multiply(trainingSet[index].x,weights)) != trainingSet[index].y){
			double temp[DEMENSION];
			multiply(temp,trainingSet[index].x,trainingSet[index].y);
			int i;
			for(i=0;i<DEMENSION;i++)weights[i] += temp[i];
	    	if(getErrorRate(weights,trainingSet) < getErrorRate(pocketWeights,trainingSet)){
				int j;
				for(j = 0;j<DEMENSION;j++)pocketWeights[j] = weights[j]; 
			}
			iter++;
		}
		if(index == n-1)index = 0;
		else index++;
	}
}

void main(){
	vector<record> trainingSet;
	vector<record> testSet;
	fstream datafile1("training_data.txt");
	fstream datafile2("test_data.txt");
	if(datafile1.is_open()&&datafile2.is_open()){
		getData(datafile1,trainingSet);
		getData(datafile2,testSet);
	}
	else{
		cout<<"can not open file!"<<endl;
		exit(1);
	}
	double weights[DEMENSION],pocketWeights[DEMENSION];
	
	double ave_error = 0.0 ;
	int j;
	for(j = 0; j < 2000; j++ ){

		random_shuffle(trainingSet.begin(), trainingSet.end());

		int i;
		for(i=0;i<DEMENSION;i++){  //ע�⣬������Ҫ��ʼ������������ʼ��ֵ�����룬�����������
		    weights[i]=0.0;
		    pocketWeights[i]=0.0;
		}
		pocketPLA(pocketWeights,weights,trainingSet,50);
	    double trainingError = getErrorRate(pocketWeights,trainingSet);
   	    double testError = getErrorRate(pocketWeights,testSet);
		ave_error += testError;
		cout<<"��"<<j<<"��ʵ��---"<<"training error:"<<trainingError<<" test error:"<<testError<<endl;

	}
	cout<<"average error rate:"<<ave_error/2000<<endl;
}

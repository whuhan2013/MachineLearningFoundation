#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define DEMENSION 5

double weight[DEMENSION];//Ȩ��ֵ
int step = 0;//�޸Ĵ���
int totalStep = 0;
int n = 0;//ѵ��������
char *file = "training_data.txt";//��ȡ�ļ���

//�洢ѵ��������inputΪx��outputΪy
struct record{
	double input[DEMENSION];
	int output;
};

//�Ѽ�¼��������������Ǵ��ڽṹ�������ڣ��������Ը���ʵ��һ�������
vector<record> trainingSet;

//�����ݶ���ѵ������������
void getData(ifstream &datafile)
{
	while(!datafile.eof())
	{
		record curRecord;
		curRecord.input[0] = 1;
		int i;
		for(i = 1; i < DEMENSION; i++){
			datafile>>curRecord.input[i];
		}
		datafile>>curRecord.output;
		trainingSet.push_back(curRecord);
	}
	datafile.close();
	n = trainingSet.size(); 
}

//����signֵ
int sign(double x){
	if(x <= 0)return -1;
	else return 1;
}

//���������(ʵ��Ϊ�������)������������ڵ�һ�������ڣ����ڼ���w(i+1)=w(i)+y*x
void add(double *v1,double *v2,int demension){
	int i;
	for(i = 0;i < demension; i++)v1[i] += v2[i];
}

//��������ֵ���ֵ�������ж�w*x�Ƿ�С��0����С��0Ҫִ�������㷨
double multiply(double *v1,double *v2,int demension){
	double temp = 0.0;
	int i;
	for(i = 0; i < demension; i++)temp += v1[i] * v2[i];
	return temp;
}

//����ʵ��num�������˻�����result�У����ڼ���y*x
void multiply(double *result,double *v,int demension,double num){
	int i;
	for(i = 0; i < demension; i++)result[i] =  num * v[i];
}

void PLA()
{
	int correctNum = 0;//��ǰ������ȷ��������������n���������һȦ�����ʾȫ����ȷ���㷨����
	int index = 0;//��ǰ���ڼ���ڼ�������
	bool isFinished = 0;//�㷨�Ƿ�ȫ����ɵı�ʾ��=1��ʾ�㷨����
	while(!isFinished){
		if(trainingSet[index].output == sign(multiply(weight,trainingSet[index].input,DEMENSION)))correctNum++;//��ǰ�����޴�������ȷ������+1
		else{//����ִ�������㷨
			double temp[DEMENSION];
			multiply(temp,trainingSet[index].input,DEMENSION,trainingSet[index].output);//����y*x
			add(weight,temp,DEMENSION);//����w(i+1)=w(i)+y*x
			step++;//����һ����������������+1
			correctNum = 0;//���ڳ����ˣ�������ȷ��������0
			//cout<<"step"<<step<<":"<<endl<<"index="<<index<<" is wrong"<<endl;
		}
		if(index == n-1)index = 0;
		else index++;
		if(correctNum == n)isFinished = 1;
	}
}

void main()
{
	ifstream dataFile(file);
	if(dataFile.is_open()){
	  	 getData(dataFile);
	 }
	 else{
		 cout<<"�����ļ���ʧ�ܣ�"<<endl;
	  	 exit(1);
	 }
	int i;
	for(i = 0; i < 2000; i++)
	{
	  random_shuffle(trainingSet.begin(), trainingSet.end());
	  int j;
	  for(j = 0; j < DEMENSION; j++)weight[j] = 0.0;
	  PLA();
	  totalStep += step;
	  cout<<"��"<<i<<"�ε�����step:"<<step<<endl;
	  step = 0;
	}
	cout<<"average step:"<<totalStep/2000<<endl;
}
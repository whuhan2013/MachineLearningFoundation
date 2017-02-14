#include<iostream>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<math.h>
using namespace std;

#define DATASIZE 20 //����[-1,1]���ڵ����Ŀ

//ѵ�������ṹ��
struct record{
	double x;
	int y;
};

//hyphothesis�Ľṹ�壬sΪ+1��-1��theta��20����ָ���21������ȡֵ
struct hyphothesis{
	int s;
	double theta;
};

//sign����
int sign(double x){
	if(x <= 0)return -1;
	else return 1;
}

//�����[-1,1]������DATASIZE�����x���������Ӧ��y
void getRandData(vector<record> &trainingData){
	int i;
	for(i = 0; i < DATASIZE; i++){
		record temp;
		temp.x = 2.0 * rand() / double(RAND_MAX) - 1.0;
		temp.y = sign(temp.x);
		trainingData.push_back(temp);
	}
}

//�������������20%�ĵ��yֵ�����ŵߵ��������20%����ͨ����������õ�[0,1]��������С��0.2����Ϊ����������
void getNoise(vector<record> &trainingData){
	int i;
	for(i = 0; i < DATASIZE; i++){
		double randnum = rand() / double(RAND_MAX);
		if(randnum < 0.2)
			trainingData[i].y = -1 * trainingData[i].y;
	}
}

//�Լ�����ıȽϷ���������sort
bool myCompare( record &v1, record &v2){
	return v1.x < v2.x;
}

//��MAXSIZE = 20��������X������������ֱ�ӵ����Դ�sort�������������������Լ�����ıȽϷ�����C++������ʶrecord,��֪����ô�Ƚϣ�����Ҫ����mycompare��������
void sortTrainingData(vector<record> &trainingData){
	sort(trainingData.begin(),trainingData.end(),myCompare);
}

//�������뼯�Ϻ�ָ����hyphothesis�����Ӧ�Ĵ�����
double calculateError(vector<record> &trainingData,hyphothesis &h){
	int i;
	int error = 0;
	for(i = 0; i < DATASIZE; i++){
		int temp = h.s * sign(trainingData[i].x - h.theta);
		if(temp != trainingData[i].y)error++;
	}
	return error/double(DATASIZE);
}

//����S = 1 or -1,thetaȡֵ��21�У�����42��hyphothesis�����Ǽ����42������С��ΪE_in������¼��ʱ��С����Ͷ�Ӧ��hyphothesis
double E_in(vector<record> &trainingData,hyphothesis &bestH){
	hyphothesis temp;
	double min_errorRate = 1.0;
	int i;
	//s = 1ʱ
	for(i = 0; i < DATASIZE+1; i++){
		temp.s = 1;
		if(i == 0)temp.theta = trainingData[0].x -1.0;//thetaȡֵ��thetaС����С
		else if(i == DATASIZE) temp.theta = trainingData[DATASIZE - 1].x + 1.0;//thetaȡֵ������֮��
		else temp.theta = (trainingData[i-1].x + trainingData[i].x) / 2.0;//thetaȡֵ�������

		double errorRate = calculateError(trainingData,temp);//�����hyphothesis�Ĵ����С�������
		if(errorRate < min_errorRate){
			bestH = temp;
			min_errorRate = errorRate;
		}
	}
	//s = -1ʱ
	for(i = 0; i < DATASIZE+1; i++){
		temp.s = -1;
		if(i == 0)temp.theta = trainingData[0].x -1.0;
		else if(i == DATASIZE) temp.theta = trainingData[DATASIZE - 1].x + 1.0;
		else temp.theta = (trainingData[i-1].x + trainingData[i].x) / 2.0;

		double errorRate = calculateError(trainingData,temp);
		if(errorRate < min_errorRate){
			bestH = temp;
			min_errorRate = errorRate;
		}
	}
	return min_errorRate;
}

//����16��õ��Ĺ�ʽ����E_out��ע�⣬�����������ֵ��fabs,������abs
double E_out(hyphothesis &bestH){
	return 0.5 + 0.3 * double(bestH.s) * (double)(fabs(bestH.theta) - 1.0);
}

void main(){
	int i;
	double totalE_inRate = 0.0;
	double totalE_outRate = 0.0;

	int seed[5000];//����Ҫ����5000����ƽ��������Ҫ��5000�����������������
	int j;
	for( j = 0; j < 5000; j++){
		seed[j] = rand();	//��5000������ͨ��һ��ȡ���������
	}

	for(i = 0; i < 5000; i ++){
		srand(seed[i]);//ÿ��ȡһ�����ӣ���ôÿ�β�������������оͲ�һ����
	    vector<record> trainingData;
	    getRandData(trainingData);//�������ѵ������
	    getNoise(trainingData);//������
	    sortTrainingData(trainingData);//��������
		hyphothesis bestH = {0,0};
        double min_errorRate = E_in(trainingData,bestH);//��������hyphothesis����¼��С������
	    cout<<"mininum E_in:"<<min_errorRate<<endl;
		totalE_inRate += min_errorRate;
		totalE_outRate += E_out(bestH);
		cout<<"E_out:"<<E_out(bestH)<<endl;//������εõ�������hyphothesis��E_out
	}
	cout<<"average E_in:"<<totalE_inRate / 5000<<endl;//��ƽ��E_in
	cout<<"E_out:"<<totalE_outRate / 5000<<endl;//��ƽ��E_out
}
#include<iostream>
#include<fstream>
#include<vector>
#include<math.h>
#include<algorithm>
using namespace std;

#define DEMENSION 9 //����ά��

//���ݽṹ��
struct Record{
	double x[DEMENSION];
	int y;
};

//ȡ����ĳһά�ȵ�x�����ݵ�y��ɵĵ�ά�ȣ���Ϊ����ǰ��д���ǵ�ά��x�Ĵ����ʼ��㣬�����ά��ֻҪ�ֱ�ȡ��ÿ��ά�ȼ���Ϳ�����
struct SingleDemension{
	double x;
	int y;
};

//hyphothesis��ʽ
struct Hyphothesis{
	int s;
	double theta;
};

//���ļ��������ݵ�Record������
void getData(fstream &datafile,vector<Record> &data){
	while(!datafile.eof()){
		Record temp;
		int i;
		for(i = 0; i < DEMENSION; i++)
			datafile>>temp.x[i];
		datafile>>temp.y;
		data.push_back(temp);
	}
	datafile.close();
}

//sign
int sign(double x){
	if(x <= 0)return -1;
	else return 1;
}

//����ȽϷ�ʽ
bool myCompare( SingleDemension &v1, SingleDemension &v2){
	return v1.x < v2.x;
}

//������ĵ�ά��X�����ݽ������򣬱ȽϷ����������Լ������
void sortData(vector<SingleDemension> &data){
	sort(data.begin(),data.end(),myCompare);
}

//���뵥ά��X�����ݽ��м����������
double calculateError(vector<SingleDemension> &data,Hyphothesis &h,int n){
	int i;
	int error = 0;
	for(i = 0; i < n; i++){
		int temp = h.s * sign(data[i].x - h.theta);
		if(temp != data[i].y)error++;
	}
	return error/double(n);
}

//�ֱ��ÿ��ά�ȵ�ÿ��hyphothesis��������ʣ���¼��С�����ʺ�����hyphothesis���Լ����Ӧ��ά��
double E_in(vector<Record> &trainingData,Hyphothesis &bestH,int &bestDemension,int trainingDataSize){
	int i;
	double min_errorRate = 1.0;
	Hyphothesis temp = {0,0};
	for(i = 0; i < DEMENSION; i++){       //�ֱ��ÿ��ά�ȼ���         
		vector<SingleDemension> singleDemension;
		int j;
		for(j = 0; j < trainingDataSize; j++){   //ȡ����ά�ȵ�x��ȡ��y����γ��µĵ�ά��x����
			SingleDemension temp = {0,0};
			temp.x = trainingData[j].x[i];
			temp.y = trainingData[j].y;
			singleDemension.push_back(temp);
		}
		sort(singleDemension.begin(),singleDemension.end(),myCompare);//����

		//s = 1ʱ������ά������hyphothesis�Լ���Сerror����ʱthetaȡֵ�ڱ䣩
		for(j = 0; j < trainingDataSize+1; j++){ 
		    temp.s = 1;
		    if(j == 0)temp.theta = singleDemension[0].x -1.0;
		    else if(j == trainingDataSize) temp.theta = singleDemension[trainingDataSize - 1].x + 1.0;
		    else temp.theta = (singleDemension[j-1].x + singleDemension[j].x) / 2.0;

		    double errorRate = calculateError(singleDemension,temp,trainingDataSize);
			if(errorRate < min_errorRate){   //������hyphothesis�ȿڴ���ĸ����㣬��������ڴ����hyphothesis������¼��ʱȫ����С���󣬲���¼��ʱ��ά��
			    bestH = temp;
			    min_errorRate = errorRate;
				bestDemension = i+1;
			}
		}

		//s = -1ʱ������ά������hyohothesis�Լ�����error��thetaȡֵ�ڱ䣩
	    for(j = 0; j < trainingDataSize+1; j++){
		    temp.s = -1;
		    if(j == 0)temp.theta = singleDemension[0].x -1.0;
		    else if(j == trainingDataSize) temp.theta = singleDemension[trainingDataSize - 1].x + 1.0;
		    else temp.theta = (singleDemension[j-1].x + singleDemension[j].x) / 2.0;

		    double errorRate = calculateError(singleDemension,temp,trainingDataSize);
		    if(errorRate < min_errorRate){
			    bestH = temp;
			    min_errorRate = errorRate;
				bestDemension = i+1;
			}
		}

	}
	return min_errorRate;
}

//���ò�������testData,�Ѿ��õ�������hyphothesis�������ڵ�ά�ȼ����ά�ȵ�E_out
double E_out(vector<Record> testData,int bestDemension,Hyphothesis bestH,int testDataSize){
		int j;
		vector<SingleDemension> bestDemensionData;
		for(j = 0; j < testDataSize; j++){
			SingleDemension temp = {0,0};
			temp.x = testData[j].x[bestDemension-1];
			temp.y = testData[j].y;
			bestDemensionData.push_back(temp);
		}
		
		return calculateError(bestDemensionData,bestH,testDataSize);
}


void main(){
	vector<Record> trainingData;//ѵ����������
	vector<Record> testData;//������������
	fstream datafile1("training_data.txt");
	fstream datafile2("test_data.txt");
	if(datafile1.is_open() && datafile2.is_open()){
		getData(datafile1,trainingData);//��ȡѵ������
		getData(datafile2,testData);//��ȡ��������
	}
	else{
		cout<<"�ļ���ʧ�ܣ�"<<endl;
		exit(1);
	}
	int trainingDataSize = trainingData.size();//ѵ��������
	int testDataSize = testData.size();//����������
	Hyphothesis bestH = {0,0};//��¼ȫ������hyphothesis
	int bestDemension = 0;//��¼��Ӧ��ά��
	double Error_in = E_in(trainingData,bestH,bestDemension,trainingDataSize);//����ѵ����������E_in
	double Error_out = E_out(testData,bestDemension,bestH,testDataSize);//���ò�����������E_out
	cout<<"���ά��Ϊ��"<<bestDemension<<",   ��СE_inΪ��"<<Error_in<<",    ���Ӧ��E_outΪ��"<<Error_out<<endl;
}
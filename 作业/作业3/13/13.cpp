#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

#define N 1000
#define X1min -1
#define X1max 1
#define X2min -1
#define X2max 1

struct Record{
	double x[3];
	int y;
};

int sign(double x){
	if(x <= 0)return -1;
	else return 1;
}

void getRandomData(vector<Record> &data){
	Record temp;
	int i;
	for(i = 0; i < N; i++){
		temp.x[0] = 1.0;
		temp.x[1] = (X1max - X1min) * rand()/RAND_MAX - (X1max - X1min)/2.0;
	    temp.x[2] = (X2max - X2min) * rand()/RAND_MAX - (X2max - X2min)/2.0;
		temp.y = sign(temp.x[1]*temp.x[1] + temp.x[2]*temp.x[2] - 0.6);
		data.push_back(temp);
	}
}

void getNoise(vector<Record> &data){
	int i;
	for(i = 0; i < N; i++){
		if(rand()/RAND_MAX < 0.1)
			data[i].y = -data[i].y;
	}
}


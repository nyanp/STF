#include<iostream>
#include<map>
#include<sstream>
#include<string>
#include<fstream>
#include"Linear.h"

using namespace std;

class Gyro{
public:
	Gyro(const std::map<double,double>& table, 
		 const double& ad_data)
		 : li_(table), ad_data_(ad_data){}

	double value() const{
		return 1;
	}
private:
	const Linear<> li_;
	const double& ad_data_;
};

int main(void){
	double ad_data[128] = {0};

	std::map<double,double> table;
	table[0.0] = 0.2; table[2.0] = 0.4;
	table[4.0] = 0.5; table[5.0] = 0.6;

	ifstream ifs("input.txt");// 0 0.2\n‚Ý‚½‚¢‚ÈŒ`Ž®
	string s;
	double key,value;
	while(getline(ifs,s)){
		istringstream ss(s);
		ss >> key >> value;
		table[key] = value;
	}

	Gyro gyro(table, ad_data[3]);
	cout << gyro.value() << endl;

	ad_data[3] = 3.0;
	cout << gyro.value() << endl;
	
}
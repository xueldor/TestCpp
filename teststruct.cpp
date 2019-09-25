#include <iostream>
#include <string>
#include <cstring>

using namespace std;


struct inflatable{
	char name[20];
	float volume;
	double price;
};//�ֺ�

typedef struct inflatable2{
	std::string name;
	float volume;
	double price;
} inflatable2_s;//C����Ϊ��ʡ��struct�ؼ��ֻ�����д

//λ��
struct bitArea{
	bool first:1;//1bit
	char second: 2;
	unsigned third:8;
	int forth:20;
};

union fourInOne{
	int intVal;
	long longVal;
	double double_val;

};

enum spec{red,green,orange,blue = 100,grey};//grey��101

void testStru(){

	struct inflatable goose;//C���Բ���ʡ��struct
	inflatable hat;//C++����ʡ��struct�ؼ���
	strcpy(goose.name,"no");
	strcpy_s(hat.name,"oh");
	cout<<hat.name<<"  "<<hat.price<<endl;

	inflatable2_s bat;
	bat.name = "nik";

	inflatable pal = {
		"jam",1.2f//,50.656
	};
	cout<<pal.name<<"  "<<pal.volume<<"  "<<pal.price<<endl;

	bitArea testBit;
	testBit.first = (bool)0xF;
	cout<<testBit.first<<"  "<<sizeof(bitArea)<<"  "<<sizeof(testBit)<<endl;

	//test enum
	spec specA = green;
	cout<<specA<<endl;
	int aa = specA;//ö�ٿ���ת��int
	specA = (spec)2;//��֮��intת��ö�ٱ���ǿת
	cout<<specA<<"  "<<grey<<endl;

}


int main2(){
	testStru();

	return 0;
}
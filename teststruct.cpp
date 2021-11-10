#include <iostream>
#include <string>
#include <cstring>

using namespace std;


struct inflatable{
	char name[20];
	float volume;
	double price;
};//分号

typedef struct inflatable2{
	std::string name;
	float volume;
	double price;
} inflatable2;//C语言为了省略struct关键字会这样写

//位域
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

enum spec{red,green,orange,blue = 100,grey};//grey是101

void testStru(){

	struct inflatable goose;//C语言不能省略struct
	inflatable hat;//C++可以省略struct关键字
	strcpy(goose.name,"no");
	strcpy_s(hat.name,"oh");
	cout<<hat.name<<"  "<<hat.price<<endl;

	inflatable2 bat;
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
	int aa = specA;//枚举可以转成int
	specA = (spec)2;//反之，int转成枚举必须强转
	cout<<specA<<"  "<<grey<<endl;

}


int main2(){
	testStru();

	return 0;
}
#include <stdlib.h> 
#include <iostream>

//���õ���ƣ�Ӧ�÷ŵ�ͷ�ļ������ֻ����ʾ
class Time{
private :
	int hours;
	int minutes;

public:
	Time(int h,int m=0):hours(h),minutes(m){};

	//���Ч�ʱ��⿽�����󣬲���Ӧ������Ϊ&
	//���Ƿ���ֵ���������ã���Ϊsum��һ���ֲ�������
	Time addTime(const Time &time)const{//����const��ʾ��������Ӧ�øı������ֵ����Ӧ���޸����Ա
		Time sum(0);
		sum.minutes = minutes + time.minutes;
		sum.hours = hours + time.hours + sum.minutes /60;
		sum.minutes %= 60;
		return sum;
	}

	//�����������ʵ��`addTime` ����`operator+` �Ϳ�����
	Time operator+(const Time &time)const{
		return addTime(time);
	}

	void show()const{
		std::cout<<hours <<"h " <<minutes<<"m"<<std::endl;
	}
	/*
		����<<, ʵ��show()����ͬ���Ĺ��ܡ�
		���ֱ�����أ���ôʹ����������time<<cout, ����֡�ϣ������ cout<<time�� 
		�����ֲ����޸�iostream �ļ�����˱���ʹ�� ��Ԫ������
		����ֵ������ostream &�����ܽ�����ostream����Ϊ�������ostream���ᵼ��os���󿽱���
	*/
	friend std::ostream & operator<<(std::ostream & os, const Time & t)//����Ϊ��Ա�������ز�ͬ���ǳ�Ա������ʽ��һ���������������ߣ��ڶ���������������ұ�
	{//�����friend�ؼ��֣��������������1)����Time��ĳ�Ա�� 2) ȴ���Ա�����ķ���Ȩ����ͬ
		//ͨ���Ѻ�����д�����棬����Ҫ"Time::"���Ρ�
		os << t.hours << " hours, " << t.minutes << " minutes";
		return os;
	}

	//������Time * double �����Ĳ�����������Ҫ����*ʵ��Time * double֮�⣬��Ӧ��ͨ����Ԫ�ķ�ʽʵ��double * Time ��

	//���ص�Ŀ�����
	Time& operator ++();//ǰ����������أ���������������β�
	Time operator ++(int);//������������أ���������������βΣ���������β�û�ã�ֻ�Ǳ������á�
	//���ϣ�ǰ��++�Ƿ����������Է���������Time& �������Ƿ��صĲ�������������Time

};
//�Ѿ���������ʵ����
//std::ostream & operator<<(std::ostream & os, const Time & t)
//{
//	os << t.hours << " hours, " << t.minutes << " minutes";
//	return os;
//}

Time& Time::operator ++(){//ǰ��
	++minutes;
	if(minutes>=60){
		hours +=1;
		minutes -= 60;
	}
	return *this;
}
Time Time::operator ++(int){//����
	Time old = *this;//��������
	++*this;//����ǰ��++������
	return old;
}

int main12(){
	Time a(3,10);
	Time b(2,5);

	//���ַ����������������
	Time c = a.operator+(b);//����һ��tag 1

	Time d = a + b;//�����������a��ʾ���ö����ұ�b��ʾ����

	c.show();
	std::cout<<d<<std::endl;//������<<�������cout�ǵ�һ��������d�ǵڶ����������൱��operator<<(std::cout, d)
	//cout<<d,d��Time���ͣ�cout��ostream���ͣ�ostream����û��������ذ汾�����Բ����ܷ����"cout.operator<<()",����cout�ͳ��˵�һ��������
	operator<<(std::cout, d)<<std::endl;;//�Ƚ�һ�¸� tag 1 ������

	std::cout<<(c++)<<std::endl;
	std::cout<<(++d)<<std::endl;

	system("pause");
	return 0;
}
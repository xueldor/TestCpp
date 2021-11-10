//演示命名空间 头文件

//头文件中仅包含声明
namespace 张三{

	extern std::string name;
	void payed();
}

namespace 李四{

	extern std::string name;
	void payed();

	namespace 亲儿子{
		extern std::string name;
	}
}

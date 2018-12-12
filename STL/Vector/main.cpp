#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class MyClass {
private:
	string name;
public:
	MyClass(string name) {
		this->name = name;
		cout << "make " << this->name << endl;
	}
	~MyClass() {
		cout << "delete " << this->name << endl;
	}
	void func() {
		cout << "func " << this->name << endl;
	}
};

int main(){
	// new を使用したものをvectorに入れて解放忘れするとメモリリークが発生する
	{
		vector<MyClass*> *my_vector = new vector<MyClass*>();
		vector<MyClass*>::iterator itr;
		{
			MyClass* mc = new MyClass("1");
			my_vector->push_back(mc);
			// new したものなので、デストラクタよばれない
		}
		for(itr = my_vector->begin(); itr != my_vector->end(); itr++)
			(*itr)->func();
		delete my_vector;
	}
	// new を使用しない場合
	{
		vector<MyClass> my_vector;
		vector<MyClass>::iterator itr;
		{
			MyClass mc("2");
			my_vector.push_back(mc);
			// mcのスコープが外れるため、この時点でデストラクタよばれる
		}
		// push_backをした時点でディープコピーしているので利用できる
		for(itr = my_vector.begin(); itr != my_vector.end(); itr++)
			itr->func();
		// my_vectorのスコープが外れるため、もう1度デストラクタが呼ばれる
	}
	// c++0x のスマートポインタとの組み合わせ
	{
		vector<shared_ptr<MyClass>> my_vector;
		vector<shared_ptr<MyClass>>::iterator itr;
		{
			shared_ptr<MyClass> mc = make_shared<MyClass>("3");
			my_vector.push_back(mc);
			// new したものなので、デストラクタよばれない
		}
		for(itr = my_vector.begin(); itr != my_vector.end(); itr++)
			(*itr)->func();
		// new したものではあるが、スマートポインタを利用しているため
		// my_vector のスコープが外れるさいに、デストラクタが呼ばれる
	}
	return 0;
}

/*
$ ./Vector 
make 1
func 1
make 2
delete 2
func 2
delete 2
make 3
func 3
delete 3
*/

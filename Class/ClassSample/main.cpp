#include <iostream>
#include <string>

using namespace std;

class SampleClass {
private:
	string name;
public:
	SampleClass(const char* name) {
		string text = "コンストラクタ";
		cout << text << endl;
		this->name = name;
		return;
	}
	// 継承されることを考えるとデストラクタにはvirtualをつけるほうがよい
	virtual ~SampleClass() {
		string text = "デストラクタ";
		cout << text << endl;
		return;
	}
	void func() {
		cout << this->name << endl;
		return;
	}
};

int main(){
	SampleClass *sc;
	sc = new SampleClass("あいうえお");
	sc->func();
	delete sc;
	return 0;
}
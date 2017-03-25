#include <iostream>
#include <string>

using namespace std;


int main(){
	
	{
		string *x = new string("ヒープ領域");
		cout << *x << endl;
		delete x;
	}
	
	{
		string x("スタック領域");
		cout << x << endl;
	}
	
	return 0;
}

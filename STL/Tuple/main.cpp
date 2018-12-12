#include <stdio.h>
#include <tuple>

using namespace std;

int main(){
	
	tuple<int, char, const char*> cTuple;
	cTuple = make_tuple(100, 'A', "Hello");
	printf("[%d][%c][%s]\n", get<0>(cTuple), get<1>(cTuple), get<2>(cTuple));
	
	int iInt1 = 1000;
	double fDouble1 = 100.0;
	auto cTie = tie(iInt1, fDouble1);
	printf("[%d][%f]\n", get<0>(cTie), get<1>(cTie));
	
	int iInt2;
	double fDouble2;
	tie(iInt2, fDouble2) = cTie;
	printf("[%d][%f]\n", iInt2, fDouble2);
	
	return 0;
}

/*
$ ./Tuple 
[100][A][Hello]
[1000][100.000000]
[1000][100.000000]
*/
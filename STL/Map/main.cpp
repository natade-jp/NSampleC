#include <stdio.h>
#include <map>
#include <unordered_map>

using namespace std;

int showTreeMap(map<int, int> treemap){
	for(auto iterator = treemap.begin(); iterator != treemap.end(); iterator++) {
		auto key = iterator->first;
		auto value = iterator->second;
		printf("treemap[%d] = %d\n", key, value);
	}
	return 0;
}

int testTreeMap() {
	map<int, int> treemap;
	treemap[200] = 1;
	treemap[-1] = 2;
	treemap[0xFFFFFF] = 3;
	printf("1度目の表示\n");
	showTreeMap(treemap);
	treemap.erase(-1);
	printf("2度目の表示\n");
	showTreeMap(treemap);
	return 0;
}

int showHashMap(unordered_map<int, int> hashmap){
	for(auto iterator = hashmap.begin(); iterator != hashmap.end(); iterator++) {
		auto key = iterator->first;
		auto value = iterator->second;
		printf("hashmap[%d] = %d\n", key, value);
	}
	return 0;
}

int testHashMap() {
	unordered_map<int, int> hashmap;
	hashmap[200] = 1;
	hashmap[-1] = 2;
	hashmap[0xFFFFFF] = 3;
	printf("1度目の表示\n");
	showHashMap(hashmap);
	hashmap.erase(-1);
	printf("2度目の表示\n");
	showHashMap(hashmap);
	return 0;
}


int main(){
	
	printf("ツリーマップ(二分木)のテスト\n");
	testTreeMap();
	printf("ハッシュマップ(ハッシュテーブル)のテスト\n");
	testHashMap();
	
	return 0;
}

/*
$ ./Map
ツリーマップ(二分木)のテスト
1度目の表示
treemap[-1] = 2
treemap[200] = 1
treemap[16777215] = 3
2度目の表示
treemap[200] = 1
treemap[16777215] = 3
ハッシュマップ(ハッシュテーブル)のテスト
1度目の表示
hashmap[16777215] = 3
hashmap[-1] = 2
hashmap[200] = 1
2度目の表示
hashmap[16777215] = 3
hashmap[200] = 1
*/

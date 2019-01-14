/**
 * @file dsets.cpp
 * Represents each DisjointSets object
 * @author Zixin Zhang
 */
#include "dsets.h"


/*
	Creates n unconnected root nodes at the end of the vector
	Para: num The number of nodes to create
*/
void DisjointSets::addelements(int num){
	for(int i = 0; i < num; i++){
		s.push_back(-1);
	}
}

/*
	Find a representative element in DS
	Return: The index of the root of the up-tree
	PS: Compression is needed at line 25
*/
int DisjointSets::find(int elem){
	if(s[elem] < 0){
		return elem;
	}

	else {
		return (s[elem] = find(s[elem]));
	}
}
/*
	Implemented using union-by-size
	Should NOT assume the arguments to setunion are roots
*/
void DisjointSets::setunion(int a, int b){
	//Find root node of "a" and "b"
	int root_a = find(a);
	int root_b = find(b);

	if(root_a == root_b){
		return;
	}

	int newSize = s[root_a] + s[root_b];

	if(abs(s[root_a]) < abs(s[root_b])){
		s[root_a] = root_b;
		s[root_b] = newSize;
	}

	else {
		s[root_b] = root_a;
		s[root_a] = newSize;
	}
}

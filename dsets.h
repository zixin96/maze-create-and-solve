/**
 * @file dsets.h
 * Represents each DisjointSets object
 * @author Zixin Zhang
 */
#ifndef DSETS_H
#define DSETS_H

#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

class DisjointSets {
public:

	void addelements(int num);
	int find(int elem);
	void setunion(int a, int b);


private:
	vector<int> s;
};

#endif

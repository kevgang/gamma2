// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <string.h>
#include <random>
#include <time.h>
#include <algorithm>  
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stdio.h>
#include  <fstream>
#include<vector>
#define kgrand (double)rand()/RAND_MAX*100
#define NoC 10//number of cities 
#define pop_size 10
using namespace std;
class city {
public:
	double xcord;
	double ycord;
};
class policy {
public:
	double fitness;
	vector<int> order;
	void init();
	void mutate();
	void evaluate(vector<city> master);


};
void policy::init() {
	vector<int> unshuff;
	for (int j = 0; j < NoC; j++) {
		unshuff.push_back(j);
	}
	order = unshuff;
	for (int i = 0; i < 100 * NoC; i++) {
		mutate();
	}
	
}
void policy::mutate() {
	for (int n = 0; n < .1*NoC; n++) {
		int spot1 = order.at(rand() % order.size());
		int spot2 = order.at(rand() % order.size());
		int citytemp = order.at(spot1);
		order.at(spot1) = order.at(spot2);
		order.at(spot2) = citytemp;
	}
}
void policy::eval(vector<city> master) {
	fitness = 0;
	for (int j = 1; j < order.size(); j++) {
		int lastspot = order.at(j - 1);
		int spot = order.at(j);
		double lastx = master.at(lastspot).xcord;
		double lasty = master.at(lastspot).ycord;
		double x = master.at(spot).xcord;
		double y = master.at(spot).ycord;
		fitness = fitness+(x -lastx)*(x - lastx) + (y - lasty)*(y - lasty);
	}
}
vector<policy> downsize() {
	vector<policy>temppop = population;
	
	population.erase(population.begin(), population.end());
	assert(population.size == 0); 
	while (population.size() < temppop.size()) {
		int spot1 = rand() % temppop.size();
		int spot2 = rand() % temppop.size();
		while (spot1 != spot2) {
			double fit1 = temppop.at(spot1).fitness;
			double fit2 = temppop.at(spot2).fitness;
			if (fit1 < fit2) {
				policy 1win;
				population.push_back(1win);
			}
			if (fit2 < fit1) {
				policy 2win;
				population.push_back(2win);
			}
		}
	}
	return population;
}
int main()
{
	srand(time(NULL));
	vector<policy> population;
	vector<policy> temppop;
	int maxgen=100;
	vector<city> master;
	for (int i = 0; i < 3; i++) {
		city a;
		a.xcord = kgrand;
		a.ycord = kgrand;
		master.push_back(a);

	}
	//// a full vector of cities exists now.

	for (int z = 0; z < pop_size/2; z++) {
		policy b;
		b.init();
		population.push_back(b);
	}//half population of policies exists
	for (int g = 0; g < maxgen; g++) {
		mutate();
		eval(master);
		downsize();
	}
	

	int iii;
	cin >> iii;
    return 0;
}



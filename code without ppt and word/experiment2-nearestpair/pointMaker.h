#pragma once
#include<random>
#include<vector>
#include<time.h>
#include<iostream>

namespace maker {
	bool isExist(std::vector<std::pair<double, double>> vec, std::pair<double, double> b) {
		for (std::vector<std::pair<double, double>>::iterator it = vec.begin(); it != vec.end(); it++) {
			if ((*it).first == b.first && (*it).second == b.second) {
				return true;
			}
		}
		return false;
	}
	std::vector<std::pair<double, double>> randomPoint(int len, double max, double min) {
		std::vector<std::pair<double, double>> a;
		std::uniform_real_distribution<double> unif(min, max);

		std::random_device rand_dev;          // Use random_device to get a random seed.

		std::mt19937 rand_engine(rand_dev()); // mt19937 is a good pseudo-random number 
											  // generator.
		for (int i = 0; i < len; i++) {
			double f = unif(rand_engine);
			double s = unif(rand_engine);
			a.push_back(std::pair<double, double>(f, s));
			/*if (!isExist(a, std::pair<double, double>(f, s))) {
				a.push_back(std::pair<double, double>(f, s));
			}
			else {
				i--;
			}*/
		}
		return a;
	}
	std::vector<std::pair<double, double>> pointCopy(std::vector<std::pair<double, double>> old) {
		std::vector<std::pair<double, double>> a;
		for (std::vector<std::pair<double, double>>::iterator it = old.begin(); it != old.end(); it++) {
			a.push_back(*(it));
		}
		return a;
	}
}
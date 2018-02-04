#pragma once
#include<iostream>
#include<vector>
const double MAX_DISTANCE = 1e20;
std::pair<double, double> savep1;
std::pair<double, double> savep2;
namespace solve {
	/*
	获取两点距离
	*/
	double distance(std::pair<double, double> p, std::pair<double, double> s) {
		return sqrt((p.first - s.first)*(p.first - s.first) + (s.second - p.second)*(s.second - p.second));
	}
	/*
	暴力法求解
	*/
	void traversal_pair(std::vector<std::pair<double, double>> vec) {
		double min = MAX_DISTANCE;
		double d;
		int s = vec.size();
		for (int i = 0; i < s; i++) {
			for (int j = i + 1; j < s; j++) {
				d = solve::distance(vec.at(i), vec.at(j));
				if (d < min) {
					min = d;
					savep1 = vec.at(i);
					savep2 = vec.at(j);
				}
			}
		}
		std::cout << "<" << savep1.first << "," << savep1.second << ">" << ", <" << savep2.first << ", " << savep2.second << ">" << std::endl;
		std::cout << min << std::endl;
	}
	/*
	按照x轴大小排序
	*/
	bool pair_sort(const std::pair<double, double> &a, const std::pair<double, double> &b) {
		if (a.first == b.first)
			return a.second < b.second;
		return a.first < b.first;
	}
	/*
	按照y轴大小排序
	*/
	bool pair_sort_y(const std::pair<double, double> &a, const std::pair<double, double> &b) {
		if (a.second == b.second)
			return a.first < b.first;
		return a.second < b.second;
	}
	/*
		这是通过二分法求的一种，但这一种嘛，有内排序，不表
	*/
	double _dichotomy_pair(std::vector<std::pair<double, double>> &vec, int l, int r) {
		if (l == r )
			return MAX_DISTANCE;
		if (l + 1 == r) {
			if(r>=vec.size())
				return MAX_DISTANCE;
			return distance(vec.at(l), vec.at(r));
		}

		int mid = (l + r) >> 1;
		double l_v = _dichotomy_pair(vec, l, mid);
		double r_v = _dichotomy_pair(vec, mid+1, r);

		double d = l_v<r_v?l_v:r_v;
		std::vector<std::pair<double, double>> tmp;
		for (int i = l; i < r; i++)  // push all in mid+-d to tmp
			if (fabs(vec[mid].first - vec[i].first) < d) 
				tmp.push_back(vec.at(i));

		std::sort(tmp.begin(), tmp.end(), pair_sort_y); // 通过y轴排序
		int s = tmp.size();
		double now;
		for (int i = 0; i < s; i++) {
			for (int j = i+1; j < s && fabs(tmp[i].second - tmp[j].second)<d; j++) {
				now = solve::distance(tmp.at(i), tmp.at(j));
				if (now < d) {
					d = now;
					savep1 = tmp.at(i);
					savep2 = tmp.at(j);
				}
			}
		}

		return d;
	}
	/*
	这是通过二分法求的一种，但这一种嘛，有内排序，不表
	*/
	void dichotomy_pair(std::vector<std::pair<double, double>> vec) {
		std::sort(vec.begin(), vec.end(), pair_sort);
		std::cout << _dichotomy_pair(vec, 0, vec.size()) << std::endl;
		std::cout << "<" << savep1.first << "," << savep1.second << ">" << ", <" << savep2.first << ", " << savep2.second << ">" << std::endl;
	}
	
	/*
	外排序应该怎么做呢= =、
	*/
	double _dichotomy_pair_2(std::vector<std::pair<double, double>> &vecx, std::vector<std::pair<double, double>> &vecy, int l, int r) {
		if (l == r)
			return MAX_DISTANCE;
		if (l + 1 == r) {
			if (r >= vecx.size())
				return MAX_DISTANCE;
			return distance(vecx.at(l), vecx.at(r));
		}
		int mid = (l + r) >> 1;
		double midx = vecx[mid].first;
		std::vector<std::pair<double, double>> ly, ry;
		for (std::vector<std::pair<double, double>>::iterator it = vecy.begin(); it != vecy.end(); it++) {
			if ((*it).first < midx)
				ly.push_back(*(it));
			else
				ry.push_back(*(it));
		}
		double l_v = _dichotomy_pair_2(vecx, ly, l, mid);
		double r_v = _dichotomy_pair_2(vecx, ry, mid + 1, r);

		double d = l_v<r_v ? l_v : r_v;
		std::vector<std::pair<double, double>> tmp;
		for (std::vector<std::pair<double, double>>::iterator it = vecy.begin(); it != vecy.end(); it++) {  // push all in mid+-d to tmp
			if (fabs(midx - (*it).first) < d) {
				tmp.push_back((*it));
			}
		}  // 左右按照y排序的两个数组
		int len = tmp.size();

		double min = d;
		double tempd;
		for (int i = 0; i < len; i++) { // 遍历左边
			// find start place 
			for (int j = i+1; j < len && fabs(tmp[i].second - tmp[j].second)<d; j++) {
				tempd = distance(tmp[i], tmp[j]);
				if (tempd < min) {
					min = tempd;
					savep1 = tmp.at(i);
					savep2 = tmp.at(j);
				}
			}
		}
		return min;

	}
	/*
	于是就写了一个没有内排序的。。。
	*/
	void dichotomy_pair_2(std::vector<std::pair<double, double>> vec) {
		std::vector<std::pair<double, double>> vecy = vec;
		std::sort(vec.begin(), vec.end(), pair_sort);
		std::sort(vecy.begin(), vecy.end(), pair_sort_y);
		std::cout << "<" << savep1.first << "," << savep1.second << ">" << ", <" << savep2.first << ", " << savep2.second << ">" << std::endl;
		std::cout << _dichotomy_pair_2(vec, vecy, 0, vec.size()) << std::endl;
	}
}
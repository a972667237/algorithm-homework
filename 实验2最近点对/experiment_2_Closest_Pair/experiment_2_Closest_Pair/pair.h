#pragma once
#include<iostream>
#include<vector>
const double MAX_DISTANCE = 1e20;
std::pair<double, double> savep1;
std::pair<double, double> savep2;
namespace solve {
	/*
	��ȡ�������
	*/
	double distance(std::pair<double, double> p, std::pair<double, double> s) {
		return sqrt((p.first - s.first)*(p.first - s.first) + (s.second - p.second)*(s.second - p.second));
	}
	/*
	���������
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
	����x���С����
	*/
	bool pair_sort(const std::pair<double, double> &a, const std::pair<double, double> &b) {
		if (a.first == b.first)
			return a.second < b.second;
		return a.first < b.first;
	}
	/*
	����y���С����
	*/
	bool pair_sort_y(const std::pair<double, double> &a, const std::pair<double, double> &b) {
		if (a.second == b.second)
			return a.first < b.first;
		return a.second < b.second;
	}
	/*
		����ͨ�����ַ����һ�֣�����һ����������򣬲���
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

		std::sort(tmp.begin(), tmp.end(), pair_sort_y); // ͨ��y������
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
	����ͨ�����ַ����һ�֣�����һ����������򣬲���
	*/
	void dichotomy_pair(std::vector<std::pair<double, double>> vec) {
		std::sort(vec.begin(), vec.end(), pair_sort);
		std::cout << _dichotomy_pair(vec, 0, vec.size()) << std::endl;
		std::cout << "<" << savep1.first << "," << savep1.second << ">" << ", <" << savep2.first << ", " << savep2.second << ">" << std::endl;
	}
	
	/*
	������Ӧ����ô����= =��
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
		}  // ���Ұ���y�������������
		int len = tmp.size();

		double min = d;
		double tempd;
		for (int i = 0; i < len; i++) { // �������
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
	���Ǿ�д��һ��û��������ġ�����
	*/
	void dichotomy_pair_2(std::vector<std::pair<double, double>> vec) {
		std::vector<std::pair<double, double>> vecy = vec;
		std::sort(vec.begin(), vec.end(), pair_sort);
		std::sort(vecy.begin(), vecy.end(), pair_sort_y);
		std::cout << "<" << savep1.first << "," << savep1.second << ">" << ", <" << savep2.first << ", " << savep2.second << ">" << std::endl;
		std::cout << _dichotomy_pair_2(vec, vecy, 0, vec.size()) << std::endl;
	}
}
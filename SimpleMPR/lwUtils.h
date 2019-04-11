#ifndef _LW_UTILS_H
#define _LW_UTILS_H

#include <iostream>
#include <vector>

using namespace std;

class lwUtils
{
public:
	// ������һ������
	static void Normalize(vector<double>& v);

	// ������˲���
	static  vector<double> CrossProduct(vector<double>& a, vector<double>& b);

};

#endif // !_LW_UTILS_H

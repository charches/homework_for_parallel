#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <ctime>
#include <iomanip>
#ifdef __MPI
#include <mpi.h>
#endif

using namespace std;

class Func {//记录一个函数的信息
private:
	string func_name;//函数名
	int cnt = 0;//函数调用次数
	double time_cnt = 0;//函数总调用时间
	double start_time = 0;//记录函数开始调用时间
public:
	Func(const string& name);
	Func();
	friend class Func_info;
	friend ostream& operator<<(ostream& os, const Func& func);
	friend ofstream& operator<<(ofstream& output_file, const Func& func);
};

#endif



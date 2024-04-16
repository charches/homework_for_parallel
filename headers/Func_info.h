#ifndef FUNC_INFO_H
#define FUNC_INFO_H

#include <iostream>
#include <unordered_map>
#include <ctime>
#include <iomanip>
#include <fstream>
#include "./Func.h"
#ifdef __MPI
#include <mpi.h>
#endif

using namespace std;

class Func_info {//函数信息总表
public:
	static unordered_map<string, Func*> func_list;//函数表

	static double total;//函数调用总时间
	static void tick(const string& name);//函数计时器

	static void screen_timer_print();//打印计时结果
	static void file_timer_print(ofstream& output_file);
};

#endif

#include "../headers/Func.h"
#include "../headers/Func_info.h"

using namespace std;

Func::Func(){}

Func::Func(const string& name):func_name(name), cnt(0), time_cnt(0), start_time(0){}

ostream& operator<<(ostream& os, const Func& func)
{
	int calls = func.cnt / 2;
	os << setw(25) << right << func.func_name;
	os << setw(10) << right << calls;
	os << setw(15) << right << func.time_cnt;
	os << setw(15) << right << func.time_cnt / calls;
	os << setw(15) << right << func.time_cnt / Func_info::total * 100 << "%";
	return os;
}

ofstream& operator<<(ofstream& output_file, const Func& func)
{
	int calls = func.cnt / 2;
	output_file << setw(25) << right << func.func_name;
	output_file << setw(10) << right << calls;
	output_file << setw(15) << right << func.time_cnt;
	output_file << setw(15) << right << func.time_cnt / calls;
	output_file << setw(15) << right << func.time_cnt / Func_info::total * 100 << "%";
	return output_file;
}
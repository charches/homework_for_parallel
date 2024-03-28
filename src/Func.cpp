#include "../headers/Func.h"
#include <iomanip>
#include "../headers/Func_info.h"

using namespace std;

Func::Func(){}

Func::Func(const string& name):func_name(name), cnt(0), time_cnt(0), start_time(0){}

ostream& operator<<(ostream& os, const Func& func)
{
	int calls = func.cnt / 2;
	double total = double(func.time_cnt)/ CLOCKS_PER_SEC;
	os << setw(25) << right << func.func_name;
	os << setw(10) << right << calls;
	os << setw(15) << right << total;
	os << setw(15) << right << total / calls;
	os << setw(15) << right << double(func.time_cnt) / double(Func_info::total) * 100 << "%";
	return os;
}

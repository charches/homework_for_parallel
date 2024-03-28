#include "../headers/Func.h"
#include "../headers/Func_info.h"
#include <iomanip>

using namespace std;

unordered_map<string, Func*> Func_info::func_list;
clock_t Func_info::total = 0;

void Func_info::tick(const string& name)
{
	clock_t now_time = clock();
	auto pos = func_list.find(name);
	if (pos == func_list.end())
		func_list[name] = new Func(name);
	Func* now_func = func_list[name];
	now_func->cnt += 1;
	if (now_func->cnt % 2 == 1)
		now_func->start_time = now_time;
	else
	{
		clock_t time = now_time - now_func->start_time;
		now_func->time_cnt += time;
		total += time;
	}
}
void Func_info::timer_print()
{
	for (auto i = func_list.begin(); i != func_list.end(); i++)
	{
		cout << *i->second << endl;
	}
	for (auto i = func_list.begin(); i != func_list.end(); i++)
	{
		delete i->second;
	}
}

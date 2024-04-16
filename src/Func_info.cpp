#include "../headers/Func.h"
#include "../headers/Func_info.h"

using namespace std;

unordered_map<string, Func*> Func_info::func_list;
double Func_info::total = 0;

void Func_info::tick(const string& name)
{
	double now_time;

	#ifndef __MPI
	now_time = clock() / CLOCKS_PER_SEC;
	#endif
	
	#ifdef __MPI
	now_time = MPI_Wtime();
	#endif

	auto pos = func_list.find(name);
	if (pos == func_list.end())
		func_list[name] = new Func(name);
	Func* now_func = func_list[name];
	now_func->cnt += 1;
	if (now_func->cnt % 2 == 1)
		now_func->start_time = now_time;
	else
	{
		double time = now_time - now_func->start_time;
		now_func->time_cnt += time;
		total += time;
	}
}

void Func_info::screen_timer_print()
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

void Func_info::file_timer_print(ofstream& output_file)
{
	for (auto i = func_list.begin(); i != func_list.end(); i++)
	{
		output_file << *i->second << endl;
	}
	for (auto i = func_list.begin(); i != func_list.end(); i++)
	{
		delete i->second;
	}
}

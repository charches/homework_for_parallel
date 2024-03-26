#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

class Input {
	public:
		string cal;
		string mat_type;
		int nr = 0, nc = 0;
		int mat_prt = 0;

		Input(){}
		Input(const string& filename);
		friend ostream& operator<<(ostream& my_cout, const Input& input);
};

void to_lower(string& str)
{
	for (int i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);
}
Input::Input(const string& filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			size_t pos = line.find("#");
			if (pos != string::npos)
				    line = line.substr(0, pos);
			stringstream iss(line);;
			string type, parameter;
			iss >> type >> parameter;
			to_lower(type);
			to_lower(parameter);
			if (type == "calculation")
				cal = parameter;
			else if (type == "matrix_type")
				mat_type = parameter;
			else if (type == "matrix_print")
				mat_prt = stoi(parameter);
			else if (type == "nrows")
				nr = stoi(parameter);
			else if(type == "ncols")
				nc = stoi(parameter);
		}
	}
	else {
		cout << "Can't open the file!";
		exit(0);
	}
}

ostream& operator<<(ostream& my_cout, const Input& input)
{
	my_cout << "calculation: " << input.cal << endl;
	my_cout << "matrix_type: " << input.mat_type << endl;
	my_cout << "matrix_print: " << input.mat_prt << endl;
	my_cout << "nrows: " << input.nr << endl;
	my_cout << "ncols: " << input.nc << endl;
	return my_cout;
}

int main()
{
	string filename;
	cin >> filename;
	Input input(filename);
	cout << input;
	return 0;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

void saveToFile(const string& filename, const vector<string>& data)
{
	string line;
	ofstream out;
	out.open(filename);
	if(!out.is_open())
	{
		cout << "Ошибка!";
	}
	else
	{
		for (auto i: data)
		{
			out << i << "\n";
		}
	}
	out.close();
};

vector <string> loadFromFile(const string& filename, vector<string>& outData) 
{
	string read;
	vector <string> read_file;
	ifstream in;
	in.open(filename);
	if(!in.is_open())
	{
		cout << "Не удалось открыть файл!";
	}
	else
	{
		while(getline(in, read))
		{
			read_file.push_back(read);
		}
	}
	in.close();
	return read_file;
};

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	vector <string> data;
	string filename;
	string arr;
	vector <string> read_file1;
	cout << "Как вы хотите назвать файл?: ";
	cin >> filename;
	filename.append(".txt");
	cin.ignore();
	cout << "Введите массив слов, который нужно записать в файл (напишите 0 в отдельной строке для конца записи): " << endl;
	while (getline(cin, arr))
	{
		if(arr == "0")
		{
			break;
		}
		data.push_back(arr);
	}
	saveToFile(filename, data);
	read_file1 = loadFromFile(filename, data);
	cout << "Массив слов, написанный в файле с названием " << filename << ":" << endl;
	for(auto i: read_file1)
	{
		cout << i << "\n";
	}
	return 0;
}
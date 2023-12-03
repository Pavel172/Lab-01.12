#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

struct Book
{
	string Author;
	string Title;
	int Year;
};

void saveToFile(const string& filename, const vector<Book>& data, const int& quantity)
{
	ofstream out;
	Book book1;
	out.open(filename);
	if (!out.is_open())
	{
		cout << "������!";
	}
	else
	{
		for (int i = 0; i < quantity; ++i)
		{
			book1 = data[i];
			out << i + 1 << "-�� �����: " << "�����:" << book1.Author << "; ��������:" << book1.Title <<  "; ��� ����������:" << book1.Year << ";\n";
		}
	}
	out.close();
};

vector <Book> loadFromFile(const string& filename, vector<Book>& outData, const int& quantity)
{
	string read, find;
	vector <string> read_file;
	vector<Book> from_file;
	ifstream in;
	Book book1;
	int temp;
	in.open(filename);
	if (!in.is_open())
	{
		cout << "�� ������� ������� ����!";
	}
	else
	{
		while (getline(in, read))
		{
			read_file.push_back(read);
		}
		for (int i = 0; i < quantity; ++i)
		{
			read = read_file[i];
			for (int i = 0; i < read.size(); ++i)
			{
				if (read[i] == ':' and read[i - 1] == '�')
				{
					temp = i;
					++i;
					while (read[i] != ';')
					{
						find.push_back(read[i]);
						++i;
					}
					i = temp;
					book1.Author = find;
					find.clear();
				}
				if (read[i] == ':' and read[i - 1] == '�')
				{
					temp = i;
					++i;
					while (read[i] != ';')
					{
						find.push_back(read[i]);
						++i;
					}
					i = temp;
					book1.Title = find;
					find.clear();
				}
				if (read[i] == ':' and read[i - 1] == '�')
				{
					temp = i;
					++i;
					while (read[i] != ';')
					{
						find.push_back(read[i]);
						++i;
					}
					i = temp;
					book1.Year = stoi(find);
					find.clear();
				}
			}
			from_file.push_back(book1);
		}
	}
	in.close();
	return from_file;
};

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	int quantity = 0;
	Book book;
	vector <Book> books;
	vector <Book> books_from_file;
	string filename;
	cout << "������� �������� �����: ";
	cin >> filename;
	filename.append(".txt");
	cout << "������� ���������� ����: ";
	cin >> quantity;
	for (int i = 0; i < quantity; ++i)
	{
		cout << "������� ������ " << i+1 << "-�� �����: ";
		cin >> book.Author;
		cin.ignore();
		cout << "������� �������� " << i+1 << "-�� �����: ";
		getline(cin, book.Title);
		cout << "������� ��� ���������� " << i+1 << "-�� �����: ";
		cin >> book.Year;
		books.push_back(book);
		cout << endl;
	}
	saveToFile(filename, books, quantity); 
	books_from_file = loadFromFile(filename, books, quantity);
	cout << "�����, ����������� � ����� " << filename << " : " << endl;
	for (int i = 0; i < quantity; ++i)
	{
		book = books_from_file[i];
		cout << i + 1 << "-�� �����: " << "�����: " << book.Author << "; ��������: " << book.Title << "; ��� ����������: " << book.Year << "\n";
	}
	return 0;
}
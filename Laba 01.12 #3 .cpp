#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

struct Student
{
    string Name;
    int Year;
    int Score;
};

struct Group
{
    string group_name;
    vector <Student> students;
    int quantity;
};

void saveToFile(const string& filename, vector <Group>& Groups, const int& groups_count)
{
    ofstream out;
    out.open(filename);
    if (!out.is_open())
    {
        cout << "Ошибка!";
    }
    else
    {
        for(int i = 0; i < groups_count; ++i)
        {
            for (int j = 0; j < Groups[i].quantity; ++j)
            {
                out << "Группа:" << Groups[i].group_name << "; Имя:" << Groups[i].students[j].Name << "; Год рождения:" << Groups[i].students[j].Year << "; Оценка:" << Groups[i].students[j].Score << ";" << endl;
            }
        }
    }
    out.close();
}

vector <Group> loadFromFile(const string& filename, vector<Group>& in_file, int& groups_count)
{
	int quantity = 0, count = 0, flag = 0, t = 0, temp = 0;
	const int gr = groups_count;
	string read, groupname;
	vector <string> read_file;
	vector<Group> from_file;
	Student student;
	ifstream in;
	string name, date, score;
	Group group;
	in.open(filename);
	if (!in.is_open())
	{
		cout << "Не удалось открыть файл!";
	}
	else
	{
		while (getline(in, read))
		{
			read_file.push_back(read);
		}
		for (int j = 0; j < groups_count; ++j)
		{
			flag = 1;
			count = 0;
			for (int i = t; i < in_file[j].quantity + t; ++i)
			{
				++count;
				read = read_file[i];
				for (int i = 0; i < read.size(); ++i)
				{
					if (read[i] == ':' and read[i - 1] == 'а' and read[i - 2] == 'п' and flag == 1)
					{
						temp = i;
						++i;
						while (read[i] != ';')
						{
							groupname.push_back(read[i]);
							++i;
						}
						i = temp;
						group.group_name = groupname;
						groupname.clear();
						flag = 0;
					}
					if (read[i] == ':' and read[i - 1] == 'я' and read[i - 2] == 'м')
					{
						temp = i;
						++i;
						while (read[i] != ';')
						{
							name.push_back(read[i]);
							++i;
						}
						i = temp;
						student.Name = name;
						name.clear();
					}
					if (read[i] == ':' and read[i - 1] == 'я' and read[i - 2] == 'и')
					{
						temp = i;
						++i;
						while (read[i] != ';')
						{
							date.push_back(read[i]);
							++i;
						}
						i = temp;
						student.Year = stoi(date);;
						date.clear();
					}
					if (read[i] == ':' and read[i - 1] == 'а' and read[i - 2] == 'к')
					{
						temp = i;
						++i;
						while (read[i] != ';')
						{
							score.push_back(read[i]);
							++i;
						}
						i = temp;
						student.Score = stoi(score);
						score.clear();
					}
				}
				group.students.push_back(student);
			}
			group.quantity = count;
			from_file.push_back(group);
			group.students.clear();
			t = in_file[j].quantity;
		}
	}
	in.close();
	return from_file;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    int quantity = 0, groups_count = 0, l =0;
    Student student;
    string groupname, filename;
    Group group;
    vector <Student> students_;
    vector <Group> Groups, groups_from_file;
    cout << "Введите количество групп студентов: ";
    cin >> groups_count;
    for (int i = 0; i < groups_count; ++i)
    {
        cout << "Введите название " << i + 1 << " группы студентов: ";
        cin >> groupname;
        cout << "Введите количество студентов в " << i + 1 << " группе: ";
        cin >> quantity;
        for (int j = 0; j < quantity; ++j)
        {
			cin.ignore();
            cout << "Введите имя " << j + 1 << "-го студента " << l + 1 << " группы: ";
            cin >> student.Name;
            cout << "Введите год рождения " << j + 1 << "-го студента " << l + 1 << " группы: ";
            cin >> student.Year;
            cout << "Введите оценку (от 2 до 5) " << j + 1 << "-го студента " << l + 1 << " группы: ";
            cin >> student.Score;
            students_.push_back(student);
        }
        ++l;
        group.group_name = groupname;
        group.students = students_;
        group.quantity = quantity;
        Groups.push_back(group);
        students_.clear();
    }
    cout << "Введите название файла: ";
    cin >> filename;
    filename.append(".txt");
    saveToFile(filename, Groups, groups_count);
	groups_from_file = loadFromFile(filename, Groups, groups_count);
	cout << "Группы студентов, загруженные с файла " << filename << ": " << endl;
	for (int j = 0; j < groups_from_file.size(); ++j)
	{
		for (int i = 0; i < groups_from_file[j].quantity; ++i)
		{
			cout << "Группа: " << groups_from_file[j].group_name << "; Имя: " << groups_from_file[j].students[i].Name << "; Год рождения: " << groups_from_file[j].students[i].Year << "; Оценка: " << groups_from_file[j].students[i].Score << endl;
		}
		cout << endl;
	}
    return 0;
}
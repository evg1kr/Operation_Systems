#include<fstream>
#include<iostream>
#include<iomanip>

struct employee
{
	int num;
	char name[10];
	double hours;
};

void Creator(char Header[20], int num_of_emp) 
{
	employee* mas = new employee[num_of_emp];

	for (int i = 0; i < num_of_emp; i++) {
		std::cin >> mas[i].num >> mas[i].name >> mas[i].hours;
	}

	std::ofstream out(Header, std::ios::binary);

	for (int i = 0; i < num_of_emp; i++)
	{
		out.write((char*)&mas[i], sizeof(employee));
	}
}

void Reporter(char Header[20], char Report[20], int salary)
{
	setlocale(LC_ALL, "rus");
	
	employee temp;

	std::ifstream in(Header, std::ios_base::binary);
	std::ofstream out(Report);

	out << std::setw(30) << " ";
	out << "Отчет по файлу " << Header << "." << std::endl;
	out << std::setw(20) << "Номер сотрудника " << std::setw(20) << "имя сотрудника " << std::setw(20) << "часы " << std::setw(20) << "зарплата " << std::endl;
	while (in.read((char*)&temp, sizeof(employee))) 
	{
		out << std::setw(20) << temp.num << std::setw(20) << temp.name << std::setw(20) << temp.hours << std::setw(20) << temp.hours * salary << std::endl;
	}
}

int main() {
	char bin_file[20];
	std::cout << "Insert name of bin" << std::endl;
	std::cin >> bin_file;

	int number;
	std::cout << "Insert number of employees" << std::endl;
	std::cin >> number;
	
	Creator(bin_file, number);

	employee temp;
	std::ifstream in(bin_file, std::ios_base::binary);

	while (in.read((char*)&temp, sizeof(employee)))
	{
		std::cout << std::setw(20) << temp.num << std::setw(20) << temp.name << std::setw(20) << temp.hours << std::endl;
	}

	char Report_name[20];
	std::cout << "Insert name of report" << std::endl;
	std::cin >> Report_name;

	int salary_p_h;
	std::cout << "Insert salary per hour" << std::endl;
	std::cin >> salary_p_h;

	Reporter(bin_file, Report_name, salary_p_h);

	return 0;
}
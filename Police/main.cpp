#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4326)
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"

#define Enter    12
#define Escape    27
#define UP_ARRON  72
#define DOWN_ARRON  80
const char* MENU_ITEMS[] =
{
	"1. Load database from file",
	"2. Save  the database to a file",
	"3. Display the database on the screen",
	"4. Display information by number",
	"5. Add a violtion",
};
const int MENU_SIZE = sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]);

//const std::map<int, std::string>MENU_ITEMS =
//{
	//"1. Load database from file",
	//"2. Save  the database to a file",
	//"3. Display the database on the screen",
	//"4. Display information by number",
	//"5. Add a violtion",
//};
const std::map<int, std::string>VIOLATIONS =
{
	{1, "Seat Belt"},
	{2, "Parking in the wrong place"},
	{3, "Crossing a solid line"},
	{4, "Speeding"},
	{5, "Lack of a driver's license "},
	{6, "Lack of the right to drive a car"},
	{7, "Lack of insurancce "},
	{8, "Driving through a red light "},
	{9, "Driving into the oncoming lane"},
	{10, "Driving at the Crossroads"},
	{11, "Driving while Intoxicated"},

};

class Crime
{
	int id;
	std::string place;
	tm time;
public:
	/*const std::string& get_license_plate()const
	{
		return license_plate;

	}*/
	int get_id()const
	{
		return id;
	}
	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const int get_violation_id()const
	{
		return id;
	}

	const std::string& get_place()const
	{
		return place;
	}
	const std::string get_time()const
	{
		/*std::string result = asctime(&time);
		result.pop_back();
		return result;*/
		const int SIZE = 256;
		char formated[SIZE]{};
		strftime(formated, SIZE, "%R,%e,%m.%y", &time);
		return formated;
	}
	const time_t get_timestamp()const
	{
		tm copy = time;
		return mktime(&copy);
	}
	/*void set_license_plate(const std::string& license_plate)
	{
		this->license_plate = license_plate;
	}*/
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		char* time_buffer = new char[time.size() + 1] {};
		strcpy(time_buffer, time.c_str());

		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ": ./";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);

		delete[] time_buffer;

		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon= time_elements[3];
		this->time.tm_year= time_elements[4]-1900;

		//this->time = time;
	}
	void set_timestamp(time_t timestamp)
	{
		time = *localtime(&timestamp);
	}

	 //                 constructors:
	explicit Crime
	(
		int violation_id = 0,
		const std::string& place = "Place",
		const std::string& time = "00:00 01.01.200"
	)
	{
		this->time = {};
		this->set_violation_id(violation_id);
		this->set_place(place);
		this->set_time(time);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif // DEBUG
	}
	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG

	}

};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << " : " << obj.get_place() << " " << obj.get_violation();
}
std::ofstream& operator<<(std::ofstream& os, const Crime& obj)
{
	 os << obj.get_violation_id() << " " << obj.get_timestamp() << " " << obj.get_place();
	 return os;
}
std::istream& operator>>(std::istream& is, Crime& obj)
{
	int id;
	time_t timestamp;
	std::string place;
	is >>  id >> timestamp;
	std::getline(is, place, ',');
	is.ignore();
	obj.set_violation_id(id);
	obj.set_timestamp(timestamp);
	obj.set_place(place);
	return is;
}
int menu();
void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base,const std::string& filename);
std::map<std::string, std::list<Crime>> load(const std::string& filename);

void main()
{
	setlocale(LC_ALL, "");
	/*Crime crime(1, "Street.Limaya", "18:10 1.09.2024");
	cout << crime << endl;*/

	std::map<std::string, std::list<Crime>> base 
	{
		{"a777bb", {Crime(1,"Limaya str", "18:10 1.09.2024"), Crime(2,"Liberty sq.","12:25 20.08.2024")}},
		{"a000bb", {Crime(6,"Kitega str", "17:45 1.08.2024"), Crime(8,"Mongala sq.","17:45 01.08.2024")}},
		{"a001aa", {Crime(10,"Niagwe str", "21:50 1.08.2024"), Crime(9,"Ngaliema sq","21:50 01.08.2024")}},
	};
	print(base);
	save(base, "base.txt");
	do
	{
		switch (menu())
		{

		}
	} while (true);

}
int menu()
{
	int selected_item = 0;
	char key;
	do
	{
		system("CLS");
		for (int i = 0; i < sizeof(MENU_SIZE);i++)
		{
			cout << (i == selected_item ?  "[" : " ");
			cout.width(32);
			cout << std::left;
			cout << MENU_ITEMS[i];
			cout << (i == selected_item ?  "]" : " ");
			cout << endl;
		}
		key = _getch();
		//cout << (int)key << endl;
		switch (key)
		{
		case UP_ARRON: 
			if (selected_item > 0)selected_item--; break;
		case DOWN_ARRON: 
			if (selected_item > sizeof(MENU_ITEMS[0]) - 1) selected_item--; break;
		case Enter: return selected_item + 1 ;
		case Escape: return 0;
		}
	} while (true);
	return 0;
}
void print(const std::map<std::string, std::list<Crime>>& base)
{
	cout << delimiter << endl;
	for
		(
			std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
			map_it != base.end();
			++map_it

			)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
	cout << "Number of plates in base: " << base.size() << endl;
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
std::ofstream fout(filename);
	//fout << delimiter << endl;
	for
		(
			std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
			map_it != base.end();
			++map_it

			)
	{
		fout << map_it->first << ":\t";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << *it << " , ";
		}
		fout.seekp(-1, std::ios::cur);
		fout << ";\n";
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}
std::map<std::string, std::list<Crime>> load(const std::string& filename)
{
	std::map<std::string, std::list<Crime>>base;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string license_plate;
			std::getline(fin, license_plate);
			//if (license_plate.empty())continue;
			license_plate.erase(0, license_plate.find_first_not_of('\n'));
			fin.ignore();

			std::string crimes;
			std::string buffer;
			std::getline(fin, buffer);
			char* sz_buffer = new char[buffer.size() + 1] {};
			strcpy(sz_buffer, buffer.c_str());
			char delimiters[] = ",";
			Crime crime(0, "place", "00:00 01.01.2000");
			for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiter))
			{
				//std::cout << pch << "\t";
				//std::string s_crime(pch);
				//std::string s_crime = pch;
				std::stringstream ss_crime(pch,std::ios_base::in | std::ios_base::out);
			//Crime crime(0, "place", "00:00 01.01.2000");
				//Crime crime;
				ss_crime >> crime;
				base[license_plate].push_back(crime);
				
			}
			cout << endl;
				/*std::string license_plate;
				std::getline(fin, license_plate , ':');
				fin.ignore();
				Crime crime(0,"place","time");
				fin >> crime;
				base[license_plate].push_back(crime);*/
				delete[] sz_buffer;
		}
		fin.close();
	}
	else {
		std::cerr << "Error: file not found" << endl;
	}
	return base;
}
#include<iostream>
#include<string>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"

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
	std::string license_plate;
	int id;
	int violation;
	std::string place;
	std::string time;
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
	const std::string& get_place()const
	{
		return place;
	}
	const std::string& get_time()const
	{
		return time;
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
		this->time = time;
	}

	 //                 constructors:
	Crime(int violation_id, const std::string& place, const std::string& time)
	{
		//set_license_plate(license_plate);
		set_violation_id(violation_id);
		set_place(place);
		set_time(time);
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

void main()
{
	setlocale(LC_ALL, "");
	/*Crime crime(1, "Street.Limaya", "18:10 1.09.2024");
	cout << crime << endl;*/

	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb", {Crime(1,"Limaya str", "18:10 1.09.2024"), Crime(2,"Liberty sq.","12:25 20.08.2024")}},
		{"a000bb", {Crime(6,"Kitega str", "17:45 1.08.2024"), Crime(8,"Mongala sq.","17:45 01.08.2024")}},
		{"a001aa", {Crime(10,"Niagwe str", "21:50 1.08.2024"), Crime(9,"Ngaliema sq","21:50 01.08.2024")}},
	};
	cout << delimiter << endl;
	for
		(
			std::map<std::string, std::list<Crime>>::iterator map_it = base.begin();
			map_it != base.end();
			++map_it

			)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}

}
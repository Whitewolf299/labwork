#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <map>
#include <ctime>
#include <cstdlib>

using namespace std;

// use a HT to count frequencies

class Patient
{
public:
string name;
int age;
int arrival_time;
int severity;
int life_points;


int getPriority() const
{
	return severity * (100 - arrival_time) - 2 * age;
}

};

bool operator<(const Patient& left, const Patient& right)
{
	return left.getPriority() < right.getPriority();
}

bool operator>(const Patient& left, const Patient& right)
{
	return left.getPriority() > right.getPriority();
}

bool operator==(const Patient& left, const Patient& right)
{
	return left.getPriority() == right.getPriority();
}

void task1()
{
	string user_input;
	cout << "Enter Stuff: ";
	getline(cin, user_input);
	vector<char> keys{};
	unordered_map<char, int> frequencies{};
	//            KEY,  Value

	for (auto ch : user_input)
	{
		frequencies[ch]++;
	}

	for (auto kvp : frequencies)
	{
		cout << "'" << kvp.first << "' : " << kvp.second << endl;
		keys.push_back(kvp.first);
	}

	sort(keys.begin(), keys.end());
	for (auto key : keys)
	{
		cout << "'" << key << "' : " << frequencies[key] << endl;
	}
}

void task2()
{
	priority_queue<Patient> waitlist{};
	srand(time(NULL));

	for (int i = 0; i < 100; i++)
	{
		Patient p{};
		p.age = rand() % 99 + 1;
		p.severity = rand() % 99 + 1;
		p.arrival_time = i;
		p.life_points = rand() % 99 + 1;
		waitlist.push(p);
	}

	int timer = 0;
	while (waitlist.size() > 0)
	{
		timer++;
		Patient p = waitlist.top();
		waitlist.pop();

		cout << "looking at Patient: " << endl
			<< "Name: " << p.name << endl
			<< "Age: " << p.age << endl
			<< "Severity: " << p.severity << endl
			<< "Priority: " << p.getPriority() << endl << "..." << endl;
		if (timer > p.life_points)
		{
			cout << "DEAD" << endl;
		}
		else
		{
			cout << "Yay, Saved" << endl;
		}
		cout << endl;
	}


}

void task3()
{
	int power = 1;
	string output;
	int mask = 1;
	if (n == 0)
	{
		return "0";
	}
	while (mask <= n)
	{
		int digit = (n / mask) % 2;
		if (digit == 1)
		{
			output = "1" + output;
		}
		else
		{
			output = "0" + output;
		}
		mask = pow(2, power);
		power++;
	}
}

void task5()
{
	vector<string> result{};
	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		result.push_back(string{ ch });

	}
	length--;
}

int main()
{
	task1();
	return 0;

}
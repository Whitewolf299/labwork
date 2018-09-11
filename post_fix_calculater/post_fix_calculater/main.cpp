#include <iostream>
#include <string>
#include "StringSplitter.h"
#include <vector>
#include <stack>

using namespace std;

void multiplier(stack<double> &calc)
{
	double left_side, right_side;
	left_side = calc.top();
	calc.pop();
	right_side = calc.top();
	calc.pop();
	calc.push((left_side * 1.0)*(right_side * 1.0));
}
void adder(stack<double> &calc)
{
	double left_side, right_side;
	left_side = calc.top();
	calc.pop();
	right_side = calc.top();
	calc.pop();
	calc.push((left_side * 1.0)+(right_side * 1.0));
}
void divider(stack<double> &calc)
{
	double left_side, right_side;
	left_side = calc.top();
	calc.pop();
	right_side = calc.top();
	calc.pop();
	calc.push((left_side * 1.0)/(right_side * 1.0));
}
void subtractor(stack<double> &calc)
{
	double left_side, right_side;
	left_side = calc.top();
	calc.pop();
	right_side = calc.top();
	calc.pop();
	calc.push((left_side * 1.0)-(right_side * 1.0));
}

int main(void)
{
	string ans = "y";
	while (ans == "y")
	{

		int checker = 1;
		string line;

		while (checker != 0)
		{
			cout << " Enter a operation in post-fix form to be solved : ";

			getline(cin, line);
			string to_analyze = line;
			int result = 0;

			try
			{
				result = stoi(to_analyze);
				checker = 0;
			}
			catch (...)
			{
				cout << "Could not parse " << to_analyze
					<< endl;

			}
		}

		vector<string> pieces =
			StringSplitter::split(line, " ");
		stack<double> calc;
		for (auto item : pieces)
		{

			if (item != "*" && item != "+" && item != "/" && item != "-")
			{
				calc.push(stoi(item));
			}
			else {
				if (item == "*")
				{
					multiplier(calc);
				}
				if (item == "+")
				{
					adder(calc);
				}
				if (item == "/")
				{
					divider(calc);
				}
				if (item == "-")
				{
					subtractor(calc);
				}
			}
		}

		if (calc.size() != 1)
		{
			cout << " This is an invalid equation" << endl;

		}
		else
		{
			cout << "The answer is : " << calc.top() << endl << endl;
		}
		cout << "Would you like to ask another querry (y/n) :";
		getline(cin, ans);
	}
	cout << endl << endl << " Thankyou have a nice day :) " << endl;
}
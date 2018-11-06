#include <unordered_map> //hash table
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "StringSplitter.h"
using namespace std;

//LAB EXTRA CREDIT
void concordance(string text)
{
	//TODO
}

bool hasUniqueChars(string text)
{
	unordered_map<char, int> unique;
	int counter = 0;

	while (counter < text.length())
	{
		if (unique[text[counter]] > 0)
		{
			unique[text[counter]] += 1;
		}
		else
		{
			unique[text[counter]] = 1;
		}
		counter++;
	}

	for (auto chars : unique)
	{
		if (chars.second > 1)
		{
			return false;
		}
	}

	return true;
}

bool isAnagram(string first, string second)
{
	unordered_map<char, int> unique1;
	unordered_map<char, int> unique2;
	int counter = 0;

	while (counter < first.length())
	{
		if (unique1[first[counter]] > 0)
		{
			unique1[first[counter]] += 1;
		}
		else
		{
			unique1[first[counter]] = 1;
		}
		counter++;
	}
	counter = 0;
	while (counter < second.length())
	{
		if (unique2[second[counter]] > 0)
		{
			unique2[second[counter]] += 1;
		}
		else
		{
			unique2[second[counter]] = 1;
		}
		counter++;
	}

	for (auto item : unique1)
	{
		if (item.second != unique2[item.first])
		{
			return false;
		}
	}
	return true;
}

string mostCommonSubstring(string text, int size)
{
	if (size > text.length() || size < 1)
	{
		return "NULL";
	}
	unordered_map<string, int> common;
	string temp = "";
	int counter = 0;
	while (counter + (size - 1) < text.size())
	{
		for (int I = 0; I < size; I++)
		{
			temp = temp + text[counter + I];
		}

		common[temp]++;
		counter++;
		temp = "";
	}
	int highest = 0;
	string high = "";
	for (auto& items : common)
	{
		if (highest < items.second)
		{
			high = items.first;
			highest = items.second;
		}
	}

	return high;
}

int main(void)
{
/*
	ifstream input_file{ "test_file.txt" };
	string all_lines;
	if (input_file.is_open())
	{
		while (input_file.good() == true)
		{
			string line;
			getline(input_file)
		}
	}
*/

	//unique chars test
	cout << boolalpha;
	cout << "***unique characters test***" << endl;

	//test case #1
	cout << "abcde: " <<
		hasUniqueChars("abcde") 
		<< " (expected: true)"
		<< endl;
 
	//test case #2:
	cout << "aaaa: " <<
		hasUniqueChars("aaaa")
		<< " (expected: false)"
		<< endl;

	//test case #3:
	cout << "(empty string): " <<
		hasUniqueChars("")
		<< " (expected: true)"
		<< endl;

	//test case #4:
	cout << "abcdea: " <<
		hasUniqueChars("abcdea")
		<< " (expected: false)"
		<< endl;

	//anagram tests
	cout << endl << endl;
	cout << "***anagram tests***" << endl;

	//test case #1:
	cout << "tab, bat: " <<
		isAnagram("tab", "bat")
		<< " (expected: true)"
		<< endl;

	//test case #2
	cout << "bat, tab: " <<
		isAnagram("bat", "tab")
		<< " (expected: true)"
		<< endl;

	//test case #3
	cout << "(empty), (empty): " <<
		isAnagram("", "")
		<< " (expected: true)"
		<< endl;

	//test case #4
	cout << "dog, cat: " <<
		isAnagram("dog", "cat")
		<< " (expected: false)"
		<< endl;

	//test case #5
	cout << "castles, castle: " <<
		isAnagram("castles", "castle")
		<< " (expected: false)"
		<< endl;

	//test case #6
	cout << "bat, tabb: " <<
		isAnagram("bat", "tabb")
		<< " (expected: false)"
		<< endl;

	//most common substring
	cout << endl << endl << "***Most common substring***" << endl;

	//test case #1
	cout << "abcabcdefdefabc. 3: " <<
		mostCommonSubstring("abcabcdefdefabc", 3)
		<< " (expected: abc)"
		<< endl;

	//test case #2
	cout << "defdefabcabc, 3: " <<
		mostCommonSubstring("defdefabcabc", 3)
		<< " (expected: def)"
		<< endl;

	//test case #3
	cout << "aaabbcccc, 1: " <<
		mostCommonSubstring("aaabbcccc", 1)
		<< " (expected: c)"
		<< endl;

	//test case #4
	cout << "abcdefhijklmnopqrstuvwxyz, 4: " <<
		mostCommonSubstring("abcdefhijklmnopqrstuvwxyz", 4)
		<< " (expected: abcd)"
		<< endl;

	//test case #5
	cout << "abc, 5: " <<
		mostCommonSubstring("abc", 5)
		<< " (expected: NULL)"
		<< endl;

	//test case #6
	cout << "(Empty), 1: " <<
		mostCommonSubstring("", 1)
		<< " (expected: NULL)"
		<< endl;

	//test case #7
	cout << "abcabcab, 3: " <<
		mostCommonSubstring("abcabcab", 3)
		<< " (expected: abc)"
		<< endl;

	//test case #8
	cout << "abcabcab, 0: " <<
		mostCommonSubstring("abcabcab", 0)
		<< " (expected: NULL)"
		<< endl;

	return 0;
}
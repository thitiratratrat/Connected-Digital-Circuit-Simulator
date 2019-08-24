#pragma once
#ifndef INPUTOUTPUT_HPP
#define INPUTOUTPUT_HPP

#include <iostream>
#include <vector>
using namespace std;

class Input {
public:
	Input(string n = "", int v = 0) { value = v; name = n; }
	void setValue(int v) { value = v; }
	void setName(string n) { name = n; }
	int getValue() const { return value; }
	string getName() const { return name; }
	string formatName() const;
	void changeValue();
private:
	int value;
	string name;
};

class Output {
public:
	Output() { value = 0; formula = ""; }
	int getValue() const { return value; }
	string getFormula() const { return formula; }
	void setFormula(string f) { formula = f; }
	void setValue(int v) { value = v; };
private:
	int value;
	string formula;
};


#endif

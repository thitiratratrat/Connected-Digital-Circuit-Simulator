#pragma once
#ifndef CODECONVERTER_HPP
#define CODECONVERTER_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Gate.hpp"
using namespace std;

//2 to 4 decoder
class Decoder {
public:
	Decoder();
	void setInput1(int value, string name) { input1.setValue(value); input1.setName(name); }
	void setInput2(int value, string name) { input2.setValue(value); input2.setName(name); }
	void setEnable(int value, string name) { enable.setValue(value); enable.setName(name); }
	vector<int> getOutput();
	vector<string> getFormula();
private:
	Input input1;
	Input input2;
	Input enable;
	vector <Output> output;
	void getOutput1();
	void getOutput2();
	void getOutput3();
	void getOutput4();
};


//4 to 2 bit
class Encoder {
public:
	Encoder();
	void setInput(int value, string name, int index) { input[index].setValue(value); input[index].setName(name); }
	vector<int> getOutput();
	vector<string> getFormula();
private:
	vector<Input> input;
	vector<Output> output;
	OrGate or;
};


//2 input
class Multiplexer {
public:
	void setInput1(int value, string name) { input1.setValue(value); input1.setName(name); }
	void setInput2(int value, string name) { input2.setValue(value); input2.setName(name); }
	void setSelect(int value, string name) { select.setValue(value); select.setName(name); }
	int getOutput();
	string getFormula();
private:
	Input select;
	Input input1;
	Input input2;
	Output output;
};

//1 to 4 channel
class Demultiplexer {
public:
	Demultiplexer();
	void setInput(int value, string name) { input.setValue(value); input.setName(name); }
	void setSelect2(int value, string name) { select2.setValue(value); select2.setName(name); }
	void setSelect1(int value, string name) { select1.setValue(value); select1.setName(name); }
	vector<int> getOutput();
	vector<string> getFormula();
private:
	Input input;
	Input select1; //least significant bit
	Input select2;
	vector<Output> output;
};

#endif

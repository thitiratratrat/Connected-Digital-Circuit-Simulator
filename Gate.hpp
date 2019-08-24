#pragma once
#ifndef GATE_HPP
#define GATE_HPP

#include <iostream>
#include "InputOutput.hpp"
using namespace std;

//AND, OR, NOT, XOR, NAND, NOR, XNOR

class Gate {
public:
	Gate() {}
	void setInput1(int value, string name) { input1.setValue(value); input1.setName(name); }
	void setInput2(int value, string name) { input2.setValue(value); input2.setName(name); }
	virtual int getOutput() { return 0; }
	virtual string getFormula() { return ""; };
protected:
	Input input1;
	Input input2;
	Output output;
};

class AndGate : public Gate {
public:
	AndGate() : Gate() {}
	int getOutput();
	string getFormula();
};

class OrGate : public Gate {
public:
	int getOutput();
	string getFormula();
};

//shouldn't have 2 inputs
class NotGate : public Gate {
public:
	int getOutput();
	string getFormula();
};

class XorGate : public Gate {
public:
	XorGate() : Gate() {}
	int getOutput();
	string getFormula();
};

class NandGate : public Gate {
public:
	int getOutput();
	string getFormula();
};

class NorGate : public Gate {
public:
	int getOutput();
	string getFormula();
};


class XnorGate : public Gate {
public:
	int getOutput();
	string getFormula();
};

#endif


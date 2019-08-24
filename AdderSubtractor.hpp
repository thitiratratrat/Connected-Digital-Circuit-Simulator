#pragma once
#ifndef ADDERSUBTRACTOR_HPP
#define ADDERSUBTRACTOR_HPP

#include <iostream>
#include "Gate.hpp"

using namespace std;

class HalfAdder {
public:
	void setInput1(int value, string name) { input1.setValue(value); input1.setName(name); }
	void setInput2(int value, string name) { input2.setValue(value); input2.setName(name); }
	virtual int getOutputSum();
	virtual int getOutputCarry();
	virtual string getFormulaSum();
	virtual string getFormulaCarry();
protected:
	Input input1;
	Input input2;
	XorGate xor;
	AndGate and;
	Output sum;
	Output carry;

};

class HalfSubtractor {
public:
	void setInput1(int value, string name) { input1.setValue(value); input1.setName(name); }
	void setInput2(int value, string name) { input2.setValue(value); input2.setName(name); }
	virtual int getOutputDiff();
	virtual int getOutputBorrow();
	virtual string getFormulaDiff();
	virtual string getFormulaBorrow();
protected:
	Input input1;
	Input input2;
	XorGate xor;
	Output difference;
	Output borrow;
};


class FullAdder : public HalfAdder{
public:
	void setInputCin(int value, string name) { Cin.setValue(value); Cin.setName(name); }
	int getOutputSum();
	int getOutputCarry();
	string getFormulaSum();
	string getFormulaCarry();

private:
	Input Cin;
	XorGate xor2;
};


class FullSubtractor :public HalfSubtractor {
public:
	void setInputBin(int value, string name) { Bin.setValue(value); Bin.setName(name); }
	int getOutputDiff();
	int getOutputBorrow();
	string getFormulaDiff();
	string getFormulaBorrow();

private:
	Input Bin;
	XorGate xor2;
};


#endif

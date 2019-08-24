#pragma once
#ifndef OTHERCOMPONENTS_HPP
#define OTHERCOMPONENTS_HPP

#include <iostream>
#include <algorithm>
#include "CodeConverter.hpp"
#include "AdderSubtractor.hpp"
using namespace std;

template<typename Connect1, typename Connect2>
class Wire {
public:
	void setInput(Connect1* i) { input = i; }
	void setOutput(Connect2* o) { output = o; }
	Connect1 getConnect1() const { return inputC; }
	Connect2 getConnect2() const { return outputC; }
	string getFormula() const { return input.getName(); }
	int getValue() const { return input.getValue(); }
	void setInput(int value, string name) { input.setValue(value); input.setName(name); }

private:
	Connect1* inputC;
	Connect2* outputC;
	Input input;
};

template<typename Component>
class Board {
public:
	Board() {};
	//save component of board and can load
	void addComponent(Component c, int type);
	void deleteComponent(Component c, int type);
	void saveBoard() {}
	//update output after button pressed or wire connected
	void updateOutput() {};

private:
	vector<Wire<Input, Input>*> wire;
	vector<Input*> input;
	vector<Output*> output;
	vector<Gate*> gate;
	vector<HalfAdder*> halfadder;
	vector<HalfSubtractor*> halfsubtractor;
	vector<Decoder*> decoder;
	vector<Encoder*> encoder;
	vector<Demultiplexer*> demultiplexer;
	vector<Multiplexer*> multiplexer;
};


//class SegmentOutput {
//public:
//	SegmentOutput() { input.reserve(4); output.reserve(7); }
//	vector<int> getInput() const;
//	vector<int> getOutput() const;
//	int getNumber();
//	void setInputValue(int index, int value);
//private:
//	vector<Input> input;
//	vector<Output> output;
//};


#endif
#pragma once

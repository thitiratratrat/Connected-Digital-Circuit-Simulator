#include "AdderSubtractor.hpp"

int HalfAdder::getOutputSum() {
	xor.setInput1(input1.getValue(), input1.getName());
	xor.setInput2(input2.getValue(), input2.getName());
	sum.setValue(xor.getOutput());
	return sum.getValue();
}

int HalfAdder::getOutputCarry() {
	and.setInput1(input1.getValue(), input1.getName());
	and.setInput2(input2.getValue(), input2.getName());
	carry.setValue(and.getOutput());
	return carry.getValue();
}

string HalfAdder::getFormulaSum() {
	sum.setFormula(xor.getFormula());
	return sum.getFormula();
}

string HalfAdder::getFormulaCarry() {
	carry.setFormula(and.getFormula());
	return and.getFormula();
}

int HalfSubtractor::getOutputDiff() {
	xor.setInput1(input1.getValue(), input1.getName());
	xor.setInput2(input2.getValue(), input2.getName());
	difference.setValue(xor.getOutput());
	return difference.getValue();
}

int HalfSubtractor::getOutputBorrow() {
	if (input1.getValue() == 0 && input2.getValue() == 1)
		borrow.setValue(1);
	else
		borrow.setValue(0);
	return borrow.getValue();
}

string HalfSubtractor::getFormulaDiff() {
	difference.setFormula(xor.getFormula());
	return difference.getFormula();
}

string HalfSubtractor::getFormulaBorrow() {
	borrow.setFormula(input1.formatName() + "'" + input2.formatName());
	return borrow.getFormula();
}


int FullAdder::getOutputSum() {
	xor2.setInput1(HalfAdder::getOutputSum(), HalfAdder::getFormulaSum());
	xor2.setInput2(Cin.getValue(), Cin.getName());
	sum.setValue(xor2.getOutput());
	return sum.getValue();
}

int FullAdder::getOutputCarry() {
	if ((input1.getValue() == 0 && input2.getValue() == 1 && Cin.getValue() == 1) ||
		(input1.getValue() == 1 && input2.getValue() == 0 && Cin.getValue() == 1) ||
		(input1.getValue() == 1 && input2.getValue() == 1 && Cin.getValue() == 0) ||
		(input1.getValue() == 1 && input2.getValue() == 1 && Cin.getValue() == 1)) {
		carry.setValue(1);
	}
	else {
		carry.setValue(0);
	}
	return carry.getValue();
}

string FullAdder::getFormulaSum() {
	sum.setFormula(xor2.getFormula());
	return sum.getFormula();
}

string FullAdder::getFormulaCarry() {
	carry.setFormula(HalfAdder::getFormulaCarry() + " + " + Cin.formatName() + "(" + HalfAdder::getFormulaSum() + ")");
	return carry.getFormula();
}


int FullSubtractor::getOutputDiff() {
	xor2.setInput1(HalfSubtractor::getOutputDiff(), HalfSubtractor::getFormulaDiff());
	xor2.setInput2(Bin.getValue(), Bin.getName());
	difference.setValue(xor2.getOutput());
	return difference.getValue();
}

int FullSubtractor::getOutputBorrow() {
	if ((input1.getValue() == 0 && input2.getValue() == 0 && Bin.getValue() == 1) ||
		(input1.getValue() == 0 && input2.getValue() == 1 && Bin.getValue() == 0) ||
		(input1.getValue() == 0 && input2.getValue() == 1 && Bin.getValue() == 1) ||
		(input1.getValue() == 1 && input2.getValue() == 1 && Bin.getValue() == 1)) {
		borrow.setValue(1);
	}
	else
		borrow.setValue(0);
	return borrow.getValue();
}

string FullSubtractor::getFormulaDiff() {
	difference.setFormula(xor2.getFormula());
	return difference.getFormula();
}

string FullSubtractor::getFormulaBorrow() {
	borrow.setFormula(input1.formatName() + "'" + "(" + input2.formatName() + "(XOR)" +
		Bin.formatName() + ")" + " + " + input2.formatName() + Bin.formatName());
	return borrow.getFormula();
}

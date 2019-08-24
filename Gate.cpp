#include "Gate.hpp"

int AndGate::getOutput() {
	output.setValue(input1.getValue() * input2.getValue());
	return output.getValue();
}

string AndGate::getFormula() {
	output.setFormula(input1.formatName() + input2.formatName());
	return output.getFormula();
}

int OrGate::getOutput() {
	if (input1.getValue() == 1 || input2.getValue() == 1)
		output.setValue(1);
	else
		output.setValue(0);
	return output.getValue();
}

string OrGate::getFormula() {
	output.setFormula(input1.formatName() + " + " + input2.formatName());
	return output.getFormula();
}


int NotGate::getOutput() {
	if (input1.getValue() == 1)
		output.setValue(0);
	else
		output.setValue(1);
	return output.getValue();
}

string NotGate::getFormula() {
	output.setFormula(input1.formatName() + "'");
	return output.getFormula();
}


int XorGate::getOutput() {
	if (input1.getValue() == input2.getValue())
		output.setValue(0);
	else
		output.setValue(1);
	return output.getValue();
}

string XorGate::getFormula() {
	output.setFormula(input1.formatName() + " (XOR) " + input2.formatName());
	return output.getFormula();
}


int NandGate::getOutput() {
	if (input1.getValue() == 1 && input2.getValue() == 1)
		output.setValue(0);
	else
		output.setValue(1);
	return output.getValue();
}

string NandGate::getFormula() {
	output.setFormula("(" + input1.formatName() + input2.formatName() + ")'");
	return output.getFormula();
}


int NorGate::getOutput() {
	if (input1.getValue() == 0 && input2.getValue() == 0)
		output.setValue(1);
	else
		output.setValue(0);
	return output.getValue();
}

string NorGate::getFormula() {
	output.setFormula("(" + input1.formatName() + " + " + input2.formatName() + ")'");
	return output.getFormula();
}


int XnorGate::getOutput() {
	if (input1.getValue() == input2.getValue())
		output.setValue(1);
	else
		output.setValue(0);
	return output.getValue();
}

string XnorGate::getFormula() {
	output.setFormula(input1.formatName() + " (XNOR) " + input2.formatName());
	return output.getFormula();
}


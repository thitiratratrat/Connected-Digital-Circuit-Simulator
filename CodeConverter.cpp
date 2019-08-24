#include "CodeConverter.hpp"
Decoder::Decoder() {
	Output temp;
	for (int i = 0; i < 4; i++)
		output.push_back(temp);
}

void Decoder::getOutput1() {
	Output temp;
	if (enable.getValue() == 1 && input2.getValue() == 0 && input1.getValue() == 0)
		temp.setValue(1);
	else
		temp.setValue(0);
	temp.setFormula(enable.formatName() + input2.formatName() + "'" + input1.formatName() + "'");
	output[0] = temp;

}

void Decoder::getOutput2() {
	Output temp;
	if (enable.getValue() == 1 && input2.getValue() == 0 && input1.getValue() == 1)
		temp.setValue(1);
	else
		temp.setValue(0);
	temp.setFormula(enable.formatName() + input2.formatName() + "'" + input1.formatName());
	output[1] = temp;
}

void Decoder::getOutput3() {
	Output temp;
	if (enable.getValue() == 1 && input2.getValue() == 1 && input1.getValue() == 0)
		temp.setValue(1);
	else
		temp.setValue(0);
	temp.setFormula(enable.formatName() + input2.formatName() + input1.formatName() + "'");
	output[2] = temp;
}

void Decoder::getOutput4() {
	Output temp;
	if (enable.getValue() == 1 && input2.getValue() == 1 && input1.getValue() == 1)
		temp.setValue(1);
	else
		temp.setValue(0);
	temp.setFormula(enable.formatName() + input2.formatName() + input1.formatName());
	output[3] = temp;
}

vector<int> Decoder::getOutput() {
	getOutput1();
	getOutput2();
	getOutput3();
	getOutput4();
	vector<int> temp;
	for (int i = 0; i < output.size(); i++)
		temp.push_back(output[i].getValue());
	return temp;
}

vector<string> Decoder::getFormula() {
	vector<string> temp;
	for (int i = 0; i < output.size(); i++)
		temp.push_back(output[i].getFormula());
	return temp;
}


Encoder::Encoder() {
	Input temp;
	Output temp2;
	for (int i = 0; i < 5; i++)
		input.push_back(temp);
	for (int i = 0; i < 3; i++)
		output.push_back(temp2);
}

vector<int> Encoder::getOutput() {
	vector<int> temp;
	//output1
	or.setInput1(input[3].getValue(), input[3].getName());
	or.setInput2(input[1].getValue(), input[1].getName());
	output[0].setValue(or .getOutput());
	temp.push_back(output[0].getValue());
	output[0].setFormula(or .getFormula());
	//output2
	or .setInput1(input[3].getValue(), input[3].getName());
	or .setInput2(input[2].getValue(), input[2].getName());
	output[1].setValue(or .getOutput());
	output[1].setFormula(or .getFormula());
	temp.push_back(output[1].getValue());

	return temp;
}

vector<string> Encoder::getFormula() {
	vector<string> temp;
	temp.push_back(output[0].getFormula());
	temp.push_back(output[1].getFormula());
	return temp;
}


int Multiplexer::getOutput() {
	if ((select.getValue() == 0 && input2.getValue() == 1 && input1.getValue() == 0) ||
		(select.getValue() == 0 && input2.getValue() == 1 && input1.getValue() == 1) ||
		(select.getValue() == 1 && input2.getValue() == 0 && input1.getValue() == 1) ||
		(select.getValue() == 1 && input2.getValue() == 1 && input1.getValue() == 1))
		output.setValue(1);
	else
		output.setValue(0);
	return output.getValue();
}

string Multiplexer::getFormula() {
	output.setFormula(select.formatName() + "'" + input2.formatName() + " + " + select.formatName() + input1.formatName());
	return output.getFormula();
}


Demultiplexer::Demultiplexer() {
	Output temp;
	for (int i = 0; i < 4; i++)
		output.push_back(temp);
}

vector<int> Demultiplexer::getOutput() {
	int num = 0;
	vector<int> temp(4, 0);
	if (select1.getValue() == 1)
		num += 1;
	if (select2.getValue() == 1)
		num += 2;
	output[num].setValue(input.getValue());
	temp[num] = input.getValue();
	for (int i = 0; i < output.size(); i++) {
		if (i == num)
			continue;
		else {
			output[i].setValue(0);
			temp[i] = 0;
		}
	}
	return temp;
}

vector<string> Demultiplexer::getFormula() {
	vector<string> temp;
	output[0].setFormula(select2.formatName() + "'" + select1.formatName() + "'" + input.formatName());
	output[1].setFormula(select2.formatName() + "'" + select1.formatName() + input.formatName());
	output[2].setFormula(select2.formatName() + select1.formatName() + "'" + input.formatName());
	output[3].setFormula(select2.formatName() + select1.formatName() + input.formatName());
	for (int i = 0; i < output.size(); i++)
		temp.push_back(output[i].getFormula());
	return temp;
}

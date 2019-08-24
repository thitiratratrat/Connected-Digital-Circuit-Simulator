#include "OtherComponents.hpp"

template<typename Component>
void Board<Component>::addComponent(Component c, int type) {
	if (type == 0)
		wire.push_back(c);
	else if (type == 1)
		input.push_back(c);
	else if (type == 2)
		output.push_back(c);
	else if (type == 3)
		gate.push_back(c);
	else if (type == 4)
		halfadder.push_back(c);
	else if (type == 5)
		halfsubtractor.push_back(c);
	else if (type == 6)
		decoder.push_back(c);
	else if (type == 7)
		encoder.push_back(c);
	else if (type == 8)
		demultiplexer.push_back(c);
	else
		multiplexer.push_back(c);
}

template<typename Component>
void Board<Component>::deleteComponent(Component c, int type) {
	if (type == 0)
		wire.erase(remove(wire.begin(), wire.end(), c), wire.end());
	else if (type == 1)
		input.erase(remove(input.begin(), input.end(), c), input.end());
	else if (type == 2)
		output.erase(remove(input.begin(), input.end(), c), input.end());
	else if (type == 3)
		gate.erase(remove(input.begin(), input.end(), c), input.end());
	else if (type == 4)
		halfadder.erase(remove(input.begin(), input.end(), c), input.end());
	else if (type == 5)
		halfsubtractor.erase(remove(input.begin(), input.end(), c), input.end());
	else if (type == 6)
		decoder.erase(remove(input.begin(), input.end(), c), input.end());
	else if (type == 7)
		encoder.erase(remove(input.begin(), input.end(), c), input.end());
	else if (type == 8)
		demultiplexer.erase(remove(input.begin(), input.end(), c), input.end());
	else
		multiplexer.erase(remove(input.begin(), input.end(), c), input.end());
}


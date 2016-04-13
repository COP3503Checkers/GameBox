#ifndef INPUTERROR_H_
#define INPUTERROR_H_

#include <exception>
#include <stdexcept>

//thrown to indicate bad input
class input_error: public std::runtime_error {
public:
	explicit input_error(const std::string& msg)
			: std::runtime_error(msg) {
	}
};

#endif

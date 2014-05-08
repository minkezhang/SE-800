#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <exception>

/**
 * custom exception classes are defined here -- cf. http://bit.ly/1irWjNY for implementation details
 */

class BaseClassUnimplementedError : public std::exception {
	virtual const char *what() const throw() {
		return "This method was called from a base class who did not implement the function. Please implement in the derived class.";
	}
};

#endif

#include <string>
#include "RequestObject.h"

#ifndef PARSER_H_
#define PARSER_H_

class Parser {
public:
	Parser();

	/*
	 * return
	 * 	0 - ok
	 * 	1 - error (bad resource, ...)
	 */
	int parse(std::string p_requestString, RequestObject &p_RequestObject);
private:
};

#endif /* PARSER_H_ */

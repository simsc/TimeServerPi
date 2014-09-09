#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Parser::Parser() {
}

/* HTTP Format
 *
 * <initial line, different for request vs. response>
 * Header1: value1
 * Header2: value2
 * Header3: value3
 *
 * <optional message body goes here, like file contents or query data;
 * it can be many lines long, or even binary data $&*%@!^$@>
 */

/* Header Line
 *
 * One line per header, of the form "Header-Name: value"
 */

int Parser::parse(string p_requestString, RequestObject &p_RequestObject) {
    string delimiter = "\r\n";
	string::size_type pos = 0;
	string::size_type prev = 0;

	// container for initial line, headers and body
	string initialLine;
	vector<string> headerContainer;
//	string body;

	// first line
	pos = p_requestString.find(delimiter); // find() - position of a string
	initialLine = p_requestString.substr(0, pos); // substr(index of first character, number of characters)
	prev = pos + 1;

	/*
	 * ... all other line (header)
	 * std::string::npos
	 * -> ... greatest possible value for an element of type size_t.
	 * -> ... means "until the end of the string".
	 */
	while ((pos = p_requestString.find(delimiter, prev)) != string::npos) {
        string headerLine = p_requestString.substr(prev +1, pos - prev);
		if (headerLine == "")
			break; // end of header section
		headerContainer.push_back(headerLine);
		prev = pos + 1;
	}

	// skip the empty line between headers and body
//	pos = p_requestString.find(delimiter, prev);
//	prev = pos + 1;
//	// body
//	body = p_requestString.substr(prev, p_requestString.length());
//	p_RequestObject.setBody(body);

	/**********************
	 * extract initalline *
	 *********************/
	pos = 0;
	prev = 0;
	delimiter = " ";

	vector<string> initialLineContainer;
	while ((pos = initialLine.find(delimiter, prev)) != string::npos) {
		string initialLineElem = initialLine.substr(prev, pos - prev);
		initialLineContainer.push_back(initialLineElem);
		prev = pos + 1;
	}
	string initialLineElem = initialLine.substr(prev, pos - prev);
	initialLineContainer.push_back(initialLineElem);

	/***************************************************
	 * fill request object with values of initial line *
	 **************************************************/
	for (unsigned i = 0; i < initialLineContainer.size(); i++) {
		switch (i) {
		// http request method
        case 0:
			p_RequestObject.setHttpRequestMethod(initialLineContainer[i]);
			break;
			// ressource
        case 1:
			p_RequestObject.setRessource(initialLineContainer[i]);
			break;
		default:
			break;
		}
	}

	/*********************************************
	 * fill request object with values of header *
	 ********************************************/
	for (string h : headerContainer) {
		string headerKey = h.substr(0, h.find(" "));

		if (headerKey == "Accept:") {
			p_RequestObject.setHeaderAccept(h.substr(h.find(" ") + 1));
		}

		if (headerKey == "Content-Type:") {
			p_RequestObject.setHeaderContentType(h.substr(h.find(" ") + 1));
		}

		if (headerKey == "Timezone:") {
			p_RequestObject.setHeaderTimezone(h.substr(h.find(" ") + 1));
		}
	}

    // only test output
//    cout << "Initial Line: " << initialLine << endl;
//    cout << endl;
//    for (string i : initialLineContainer) {
//       cout << "Initial Line Element: " << i << endl;
//    }
//    cout << endl;
//    for (string h : headerContainer) {
//       cout << "Header: " << h << endl;
//    }
//    cout << endl << "Body: " << body << endl;

	return 0;
}


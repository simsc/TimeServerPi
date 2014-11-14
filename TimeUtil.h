#include "Parser.h"
#include "RequestObject.h"
#include "FormatterHtml.h"
#include "FormatterJson.h"
#include "FormatterString.h"
#include "FormatterXml.h"

#ifndef TIMEUTIL_H_
#define TIMEUTIL_H_

class TimeUtil {
public:
    TimeUtil();
    std::string getRepsonse(std::string requestString);

private:
    RequestObject m_requestObject;
    Parser m_parser;
    FormatterHtml m_formatterHtml;
    FormatterJson m_formatterJson;
    FormatterString m_formatterString;
    FormatterXml m_formatterXml;
};

#endif /* TIMEUTIL_H_ */

#include <string>

#ifndef REQUESTOBJECT_H_
#define REQUESTOBJECT_H_

class RequestObject {
public:
	RequestObject();
	RequestObject(std::string p_httpRequestMethod, std::string p_ressource,
			std::string p_headerContentType, std::string p_headerAccept,
			std::string p_headerTimezone, std::string p_body);

	std::string getHttpRequestMethod();
	std::string getRessource();
	std::string getHeaderContentType();
	std::string getHeaderAccept();
	std::string getHeaderTimezone();
	std::string getBody();

	void setHttpRequestMethod(std::string p_httpRequestMethod);
	void setRessource(std::string p_ressource);
	void setHeaderContentType(std::string p_headerContentType);
	void setHeaderAccept(std::string p_headerAccept);
	void setHeaderTimezone(std::string p_headerTimezone);
	void setBody(std::string p_body);

private:
	std::string m_httpRequestMethod;
	std::string m_ressource;
	std::string m_headerContentType;
	std::string m_headerAccept;
	std::string m_headerTimezone;
	std::string m_body;
};

#endif /* REQUESTOBJECT_H_ */

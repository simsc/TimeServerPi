#include "RequestObject.h"

RequestObject::RequestObject() :
		m_httpRequestMethod(""), m_ressource(""), m_headerContentType(""), m_headerAccept(
				""), m_headerTimezone(""), m_body("") {
}

RequestObject::RequestObject(std::string p_httpRequestMethod,
		std::string p_ressource, std::string p_headerContentType,
		std::string p_headerAccept, std::string p_headerTimezone, std::string p_body) :
		m_httpRequestMethod(p_httpRequestMethod), m_ressource(p_ressource), m_headerContentType(
				p_headerContentType), m_headerAccept(p_headerAccept), m_headerTimezone(
				p_headerTimezone), m_body(p_body) {
}

std::string RequestObject::getHttpRequestMethod() {
	return m_httpRequestMethod;
}

std::string RequestObject::getRessource() {
	return m_ressource;
}

std::string RequestObject::getHeaderContentType() {
	return m_headerContentType;
}

std::string RequestObject::getHeaderAccept() {
	return m_headerAccept;
}

std::string RequestObject::getHeaderTimezone() {
	return m_headerTimezone;
}

std::string RequestObject::getBody() {
	return m_body;
}

void RequestObject::setHttpRequestMethod(std::string p_httpRequestMethod) {
	m_httpRequestMethod = p_httpRequestMethod;
}

void RequestObject::setRessource(std::string p_ressource) {
	m_ressource = p_ressource;
}

void RequestObject::setHeaderContentType(std::string p_headerContentType) {
	m_headerContentType = p_headerContentType;
}

void RequestObject::setHeaderAccept(std::string p_headerAccept) {
	m_headerAccept = p_headerAccept;
}

void RequestObject::setHeaderTimezone(std::string p_headerTimezone) {
	m_headerTimezone = p_headerTimezone;
}

void RequestObject::setBody(std::string p_body) {
	m_body = p_body;
}

/*
 * TimeServer.cpp
 *
 *  Created on: 13.11.2014
 *      Author: ada
 */

#include "TimeServer.h"

#include "boost/asio.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include <iostream>
//#include "Pi.cpp"
#include "Pi.h"
#include "dcftime_iface.hpp"
#include "dcftime_rcp_common.hpp"

using boost::asio::io_service;
using boost::asio::ip::tcp;

class dcftime_impl: public dcftime_iface {
public:
	virtual ~dcftime_impl() override = default;
	virtual long dcfTimeUnix() override {
		return 42;
	}
};
class server {
public:
	server(dcftime_impl *service) :
			service_ { service } {
	}
	void activate() {
		io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1313));
		tcp::iostream s;
		acceptor.accept(*s.rdbuf());

		boost::archive::binary_iarchive iarchive { s };

		service_ids service_id;
		iarchive >> service_id;
		std::cout << "S: service_id=" << as_integer(service_id) << std::endl;
		switch (service_id) {
		case service_ids::dcfTimeUnix:
			Pi pi;
			auto result1 = pi.requestTimeSinceEpoch();
			boost::archive::binary_oarchive oarchive { s };
//			long result1 = 4200;
			oarchive << result1;
			s.close();
			break;

//		case service_ids::dcfTimeStruct:
//			auto result2 = requestTime();
//			boost::archive::binary_oarchive oarchive { s };
//			oarchive << result2;
//			s.close();
//			break;
		}
	}
private:
	dcftime_iface *service_;
};
int main() {
	dcftime_impl dcftime;
	server s { &dcftime };
	while(1) {
		s.activate();
	}
}

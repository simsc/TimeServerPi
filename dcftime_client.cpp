#include "dcftime_client.h"

using boost::asio::io_service;
using boost::asio::ip::tcp;

long dcftime_client::dcfTimeUnix() {
	long result = 0;
	try {
	tcp::iostream stream("localhost", "1313");
	boost::archive::binary_oarchive oarchive{ stream };

	const auto &service_id = service_ids::dcfTimeUnix;
	oarchive << service_id;
	stream.flush();

	boost::archive::binary_iarchive iarchive{ stream };
	iarchive >> result;
	}
	catch (boost::archive::archive_exception ex)
	{
		std::cout << "ex caught" << std::endl;
	}
	return result;
}

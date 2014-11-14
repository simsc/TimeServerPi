#include "boost/asio.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include "boost/archive/archive_exception.hpp"

#include <iostream>

#include "dcftime_iface.h"
#include "dcftime_rcp_common.h"

class dcftime_client : public dcftime_iface {

public:
	virtual long dcfTimeUnix() override;
};

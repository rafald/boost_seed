#define BOOST_TEST_MODULE module_test_uri
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_uri_no_protocol ) {//FIXME remove http:// and fix  the issue (could be is_valid returning false)
	BOOST_CHECK( url.path() == "/ist/best/solution" );
	BOOST_CHECK_THROW( prot.writeMessageBegin("name", apache::thrift::protocol::T_CALL, 0), 
		std::out_of_range );
   
	BOOST_REQUIRE_THROW
   ( 
		int for_fun_to_show_this_can_be_statement_not_necessary_expression = 7 ;
		lb::server::getHttpServer(0, new TransportFactory, new ProtocolFactory, "http://127.0.0.1:8080" ), 
			lb::invalid_processor_error
   );
}
}

// BOOST_ROOT=~/c++/boost_1_51_0/ bjam --debug-loading -d2
// ( cls && set BOOST_ROOT=c:\cygwin\home\rdzbek\c++\boost_1_51_0 && bjam -d1 )

///////////////////////// custom main to pass runtime only arg "--auto_start_dbg=yes" ///////////////////////
#define BOOST_TEST_NO_MAIN
#include <boost/test/included/unit_test.hpp>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//____________________________________________________________________________//
struct MyConfig {
	MyConfig() {
		boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_successful_tests );//overrides command line
	}
};
BOOST_GLOBAL_FIXTURE( MyConfig );

BOOST_AUTO_TEST_CASE(run_http_server_can_not_bind_to_socket_212_1_2_1_8080__WSAEADDRNOTAVAIL_10049) {
   ??? mixed with manual
}

void run_http_server_one_GET_client_request() {//it is not BOOST_AUTO_TEST_CASE because we need timeout
	std::string endpoint = "http://127.0.0.1:8080";
	std::unique_ptr<apache::thrift::server::TServer> server;
	std::ostringstream messages_from_client;

	boost::packaged_task<int> pt( [=, &server, &messages_from_client]() -> int {
		_sleep(HTTP_SERVER_STARTUP_TIME_MS);//give server some time for startup

		using namespace boost::network;
		http::basic_request< http::tags::http_server > request;
		http::client c;
		http::client::request req(endpoint);
		//TODO wait for signal from server that it is ready
		http::client::response res = c.get(req);
		messages_from_client << "RESPONSE BODY[ " << body(res) << " ]";
		messages_from_client << "\nabout to stop server from client and exit client thread";
		server->stop();
		return 0; 
	} );
	boost::unique_future<int> fi=pt.get_future();
	boost::thread task(boost::move(pt)); // launch task on a thread

	server = make_unique_ptr( lb::server::getHttpServer(new Processor, new TransportFactory, new ProtocolFactory, endpoint ) );
	BOOST_CHECK(server.get());
	server->serve();

	fi.wait(); // wait for it to finish and then display recorded messages
	BOOST_TEST_MESSAGE(messages_from_client.str());

	BOOST_CHECK(fi.is_ready());
	BOOST_CHECK(fi.has_value());
	BOOST_CHECK(!fi.has_exception());
	BOOST_CHECK(fi.get_state()==boost::future_state::ready);
	BOOST_CHECK(fi.get()==0);

	BOOST_TEST_PASSPOINT();//test
	//_beep(Frequency, Duration);
}


//____________________________________________________________________________//
void test_inf_loop() { 
	BOOST_TEST_CHECKPOINT("About to enter an infinite loop!"); 
	while(1); 
}

using namespace boost::unit_test;
test_suite*
xinit_unit_test_suite( int argc, char* argv[] ) {
	framework::master_test_suite().p_name.value = "HTTP Server intermediate tests with dummy Protocol, Transport and Processor";

	// with explicit registration we could specify a test case timeout
	//framework::master_test_suite().add( BOOST_TEST_CASE( &test_inf_loop), 0, /* timeout */ 1 );

	auto ts1 = BOOST_TEST_SUITE( "test_suite1" );
	ts1->add( BOOST_TEST_CASE( &run_http_server_one_GET_client_request), 0, /* timeout */ 1 );
	framework::master_test_suite().add( ts1 );

	return 0;
}
int 
main( int argc_, char* argv_[] ) {
		boost::unit_test::init_unit_test_func init_func = &xinit_unit_test_suite;
		char *args[] = {"", 
			"--log_level=all", 
			"--auto_start_dbg=yes"};//TODO concat with actual main(argc argv)
		return ::boost::unit_test::unit_test_main( init_func, sizeof(args)/sizeof(args[0]), args );
}

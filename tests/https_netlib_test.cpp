#define MSG(STR_EXPR) BOOST_MESSAGE(STR_EXPR) //std::cout << "\n" << STR_EXPR << std::flush

///////////////////////// custom main to pass runtime only arg "--auto_start_dbg=yes" ///////////////////////
#define BOOST_TEST_NO_MAIN // we provide own main
#define BOOST_TEST_MAIN //  please generate default test module initialization function: init_unit_test_suite
// yes, it is not the error, BOTH must be defined BOOST_TEST_NO_MAIN and BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

//run selectively --run-test=http_netlib_transport_tests
int 
main( int argc_, char* argv_[] ) {
	boost::unit_test::init_unit_test_func init_func = &init_unit_test_suite;
#if 0	
	char *args[] = {"", 
		"--log_level=all", 
		"--auto_start_dbg=yes"};//TODO concat/merge with actual argc argv
	return ::boost::unit_test::unit_test_main( init_func, sizeof(args)/sizeof(args[0]), args );
#else	
	return ::boost::unit_test::unit_test_main( init_func, argc_, argv_ );
#endif	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MyConfig {
	MyConfig() {//overrides command line
		boost::unit_test::unit_test_log.set_threshold_level( boost::unit_test::log_test_units );
      // log_successful_tests
	}
};
BOOST_GLOBAL_FIXTURE( MyConfig );
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(XXX_tests)
BOOST_AUTO_TEST_CASE(test_XXX) {
   // XXX
}
BOOST_AUTO_TEST_SUITE_END()

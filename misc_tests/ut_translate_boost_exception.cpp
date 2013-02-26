#include "boost/test/unit_test_monitor.hpp" 
#include "boost/exception/all.hpp" 
#include "boost/test/test_tools.hpp" //BOOST_FAIL
#include "boost/test/unit_test_suite.hpp" // BOOST_GLOBAL_FIXTURE

void translate(boost::exception const& e) { 
	BOOST_FAIL(boost::diagnostic_information(e)); 
	//TODO remove prefix ut_translate_boost_exception.cpp(7): 
	//TODO always FAIL but no ERROR REQUIRE etc - better to override what()
} 
struct Exception_fixture { 
	Exception_fixture() { 
		::boost::unit_test::unit_test_monitor.register_exception_translator<boost::exception>(&translate); 
		//TODO should be called in init_unit_test_suite
	} 
}; 
BOOST_GLOBAL_FIXTURE( Exception_fixture );

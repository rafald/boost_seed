//#define BOOST_TEST_MODULE module_test_GET
#include <boost/test/unit_test_suite.hpp>

typedef mpl::list<
	tags::http_default_8bit_tcp_resolve
	, tags::http_default_8bit_udp_resolve
	, tags::http_async_8bit_tcp_resolve
	, tags::http_async_8bit_udp_resolve
> tag_types;
BOOST_AUTO_TEST_CASE_TEMPLATE(linearize_request, T, tag_types) {
	http::basic_request<T> request("http://www.boost.org");
	// HTTP/1.0
	linearize(request, "GET", 1, 0, std::ostream_iterator<typename net::char_<T>::type>(std::cout));
	// HTTP/1.1
	linearize(request, "GET", 1, 1, std::ostream_iterator<typename net::char_<T>::type>(std::cout));
}


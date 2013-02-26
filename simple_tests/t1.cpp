#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

namespace {

}

BOOST_AUTO_TEST_SUITE( safe_shared_ptr_test )


BOOST_AUTO_TEST_CASE( test_shared_ptr_ctors )
{
  BOOST_CHECK_EQUAL(sp.use_count(), 1);
}

namespace {
}

BOOST_AUTO_TEST_CASE( test_shared_ptr_compare )
{
  BOOST_CHECK_EQUAL(pa == pb, true);
}


BOOST_AUTO_TEST_CASE( test_deref_thread )
{
  deref_helper dh;

  dh.run_thread();
  dh.invalidate();
  dh.join();
}

BOOST_AUTO_TEST_SUITE_END()

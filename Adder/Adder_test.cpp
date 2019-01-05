/*
 * Adder_test.cpp
 *
 *  Created on: Dec 30, 2018
 *      Author: alpha
 */

#include "Adder.h"

#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE( my_test )
{
	Adder *a=new Adder();

    // seven ways to detect and report the same error:
    BOOST_CHECK( a->add( 2,2 ) == 4 );        // #1 continues on error

    BOOST_REQUIRE( a->add(2,2 ) == 4 );      // #2 throws on error

}

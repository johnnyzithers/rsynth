#define CATCH_CONFIG_MAIN 
#include "../include/catch2/catch.hpp"

#include "../include/ADSR.h"

#define private public

TEST_CASE( "Factorials are computed", "[factorial]" ) {

	ADSR adsr;


    SECTION( "ADSR: changing sampling rate does updage member var" ) 
    {
		adsr.setSampleRate(44100);
    	REQUIRE( adsr._sr == 44100 );
	}


}

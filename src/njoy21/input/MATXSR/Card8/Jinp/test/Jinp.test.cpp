#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "njoy21.hpp"

using namespace njoy::njoy21::input;

SCENARIO( "MATXSR Card8 Jinp",
          "[MATXSR], [Card8], [Jinp]" ){
  GIVEN( "valid inputs" ){
    WHEN( "valid inputs are provided" ){
      std::vector< std::string > validValues{
        " 0",
        " 0 1",
        " 0 1 5",
        " 0 1 5 10",
        " 0 1 5 10 20" };
      for( unsigned int i = 0; i < validValues.size(); i++ ){
        iRecordStream<char> iss( std::istringstream( validValues.at(i) ) );

        THEN( "the value can be verified" ){
          REQUIRE( 0 == argument::extract< MATXSR::Card8::Jinp >
                                     ( iss, i+1 ).value.at(0) );
          if( i >= 1 ) REQUIRE( 1 == argument::extract< MATXSR::Card8::Jinp >
                                     ( iss, i+1 ).value.at(1) );
          if( i >= 2 ) REQUIRE( 5 == argument::extract< MATXSR::Card8::Jinp >
                                     ( iss, i+1 ).value.at(2) );
          if( i >= 3 ) REQUIRE( 10 == argument::extract< MATXSR::Card8::Jinp >
                                      ( iss, i+1 ).value.at(3) );
          if( i >= 4 ) REQUIRE( 20 == argument::extract< MATXSR::Card8::Jinp >
                                      ( iss, i+1 ).value.at(4) );
        }
      }
    }
  } // GIVEN

  GIVEN( "invalid inputs" ){
    WHEN( "no input is provided" ){
      iRecordStream<char> iss( std::istringstream( " /" ) );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( argument::extract< MATXSR::Card8::Jinp >( iss, 1 ) );
      }
    }

    WHEN( "an invalid input is provided" ){
      iRecordStream<char> iss( std::istringstream( std::to_string( -1 ) ) );

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( argument::extract< MATXSR::Card8::Jinp >( iss, 1 ) );
      }
    }
  } // GIVEN
} // SCENARIO
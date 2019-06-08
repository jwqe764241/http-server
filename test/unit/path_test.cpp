#ifdef __MINGW32__
	#define __USE_MINGW_ANSI_STDIO 0
#endif

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "file/path.hpp"

TEST_CASE("path parse build test 1", "[build]")
{
	path path("aa/bb/cc/dd/ee");
	
	
	REQUIRE(path.get_size() == 5);
	
	REQUIRE(path.get_first_part().get_name() == "aa");
	REQUIRE(path.get_last_part().get_name() == "ee");
	
	REQUIRE(path.get_part(0).get_name() == "aa");
	REQUIRE(path.get_part(1).get_name() == "bb");
	REQUIRE(path.get_part(2).get_name() == "cc");
	REQUIRE(path.get_part(3).get_name() == "dd");
	REQUIRE(path.get_part(4).get_name() == "ee");
	
	
	REQUIRE(path.get_path_string() == "aa\\bb\\cc\\dd\\ee");
	REQUIRE(path.get_real_path_string() == "aa\\bb\\cc\\dd\\ee");
	
	path.append("ff");
	
	REQUIRE(path.get_last_part().get_name() == "ff");
	
	REQUIRE(path.get_part(5).get_name() == "ff");
}

TEST_CASE("path parse build test 2","[build]")
{
	path path("../../aa/bb/cc/../dd/ee/");
	
	REQUIRE(path.get_size() == 8);
	
	REQUIRE(path.get_first_part().get_name() == "..");
	REQUIRE(path.get_last_part().get_name() == "ee");
	
	REQUIRE(path.get_part(0).get_name() == "..");
	REQUIRE(path.get_part(1).get_name() == "..");
	REQUIRE(path.get_part(2).get_name() == "aa");
	REQUIRE(path.get_part(3).get_name() == "bb");
	REQUIRE(path.get_part(4).get_name() == "cc");
	REQUIRE(path.get_part(5).get_name() == "..");
	REQUIRE(path.get_part(6).get_name() == "dd");
	REQUIRE(path.get_part(7).get_name() == "ee");
	
	REQUIRE(path.get_path_string() == "..\\..\\aa\\bb\\cc\\..\\dd\\ee");
	REQUIRE(path.get_real_path_string() == "aa\\bb\\dd\\ee");
}
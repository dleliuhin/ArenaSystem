 /*! \file arena_system_test.cpp
  * \brief ArenaSystemTest class implementation.

  * \authors Il'ya Batalev
  * \date March 2021
  */

//=======================================================================================

#include "arena_system_test.h"

#include "arena_system.h"

#include "arena_system.h"
#include "arena_config.h"

//=======================================================================================
/*! \test TEST( DeviceTest, test_constructor )
 * \brief Various constructors.
 */
TEST( ArenaSystemTest, test_open_close )
{
	ASSERT_TRUE( ArenaSystem::close() );
	ASSERT_TRUE( ArenaSystem::close() );

	ASSERT_TRUE( ArenaSystem::open() );
	ASSERT_TRUE( ArenaSystem::open() );

	ASSERT_TRUE( ArenaSystem::close() );
	ASSERT_TRUE( ArenaSystem::close() );

	ASSERT_TRUE( ArenaSystem::open()  );
	ASSERT_TRUE( ArenaSystem::close() );

	ASSERT_TRUE( ArenaSystem::open()  );
	ASSERT_TRUE( ArenaSystem::close() );
}
//=======================================================================================
/*! \test TEST( DeviceTest, test_exist_wrong_filled_only_str )
 * \brief Test of function exist with wrong filled config
 */
TEST( ArenaSystemTest, test_exist_wrong_filled_only_str )
{

    ArenaConfig conf_default;
	ASSERT_EQ( nullptr, ArenaSystem::exist( conf_default, true ) );
	ASSERT_EQ( nullptr, ArenaSystem::exist( conf_default, false ) );

    ArenaConfig conf_network_filled_str;
    conf_network_filled_str.device.sn           = "conf_correct.device.sn";
    conf_network_filled_str.network.as_str.ip   = "conf_correct.network.as_str.ip";
    conf_network_filled_str.network.as_str.mask = "conf_correct.network.as_str.mask";
    conf_network_filled_str.network.as_str.gw   = "conf_correct.network.as_str.gw";

	ASSERT_EQ( nullptr, ArenaSystem::exist( conf_network_filled_str, true ) );

	ASSERT_TRUE( ArenaSystem::open() );
	ASSERT_EQ( nullptr, ArenaSystem::exist( conf_network_filled_str, true ) );
	ASSERT_TRUE( ArenaSystem::close() );
}
//=======================================================================================

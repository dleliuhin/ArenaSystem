 /*! \file arena_system_test.cpp
  * \brief ArenaSystemTest class implementation.

  * \authors Il'ya Batalev
  * \date March 2021
  */

//=======================================================================================

#include "arena_system_test.h"
#include "arena_system.h"
#include "arena_config.h"

//=======================================================================================
/*! \test TEST( DeviceTest, test_disconnected_exist_right_filled )
 * \brief Test of function exist with correct data
 */
TEST( ArenaSystemTest, test_disconnected_exist_right_filled ) 
{
	ASSERT_TRUE( ArenaSystem::open() );

        ASSERT_EQ( nullptr, ArenaSystem::exist( {}, true ) );

	ASSERT_TRUE( ArenaSystem::close() );
}
//=======================================================================================
/*! \test TEST( DeviceTest, test_disconnected_force_ip_right_filled )
 * \brief Test of function force_ip with right filled config
 */
TEST( ArenaSystemTest, test_disconnected_force_ip_right_filled )
{
	ASSERT_TRUE( ArenaSystem::open() );

        ASSERT_FALSE( ArenaSystem::force_ip( {} ) );

	ASSERT_TRUE( ArenaSystem::close() );
}
//=======================================================================================
/*! \test TEST( DeviceTest, test_disconnected_force_ip_wrong_filled_ip )
 * \brief Test of function force_ip with wrong ip address
 */
TEST( ArenaSystemTest, test_disconnected_force_ip_wrong_filled_ip )
{
	ASSERT_TRUE( ArenaSystem::open() );

        ArenaConfig conf_network_filled_error;
        // Need to fill config with camera settings

	ASSERT_TRUE( ArenaSystem::open() );

	ASSERT_FALSE( ArenaSystem::force_ip( conf_network_filled_error ) );

	ASSERT_TRUE( ArenaSystem::close() );
}
//=======================================================================================
